#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using std::deque;
using std::vector;

const long long INF = 100000000000;

struct edge
{
    long long from;
    long long to;
    long long flow;
    long long capacity;
};



bool bfs(vector<vector<long long>>& graph, vector<edge>& edges, vector<long long>& d)
{
    deque<long long> queue;
    d.assign(graph.size(), -1);
    d[0] = 0;
    queue.push_back(0);
    long long v = 0;
    while (!queue.empty())
    {
        v = queue.front();
        queue.pop_front();
        for (long long i = 0; i < graph[v].size(); ++i)
        {
            long long to = edges[graph[v][i]].to;
            long long cap = edges[graph[v][i]].capacity - edges[graph[v][i]].flow;
            if (d[to] == -1 && cap > 0)
            {
                d[to] = d[v] + 1;
                queue.push_back(to);
            }
        }
    }
    return d[graph.size() - 1] != -1;
}

bool can_reach(long long v, vector<long long>& reachable)
{
    for (long long i = 0; i < reachable.size(); ++i)
        if (v == reachable[i])
            return true;

    return false;
}

long long dfs(long long v, long long flow, vector<vector<long long>>& graph, vector<edge>& edges, vector<long long>& ptr, vector<long long>& d)
{
    if (v == graph.size() - 1)
        return flow;

    while (ptr[v] < graph[v].size())
    {
        long long e = graph[v][ptr[v]];
        if (edges[e].capacity > edges[e].flow && d[edges[e].to] == d[v] + 1)
        {
            long long curr_flow = dfs(edges[e].to, std::min(flow, edges[e].capacity - edges[e].flow), graph, edges, ptr, d);
            if (curr_flow > 0)
            {
                edges[e].flow += curr_flow;
                edges[(e % 2) ? (e - 1) : (e + 1)].flow -= curr_flow;
                return curr_flow;
            }
        }
        ++ptr[v];
    }
    return 0;
}



int main()
{
    long long n, m;
    std::cin >> n >> m;

    vector<vector<long long>> graph(n);
    vector<edge> edges(m * 2);

    long long from, to, cap, edge_count = 0;

    for (long long i = 0; i < m; ++i)
    {
        std::cin >> from >> to >> cap;
        --from;
        --to;

        graph[from].push_back(edge_count);
        graph[to].push_back(edge_count + 1);
        edges[edge_count++] = { from, to, 0, cap };
        edges[edge_count++] = { to, from, 0, cap };
    }

    std::vector<long long> ptr(n);
    std::vector<long long> d(n);

    long long flow = 0;
    while (bfs(graph, edges, d))
    {
        ptr.assign(n, 0);
        long long curr_flow = 0;
        while (curr_flow = dfs(0, INF, graph, edges, ptr, d))
            flow += curr_flow;
    }
    vector<long long> reachable;
    vector<char> used(n, 0);
    deque <long long> queue;

    queue.push_back(0);
    used[0] = true;
    reachable.push_back(0);

    while (!queue.empty())
    {
        long long v = queue.front();
        queue.pop_front();
        for (long long i = 0; i < graph[v].size(); ++i)
        {
            if (!used[edges[graph[v][i]].to] && edges[graph[v][i]].capacity > edges[graph[v][i]].flow)
            {
                queue.push_back(edges[graph[v][i]].to);
                used[edges[graph[v][i]].to] = true;
                reachable.push_back(edges[graph[v][i]].to);
            }
        }
    }

    vector<long long> bad_edges;

    for (long long i = 0; i < 2 * m; ++i)
    {
        if (can_reach(edges[i].from, reachable) && !can_reach(edges[i].to, reachable))
            bad_edges.push_back(i / 2 + 1);
    }

    std::cout << bad_edges.size() << ' ' << flow << '\n';
    for (long long i = 0; i < bad_edges.size(); ++i)
        std::cout << bad_edges[i] << ' ';

}
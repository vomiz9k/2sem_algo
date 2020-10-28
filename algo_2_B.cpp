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

    long long biggest_tea = 0;

    vector<long long> tea(m);
    for (long long i = 0; i < m; ++i)
    {
        std::cin >> tea[i];
        if (tea[i] > biggest_tea)
            biggest_tea = tea[i];
    }


    long long count = 0;
    vector<vector<long long>> people(n);
    for (long long i = 0; i < n; ++i)
    {
        std::cin >> count;
        people[i].resize(count);
        for (long long j = 0; j < count; ++j)
        {
            std::cin >> people[i][j];
            --people[i][j];
        }
    }
    

    long long from, to, cap, edge_count = 0;
    vector<vector<long long>> graph(n + m + 2);
    vector<edge> edges;
    
    for (long long i = 0; i < n; ++i)
    {
        edges.push_back({ 0, i + 1, 0, 0 });
        edges.push_back({ i + 1, 0, 0, 0 });
        graph[0].push_back(edge_count++);
        graph[i + 1].push_back(edge_count++);
    }

    for (long long i = 0; i < n; ++i)
    {
        for (long long j = 0; j < people[i].size(); ++j)
        {
            edges.push_back({ i + 1, people[i][j] + n + 1, 0, INF });
            edges.push_back({ people[i][j] + n + 1, i + 1, 0, 0 });
            graph[i + 1].push_back(edge_count++);
            graph[people[i][j] + n + 1].push_back(edge_count++);
        }
    }

    for (long long i = 0; i < m; ++i)
    {
        edges.push_back({ i + n + 1, n + m + 1, 0, tea[i] });
        edges.push_back({ n + m + 1, i + n + 1, 0, 0 });
        graph[i + n + 1].push_back(edge_count++);
        graph[n + m + 1].push_back(edge_count++);
    }
    


    std::vector<long long> ptr(n + m + 2);
    std::vector<long long> d(n + m + 2);


    long long flow = 0;
    long long right = m * biggest_tea, left = 0, mid = (left + right) / 2;
    while (right > left + 1)
    {
        for (long long i = 0; i < 2 * n; i += 2)
            edges[i].capacity = mid;
        
        flow = 0;
        while (bfs(graph, edges, d))
        {
            ptr.assign(n + m + 2, 0);
            long long curr_flow = 0;
            while (curr_flow = dfs(0, INF, graph, edges, ptr, d))
                flow += curr_flow;
        }

        if (flow >= n * mid)
            left = mid;
        else
            right = mid;

        mid = (right + left) / 2;

        for (long long i = 0; i < edges.size(); ++i)
            edges[i].flow = 0;
    }


    for (long long i = 0; i < 2 * n; i += 2)
        edges[i].capacity = right;

    flow = 0;
    while (bfs(graph, edges, d))
    {
        ptr.assign(n + m + 2, 0);
        long long curr_flow = 0;
        while (curr_flow = dfs(0, INF, graph, edges, ptr, d))
            flow += curr_flow;
    }


    if (flow >= right * n)
        std::cout << right;
    else
        std::cout << right - 1; 
    

}
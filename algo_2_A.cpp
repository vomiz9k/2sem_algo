#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using std::deque;
using std::vector;

const int INF = 1 << 30;

struct edge
{
    int from;
    int to;
    int flow;
    int capacity;
};



bool bfs(vector<vector<int>>& graph, vector<edge>& edges, vector<int>& d)
{
    deque<int> queue;
    d.assign(graph.size(), -1);
    d[0] = 0;
    queue.push_back(0);
    int v = 0;
    while (!queue.empty())
    {
        v = queue.front();
        queue.pop_front();
        for (int i = 0; i < graph[v].size(); ++i)
        {
            int to = edges[graph[v][i]].to;
            int cap = edges[graph[v][i]].capacity - edges[graph[v][i]].flow;
            if (d[to] == -1 && cap > 0)
            {
                d[to] = d[v] + 1;
                queue.push_back(to);
            }
        }
    }
    return d[graph.size() - 1] != -1;
}

int dfs(int v, int flow, vector<vector<int>>& graph, vector<edge>& edges, vector<int>& ptr, vector<int>& d)
{
    if (v == graph.size() - 1) 
        return flow;

    while (ptr[v] < graph[v].size())
    {
        int e = graph[v][ptr[v]];
        if (edges[e].capacity > edges[e].flow && d[edges[e].to] == d[v] + 1)
        {
            int curr_flow = dfs(edges[e].to, std::min(flow, edges[e].capacity - edges[e].flow), graph, edges, ptr, d);
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
    int n, m;
    std::cin >> n >> m;

    vector<vector<int>> graph(n);
    vector<edge> edges(m * 2);

    int from, to, cap, edge_count = 0;

    for (int i = 0; i < m; ++i)
    {
        std::cin >> from >> to >> cap;
        --from;
        --to;

        graph[from].push_back(edge_count);
        graph[to].push_back(edge_count + 1);
        edges[edge_count++] = { from, to, 0, cap };
        edges[edge_count++] = { to, from, 0, 0 };
    }

    std::vector<int> ptr(n);
    std::vector<int> d(n);

    int flow = 0;
    while (bfs(graph, edges, d))
    {
        ptr.assign(n, 0);
        int curr_flow = 0;
        while (curr_flow = dfs(0, INF, graph, edges, ptr, d))
            flow += curr_flow;
    }

    std::cout << flow;
}

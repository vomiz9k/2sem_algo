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

int s, t;

bool bfs(vector<vector<int>>& graph, vector<edge>& edges, vector<int>& d)
{
    deque<int> queue;
    d.assign(graph.size(), -1);
    d[s] = 0;
    queue.push_back(s);
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
    return d[t] != -1;
}

int dfs(int v, int flow, vector<vector<int>>& graph, vector<edge>& edges, vector<int>& ptr, vector<int>& d)
{
    if (v == t)
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
    std::cin >> n >> m >> s >> t;
    --s;
    --t;

    vector<vector<int>> graph(n);
    vector<edge> edges(m * 2);

    int from, to, edge_count = 0;

    for (int i = 0; i < m; ++i)
    {
        std::cin >> from >> to;
        --from;
        --to;

        graph[from].push_back(edge_count);
        graph[to].push_back(edge_count + 1);
        edges[edge_count++] = { from, to, 0, 1 };
        edges[edge_count++] = { to, from, 0, 0 };
    }

    std::vector<int> ptr(n);
    std::vector<int> d(n);

    int flow = 0;

    while (bfs(graph, edges, d))
    {
        ptr.assign(n, 0);
        int curr_flow = 0;
        while (curr_flow = dfs(s, INF, graph, edges, ptr, d))
            flow += curr_flow;
    }

    if (flow < 2)
        std::cout << "NO";
    else
    {
        std::cout << "YES\n";
        for (int i = 0; i < 2; ++i)
        {
            int v = s;
            while (v != t)
            {
                std::cout << v + 1 << ' ';
                for (int i = 0; i < graph[v].size(); ++i)
                {
                    if (edges[graph[v][i]].flow > 0 && edges[graph[v][i]].capacity > 0)
                    {
                        edges[graph[v][i]].flow -= 1;
                        v = edges[graph[v][i]].to;
                        break;
                    }
                }
            }
            std::cout << t + 1 << '\n';
        }
    }




}

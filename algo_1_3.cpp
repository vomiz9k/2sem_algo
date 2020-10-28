#include <iostream>
#include <vector>

struct ride
{
    int start;
    int x_start;
    int y_start;
    int x_end;
    int y_end;
};

bool dfs(int v, std::vector<std::vector<int>>& graph, std::vector<char>& used, std::vector<int>& match)
{
    if (used[v] == true)
        return false;
    used[v] = true;
    for (int i = 0; i < graph[v].size(); ++i)
    {
        if (match[graph[v][i]] == -1 || dfs(match[graph[v][i]], graph, used, match))
        {
            match[graph[v][i]] = v;
            return true;
        }
    }
    return false;
}


int main()
{
    int n;
    std::cin >> n;
    std::vector <ride> tax(n);
    char dvoetochie;
    int hrs, mins;
    for (int i = 0; i < n; ++i)
    {
        
        std::cin >> hrs >> dvoetochie >> mins >> tax[i].x_start >> tax[i].y_start >> tax[i].x_end >> tax[i].y_end;
        tax[i].start = hrs * 60 + mins;
    }
    std::vector <std::vector<int>> graph(n);

    for(int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
        {
            if (tax[i].start + abs(tax[i].x_start - tax[i].x_end) + +abs(tax[i].y_start - tax[i].y_end)
                + abs(tax[j].x_start - tax[i].x_end) + abs(tax[j].y_start - tax[i].y_end) < tax[j].start)
            {
                graph[i].push_back(j);
            }
         }


    std::vector<char> used(n, false);
    std::vector<int> match(n, -1);


    for (int i = 0; i < n; ++i)
    {
        dfs(i, graph, used, match);
        for (int j = 0; j < n; ++j)
            used[j] = false;
    }

    int car_count = 0;

    for (int i = n - 1; i >= 0; --i)
    {
        int j = i;
        int old_j = i;
        if (!used[j])
        {
            used[j] = true;
            while (match[j] != -1)
            {
                old_j = j;
                j = match[j];
                used[j] = true;
                match[old_j] = -1;
            }
            ++car_count;
        }
    }
    std::cout << car_count;
}


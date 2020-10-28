#include <iostream>
#include <vector>

using std::vector;


bool dfs(int v, vector<vector<int>>& graph,vector<bool>& used, vector<int>& match)
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
	int n, m;
	std::cin >> n >> m;
	vector<vector<int>> graph(n);
	vector<bool> used(n, false);
	vector<int> match(m, -1);
	int value;
	
	for (int i = 0; i < n; ++i)
	{
		std::cin >> value;
		while (value != 0)
		{
			graph[i].push_back(value - 1);
			std::cin >> value;
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			used[j] = false;
		dfs(i, graph, used, match);
	}

	int count = 0;
	for (int i = 0; i < m; ++i)
		if (match[i] != -1) ++count;

	std::cout << count << '\n';

	for (int i = 0; i < m; ++i)
		if (match[i] != -1)
			std::cout << match[i] + 1 << ' ' << i + 1 << '\n';

}
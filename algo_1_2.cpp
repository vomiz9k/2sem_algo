#include <iostream>
#include <vector>
#include <string>
#include <fstream>


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
	
	
	int n, m, a, b;
	std::ifstream in("dominoes.in");
	std::ofstream out("dominoes.out");



	in >> n >> m >> a >> b;

	std::vector<std::string> field(n);

	for (int i = 0; i < n; ++i)
		in >> field[i];

	int cnt = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (field[i][j] == '*')
				++cnt;

	if (2 * b <= a)
		out << cnt * b;

	else
	{
		std::vector<std::vector<int>> graph(n * m);


		for (int i = 0; i < n; ++i)
			for (int j = i % 2; j < m; j += 2)
				if (field[i][j] == '*')
				{
					if (i > 0 && field[i - 1][j] == '*')
						graph[i * m + j].push_back((i - 1) * m + j);
					if (j > 0 && field[i][j - 1] == '*')
						graph[i * m + j].push_back(i * m + j - 1);
					if (j < m - 1 && field[i][j + 1] == '*')
						graph[i * m + j].push_back(i * m + j + 1);
					if (i < n - 1 && field[i + 1][j] == '*')
						graph[i * m + j].push_back((i + 1) * m + j);
				}

		std::vector<char> used(n * m, false);
		std::vector<int> match(n * m, -1);


		for (int i = 0; i < n; ++i)
			for (int j = i % 2; j < m; j += 2)
			{
				for (int k = 0; k < n * m; ++k)
					used[k] = false;
				dfs(i * m + j, graph, used, match);
			}
		int pair_count = 0;

		for (int i = 0; i < n; ++i)
			for (int j = (i + 1) % 2; j < m; j += 2)
				if (match[i * m + j] != -1) ++pair_count;

		out << pair_count * a + (cnt - pair_count * 2) * b;
	}
}
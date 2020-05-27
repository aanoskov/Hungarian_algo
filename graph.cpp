#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
using namespace std;


int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	unsigned int n;
	cin >> n;
	
	vector<int> par(n + 1, 0);
	vector<int> way(n + 1, 0);
	vector<vector<int>> g(n + 1, vector<int> (n + 1, 0));
	for (size_t i = 1; i <= n; i++)
	{
		for (size_t j = 1; j <= n; j++)
		{
			cin >> g[i][j];
		}
	}
	vector<int> u(n + 1, 0);
	vector<int> v(n + 1, 0);
	for (int i = 1; i < n + 1; i++)
	{
		par[0] = i;
		int prev_col = 0;
		int next_col;
		vector<int> minv(n + 1, INT_MAX);
		vector<bool>  used(n + 1, false);

		do {
			used[prev_col] = true;
			int new_row = par[prev_col];
			int delta = INT_MAX;
			for (int j = 1; j < n + 1; j++) {
				if (!used[j])
				{
					int current = g[new_row][j] - u[new_row] - v[j];
					if (current < minv[j]){
						minv[j] = current;
						way[j] = prev_col;
					}
					if (minv[j] < delta) {
						delta = minv[j];
						next_col = j;
					}
				}
			}
			for (int j = 0; j < n + 1; j++)
			{
				if (used[j]) {
					u[par[j]] += delta;
					v[j] -= delta;
				}
				else
					minv[j] -= delta;
			}
			prev_col = next_col;
		} while (par[prev_col] != 0);

		do
		{
			int j1 = way[prev_col];
			par[prev_col] = par[j1];
			prev_col = j1;
		} while (prev_col != 0);
	}
	v[0] *= -1;
	cout << v[0] << endl;
	fclose(stdin);
	fclose(stdout);
	getchar();
	return 0;
}

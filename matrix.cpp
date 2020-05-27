#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <climits>
#include <ctime>
#include <time.h>

using namespace std;


vector<vector<int>> g;
int sec_step(int& cnt, unsigned int& n)
{
	cnt = 0;
	int j1 = 0;
	vector<int> zeros_in_row(n, 0);
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			if (g[i][j] < 0)
				g[i][j] = 0;
			if (g[i][j] == 0)
				zeros_in_row[i] += 1;
		}
	}
	for (size_t k = 0; k < n; k++)
	{
		int str = -1;
		int minimum = INT_MAX;
		for (size_t i = 0; i < n; i++)
		{

			if ((zeros_in_row[i] < minimum) && (zeros_in_row[i] != 0))
			{
				minimum = zeros_in_row[i];
				str = i;
			}
		}
		
		bool first_zero = true;
		if (str != -1)
		{
			zeros_in_row[str] = 0;
			for (size_t j = 0; j < n; j++)
			{
				if (g[str][j] == 0)
				{
					if (!first_zero)
						g[str][j] = -1;
					else
					{
						cnt += 1;
						g[str][j] = -10;
						j1 = j;
						first_zero = false;
					}
				}
			}
			for (size_t i = 0; i < n; i++)
			{
				if (g[i][j1] == 0)
				{
					g[i][j1] = -1;
					zeros_in_row[i] -= 1;
				}
			}
		}
		else
			k = n;
	}
	return cnt;
}


int main()
{
	clock_t start = clock();
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	unsigned int n;
	cin >> n;

	//vector<vector<int>> g(n, vector<int>(n, 0));
	g.resize(n);
	vector<vector<int>> first_matrix(n);
	for (size_t i = 0; i < n; i++)
	{
		g[i].resize(n);
		for (size_t j = 0; j < n; j++)
		{
			cin >> g[i][j];
			first_matrix[i].push_back(g[i][j]);
		}
	}

	for (size_t i = 0; i < n; i++)
	{
		int minimum = INT_MAX;
		for (size_t j = 0; j < n; j++)
		{
			if (g[i][j] < minimum)
				minimum = g[i][j];
		}
		for (size_t j = 0; j < n; j++)
		{
			g[i][j] -= minimum;
		}
	}
	for (size_t j = 0; j < n; j++)
	{
		int minimum = INT_MAX;
		for (size_t i = 0; i < n; i++)
		{
			if (g[i][j] < minimum)
				minimum = g[i][j];
		}
		for (size_t i = 0; i < n; i++)
			g[i][j] -= minimum;
	}

	//==========while================
	int cnt = 0;
	
	while ((cnt = sec_step(cnt, n)) != n)
	{
		//cout << cnt << endl;
		//=============STEP3==================
		vector<bool> marked_rows(n, false);
		vector<bool> marked_cols(n, false);
		for (size_t i = 0; i < n; i++)
		{
			bool zero_in_row = false;
			for (size_t j = 0; j < n; j++)
			{
				if (g[i][j] == -10) {
					zero_in_row = true;
					break;
				}
			}
			if (!zero_in_row)
				marked_rows[i] = true;
		}
	
		bool marked;
		do {
			marked = false;
			for (size_t i = 0; i < n; i++)
			{
				if (marked_rows[i])
				{
					for (size_t j = 0; j < n; j++)
					{
						if ((g[i][j] == -1) && (!marked_cols[j]))
						{
							marked_cols[j] = true;
							marked = true;
						}
					}
				}
			}
			for (size_t i = 0; i < n; i++)
			{
				for (size_t j = 0; j < n; j++)
				{
					if ((g[i][j] == -10) && (marked_cols[j]) && (!marked_rows[i]))
					{
						marked_rows[i] = true;
						marked = true;
					}
				}
			}
		} while (marked);
		
		//=============STEP4=============
		int minelem = INT_MAX;
		for (size_t i = 0; i < n; i++)
		{
			if (marked_rows[i])
			{
				for (size_t j = 0; j < n; j++)
				{
					if ((!marked_cols[j]) && (g[i][j] < minelem))
						minelem = g[i][j];
				}
			}
		}
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				if ((marked_rows[i]) && (!marked_cols[j]))
					g[i][j] -= minelem;
				if ((!marked_rows[i]) && (marked_cols[j])) {
					if (g[i][j] < 0)
						g[i][j] = 0;
					g[i][j] += minelem;
				}
			}
		}
	}
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
			cout << g[i][j] << " ";
		cout << endl;
	}
	unsigned int result = 0;
	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			if (g[i][j] == -10)
				result += first_matrix[i][j];
		}
	}
	cout << result;
	//clock_t end = clock();
	//double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	//cout << "\ntime: " << seconds << endl << endl;
	fclose(stdin);
	fclose(stdout);
	getchar();
	return 0;
}

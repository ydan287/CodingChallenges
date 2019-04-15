#include <iostream>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <cstring>
#include <random>
using namespace std;


int R, C, D;
int grid[20][20];
int tc;

bool solve(int r, int c, int d, vector<pair<int,int>> vec) {
	if (d == R * C) {
		printf("Case #%d: POSSIBLE\n", tc);
		return true;
	}
	random_shuffle(vec.begin(), vec.end());
	for (auto p : vec) {
		int i = p.first;
		int j = p.second;
		if (d == 0) {}
		else if(grid[i][j] || i == r || j == c || i - j == r - c || i + j == r + c) {
			continue;
		}
		grid[i][j] = 1;
		if (solve(i, j, d + 1, vec)) {
			printf("%d %d\n", i + 1, j + 1);
			return true;
		}
		grid[i][j] = 0;
	}
	return false;
}

int main() {
	int t;
	cin >> t;
	for (tc = 1; tc <= t; tc++) {
		cin >> R >> C;
		vector<pair<int, int> > vec;
		for (int i = 0; i <R; i++)
		{
			for (int j = 0; j < C; j++)
			{
				vec.push_back({ i,j });
			}
		}
		D = min(R, C);
		memset(grid, 0, sizeof(grid));
		if (!solve(0, 0, 0, vec)) {
			printf("Case #%d: IMPOSSIBLE\n", tc);
		}
	}
	
	return 0;
}
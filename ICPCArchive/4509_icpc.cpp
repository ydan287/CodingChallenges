#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <unordered_map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
#define fr(i,n) for(ll i =0 ; i< n ; ++i)
#define DBL_MIN          2.2250738585072014e-308 // min positive value
#define INT_MAX       10000000    // maximum (signed) int value
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define ii(_i,_j) (_i)+(_j)*W

int W, H, w, h, G, E, w2, h2, t;
int dist[900];
bool reached[900];
int gr[30][30];
int hh[30][30];
int main(){
	while (1) {
		cin >> W >> H;
		if (!W && !H) break;
		fr(i, W*H) {
			dist[i] = INT_MAX;
			reached[i] = false;
		}
		vector<pair<pair<int, int>, int>> we;
		//vector<pair<pair<int, int>, int>> we = { { { 0,1 },1 },{ { 0,2 },2 },{ { 2,1 },-2 } };
		cin >> G;
		memset(gr, 0, sizeof(gr));
		while (G--) {
			cin >> w >> h;
			gr[w][h] = 1;
		}
		cin >> E;
		memset(hh, 0, sizeof(hh));
		while (E--) {
			cin >> w >> h >> w2 >> h2 >> t;
			we.push_back({ {ii(w,h),ii(w2,h2)},t });
			hh[w][h] = 1;
		}

		fr(i, W) {
			fr(j, H) {
				if (gr[i][j] || hh[i][j] || (i==W-1 && j == H-1)) continue;
				if (i + 1 < W && !gr[i + 1][j]) we.push_back({ { ii(i,j),ii(i + 1,j) }, 1 });
				if (i - 1 >= 0 && !gr[i - 1][j]) we.push_back({ { ii(i,j),ii(i - 1,j) }, 1 });
				if (j + 1 < H && !gr[i][j + 1]) we.push_back({ { ii(i,j),ii(i ,j + 1) }, 1 });
				if (j - 1 >= 0 && !gr[i][j - 1]) we.push_back({ { ii(i,j),ii(i ,j - 1) }, 1 });
			}
		}
		int source = 0;
		dist[source] = 0;
		reached[source] = true;
		bool change = 0;
		for (int i = 0; i < W*H + 1; i++)
		{
			change = 0;
			for (auto& w_ed : we)
				if (dist[w_ed.first.first] < INT_MAX && dist[w_ed.first.second] > dist[w_ed.first.first] + w_ed.second)
				{
					change = 1;
					dist[w_ed.first.second] = dist[w_ed.first.first] + w_ed.second;
				}
		}
		if (change == 0)
		{
			if (dist[ii((W - 1), (H - 1))] >= INT_MAX)
				cout << "Impossible" << endl;
			else
				cout << dist[ii((W - 1), (H - 1))] << endl;
		}
		else
		{
			cout << "Never" << endl;
		}
	}
		

	return 0;
}
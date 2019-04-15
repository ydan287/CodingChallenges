/*
Authors Yoav Danieli and his team.

*/
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
#include <sstream>
#include <vector>
#include <numeric>


#define REP(i,a,b) for(auto i = a; i<b ; ++i)
#define RREP(i,a,b) for(auto i = a ; i>=b ; --i)
#define TR(c,it) for(auto it = (c).begin() ; it != (c).end() ; ++it)
#define INF 2e9
#define EPS 1e-9
#define NINF -2e9
#define MP make_pair
#define PB push_back
#define all(a) (a).begin(), (a).end()
#define sz(v) (ll)(v).size()
#define pb push_back
#define sec second
#define fst first

using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<ll, pi> ppi;
typedef vector<ll> vi;
typedef vector<vi> graph;

inline string IntToStr(int x) { ostringstream ss; ss << x; return ss.str(); }
inline int StrToInt(string x) { int i; istringstream iss(x); iss >> i; return i; }

struct PT {
	int x, y;
};

struct SEG {
	PT p, q;
};

PT operator - (PT a, PT b) {
	PT c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	return c;
}

int operator * (PT a, PT b) {
	int c = a.x * b.y - b.x * a.y;
	return c == 0 ? 0 : c / abs(c);
}

bool intersect(SEG a, SEG b) {
	if (a.p.x == b.p.x && a.p.y == b.p.y) {
		return false;
	}
	if (((b.p - a.p)*(a.q - a.p)) * ((b.q - a.p)*(a.q - a.p)) > 0) return false;
	if (((a.p - b.p)*(b.q - b.p)) * ((a.q - b.p)*(b.q - b.p)) > 0) return false;
	return true;
}

vi visible;
graph g;

bool dfs(int n, int s) {
	if (visible[n] != -1) {
		return visible[n] == s;
	}
	visible[n] = s;
	for (auto& i : g[n]) {
		if (!dfs(i, 1 - s)) {
			return false;
		}
	}
	return true;
}

int main() {
	int w, p;
	while (cin >> w >> p) {
		vector<PT> wells(w);
		for (int i = 0; i < w; i++) {
			cin >> wells[i].x >> wells[i].y;
		}
		vector<SEG> pipes(p);
		for (int i = 0; i < p; i++) {
			int well;
			cin >> well >> pipes[i].q.x >> pipes[i].q.y;
			pipes[i].p = wells[well - 1];
		}
		g = graph(p);
		for (int i = 0; i < p; i++) {
			for (int j = 0; j < p; j++) {
				if (intersect(pipes[i], pipes[j])) {
					g[i].push_back(j);
				}
			}
		}
		bool possible = true;
		visible = vi(p, -1);
		for (int i = 0; i < p; i++) {
			if (visible[i] == -1 && !dfs(i, 0)) {
				possible = false;
				break;
			}
		}
		cout << (possible ? "possible" : "impossible") << endl;
	}
	return 0;
}

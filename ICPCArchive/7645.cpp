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
#include <valarray>


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
	double x, y;
	PT(double x = 0, double y = 0) : x(x), y(y) {}
	bool operator<(const PT& p) const{
		return (x*p.y - y * p.x) > 0;
	}
};

map<PT, pair<int, int>> mp;
int n;
int main() {
	while (cin >> n) {
		mp.clear();
		mp[PT(0.0, 1.0)];
		mp[PT(-1.0, 0.0)];
		PT maria;
		//better than maria and lesser than maria
		int q1 = 0, q2 = 0, q3 = 0, q4 = 0, same =0;
		cin >> maria.x >> maria.y;
		REP(i, 0, n - 1) {
			PT tmp;
			cin >> tmp.x >> tmp.y;
			if		(maria.x > tmp.x && maria.y > tmp.y) q3++;
			else if (maria.x < tmp.x && maria.y < tmp.y) q1++;
			else if (maria.x == tmp.x && maria.y == tmp.y) same++;
			else { 
				tmp.x -= maria.x; tmp.y -= maria.y; // centrilize
				if (tmp.x >= 0 && tmp.y <= 0) {
					tmp.y *= -1; // change to q2
					tmp.x *= -1;
					mp[tmp].second++;
					q4++;
				}
				else if (tmp.x <= 0 && tmp.y >= 0) {
					mp[tmp].first++;
					q2++;
				}
			}
		}
		int best = 1 + q1 + q4;
		int worst = n- q3- q2;
		for (auto p : mp) {
			best = min(best, 1 + q1 + q4 - p.second.second);
			worst = max(worst, n - q3 - q2 + p.second.first);
			q4 += p.second.first - p.second.second;
			q2 += p.second.second - p.second.first;
		}
		cout << best << " " << worst << endl;
	}
	return 0;
}

/*
7
10 10
11 10
10 11
10 9
9 10
9 9
11 11
*/
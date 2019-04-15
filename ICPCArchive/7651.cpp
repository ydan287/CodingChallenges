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

ll H, D;

struct myhash
{
	std::size_t operator()(const vector<ll>& v) const
	{
		size_t ret = 0;
		REP(i, 0, v.size() - 1) {
			ret ^= v[i];
		}
		return ret;
	}
};

unordered_map < vector < ll >, ll, myhash > um;

set<ll> res;

ll calc(vector<ll> v) {
	sort(v.begin(), v.end());
	if (um[v]) {
		return um[v];
	}
	else {
		bool flg = true;
		REP(i, 0, v.size()) {
			if (v[i]) {
				flg = false;
				break;
			}
		}
		if (flg) {
			um[v] = 1;
			return 1;
		}
		ll sum = 0;
		REP(i, 0, v.size()) {
			if (v[i] == 0) continue;
			v[i] -= 1;
			sum += calc(v);
			v[i] += 1;
		}
		um[v] = sum;
		return sum;
	}
}

void recur(vector<ll>& v,int i, int last, int total) {
	if (i == D) {
		res.insert(calc(v));
		return;
	}
	for (v[i] = i + 1 == D ? total : last; v[i] <= total; ++v[i]) {
		recur(v, i + 1, v[i], total - v[i]);
	}
}

int main() {
	while (cin >> D >> H) {
		um.clear();
		res.clear();
		vector<ll> v(D,0);
		recur(v, 0, 0, H-1);
		for (auto it : res) {
			cout << it << endl;
		}
	}

	return 0;
}
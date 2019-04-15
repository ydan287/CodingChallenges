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
#include <unordered_set>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>

#define REP(i,a,b) for(auto i = a; i<b ; ++i)
#define TR(c,it) for(auto it = (c).begin() ; it != (c).end() ; ++it)
#define INF 2e9
#define NINF -2e9
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define EPS 1e-10

//memset(dp_memo, -1, sizeof dp_memo); // useful to initialize DP memoization table
//memset(arr, 0, sizeof arr); // useful to clear array of integers
//swapping a and b: a^=b; b^=a; a^=b;
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

struct _ed {
	ll to;
	ll ac;
	ll ap;
	_ed(ll s, ll a, ll b) : to(s), ac(a), ap(b) {}
};

unordered_map<string, ll> dishes;
vector<vector<_ed> > adj;
ll v, e;
vector<ll> visible;
vector<ll> ord;
vector<ll> rord;
vector<pair<ll, ll > > wei;
vector<vector<pair<ll, ll> > > f;
int p;

int fg;

void dfs_for_TS(ll a)
{
	if (visible[a] == 1) fg = 1;//circle found
	if (visible[a] != 0) return;
	visible[a] = 1;
	for (auto& x : adj[a])
		dfs_for_TS(x.to);
	visible[a] = 2;
	ord[p] = a;
	rord[a] = p--;
}
bool TS()
{
	visible = vector<ll>(v, 0);
	ord = vector<ll>(v, 0);
	rord = vector<ll>(v, 0);
	wei = vector<pair<ll, ll> >(v, { INF,INF });
	fg = 0;
	p = v - 1;
	for (ll i = 0; i<v; i++) {
		if (visible[i] == 0)
			dfs_for_TS(i);
	}
	if (fg != 1)
		return true;
	return false;
}

int main() {

	ll B, N, p, c;
	string main, base, ingr;
	while (cin >> B >> N) {
		ll indx = 1;
		if (N == 0) {
			printf("0\n0\n");
			continue;
		}
		dishes.clear();
		adj.clear();
		REP(i, 0, N) {
			cin >> main >> base >> ingr >> c >> p;
			if (!dishes[base]) { 
				dishes[base] = indx++;
				adj.emplace_back();
			}
			if (!dishes[main]) {
				dishes[main] = indx++; 
				adj.emplace_back();
			}
			adj[dishes[base] - 1].emplace_back(_ed(dishes[main]-1,c,p));
		}
		v = dishes.size();
		TS();
		REP(i, 0, v) {
			if (wei[i].F == INF) wei[i] = { 0,0 };
			for (auto& var : adj[ord[i]]) {
				if (wei[rord[var.to]].F > wei[i].F + var.ac
				|| (wei[rord[var.to]].F == wei[i].F + var.ac
					&& wei[rord[var.to]].S < wei[i].S + var.ap)) {
					wei[rord[var.to]].F = wei[i].F + var.ac;
					wei[rord[var.to]].S = wei[i].S + var.ap;
				}
			}
		}
		
		f = vector<vector<pair<ll, ll> > >(B+1, vector<pair<ll, ll> >(v));
		REP(b, 0, B+1) {
			REP(n,0,v) {
				if (b == 0) {
					f[b][n] = { 0,0 };
					continue;
				}
				if (wei[n].F > b) {
					if (n == 0) f[b][n] = { 0,0 };
					else f[b][n] = f[b][n - 1];
					continue;
				}
				if (n == 0) {
					f[b][n] = wei[n];
					continue;
				}
				f[b][n] = (f[b][n-1].S >= f[b-wei[n].F][n-1].S + wei[n].S)?
					f[b][n - 1] : MP(f[b - wei[n].F][n - 1].F + wei[n].F, f[b - wei[n].F][n - 1].S + wei[n].S);
			}
		}

		printf("%lld\n%lld\n", f[B][v - 1].S, f[B][v - 1].F);
		//cout << f[B][v - 1].S << '\n' << f[B][v - 1].F << '\n';
		
	}
	return 0;
}
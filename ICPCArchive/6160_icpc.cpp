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

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

unordered_map<ll, int> um;
struct eq
{
	ll a;
	char op;
	ll b;
	ll c;
	eq(ll a, char op, ll b, ll c) : a(a), op(op), b(b), c(c) {}
};
vector<eq> eq_list;
bool flag = false;
ll best;
vector<eq> best_list;
//char opr[] = { '+', '-', '*', '/' };
ll tar;
void solve() {
	pair<ll, int> arr[6];
	int i = 0;
	for (auto it : um) {
		if (it.first == tar) {
			best = tar;
			best_list = eq_list;
			flag = true;
			return;
		}
		if (abs(it.first - tar) < abs(best-tar)) {
			best = it.first;
			best_list = eq_list;
		}
		arr[i++] = it;
	}
	if (um.size() == 1) return;
	for (int it = 0; it < i; ++it){//auto it = um.begin(); it != um.end(); ++it) {
		if (flag) return;
		if (arr[it].second < 1) continue;
		ll a = arr[it].first;
		for (int jt = it; jt < i ; ++jt) {
			if (flag) return;
			if (arr[jt].second < 1) continue;
			if (it == jt && arr[it].second < 2) continue;
			ll b = arr[jt].first;
			// +
			{	
				if (!a || !b) continue;
				um[a +b] += 1;
				if (!--um[a]) um.erase(a);
				if (!--um[b]) um.erase(b);
				eq_list.push_back(eq(a, '+', b, a+b));
				solve();
				if (flag) return;
				eq_list.pop_back();
				um[a] += 1;
				um[b] += 1;
				if (!--um[a+b]) um.erase(a+b);
			}
			// -
			{
				if (a<b) {
					swap(a, b);
				}

				um[a-b] += 1;
				if (!--um[a]) um.erase(a);
				if (!--um[b]) um.erase(b);
				eq_list.push_back(eq(a, '-', b, a - b));
				solve();
				if (flag) return;
				eq_list.pop_back();
				um[a] += 1;
				um[b] += 1;
				if (!--um[a - b]) um.erase(a-b);
			}
			// *
			{
				um[a*b] += 1;
				if (!--um[a]) um.erase(a);
				if (!--um[b]) um.erase(b);
				eq_list.push_back(eq(a, '*', b, a * b));
				solve();
				if (flag) return;
				eq_list.pop_back();
				um[a] += 1;
				um[b] += 1;
				if (!--um[a * b]) um.erase(a * b);
			}
			// /
			{
				if (a < b) {
					swap(a, b);
				}
				if (b==0 || a%b) continue;
				um[a / b] += 1;
				if (!--um[a]) um.erase(a);
				if (!--um[b]) um.erase(b);
				eq_list.push_back(eq(a, '/', b, a / b));
				solve();
				if (flag) return;
				eq_list.pop_back();
				um[a] += 1;
				um[b] += 1;
				if (!--um[a / b]) um.erase(a / b);
			}
		}
	}
}

int main()
{
	int TC;
	cin >> TC;
	while (TC--) {
		um.clear();
		eq_list.clear();
		best_list.clear();
		best = 1000000000;
		flag = false;
		fr(i, 6) {
			ll tmp;
			cin >> tmp;
			um[tmp] += 1;
		}
		cin >> tar;
		solve();
		cout << "Target: " << tar << endl;
		for (auto var : best_list) {
			printf("%lld %c %lld = %lld\n", var.a, var.op, var.b, var.c);
		}
		cout << "Best approx: " << best << endl;
		if (TC) cout << endl;
	}
	return 0;
}
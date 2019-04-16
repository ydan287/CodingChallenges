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
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;


int main() {
	ll TC;
	while (cin >> TC) {
		while (TC--) {
			ll n;
			scanf("%lld", &n);
			vector<ll> canvasses;
			for (ll i = 0; i < n; ++i) {
				ll tmp;
				scanf("%lld", &tmp);
				canvasses.push_back(tmp);
			}
			priority_queue<ll, vector<ll>, greater<ll> > pq(canvasses.begin(), canvasses.end());
			ll sum = 0;
			while (1) {
				ll a = pq.top();
				pq.pop();
				if (pq.empty()) break;
				ll b = pq.top();
				pq.pop();
				sum += a + b;
				pq.push(a + b);
			}
			printf("%lld\n", sum);
		}
	}
	return 0;
}
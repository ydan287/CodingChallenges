
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

struct pair_compare {
	bool operator() (pair<ll, ll> a, pair<ll, ll>b) {
		if (a.first == b.first) return a.second < b.second;
		return a.first > b.first;
	}

};

int main(int argc, char **argv) {
	int TC;
	scanf("%d", &TC);
	vector<ll> res;

	while (TC--) {
		ll p, n, sum=0;
		scanf("%lld %lld", &p, &n);
		priority_queue<pair<ll, ll>, vector<pair<ll, ll> >, pair_compare > partners;
		vector<ll> res;
		for (ll i = 0; i < n; ++i) {
			ll limit;
			scanf("%lld", &limit);
			sum += limit;
			pair<ll, ll> pr(limit,i);
			partners.push(pr);
			res.push_back(0);
		}
		if (sum < p) {
			printf("IMPOSSIBLE\n");
			continue;
		}
		while (!partners.empty()) {
			ll mini = min(partners.top().first, (p / n));
			res[partners.top().second] = mini;
			partners.pop();
			n--;
			p -= mini;
		}
		for (auto i = 0; i < res.size(); ++i) {
			printf("%lld", res[i]);
			if (i + 1 < res.size()) {
				printf(" ");
			}
		}
		if (TC >= 0) {
			printf("\n");
		}
	}

	return 0;
}
/*
3
20 4
10 10 4 4
7 3
1 1 4
34 5
9 8 9 9 4

*/
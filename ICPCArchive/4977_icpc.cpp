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

int main(int argc, char **argv) {
	int TC = 0;
	scanf("%d", &TC);
	while (TC--)
	{
		bool possible = true;
		ll n, m, l=0;
		scanf("%lld %lld", &n, &m);
		vector<pair<ll,ll> > forecast;
		vector<ll> days(n+1, 0);
		set<pair <ll,ll> > zeros;
		vector<ll> dragon;
		for (ll i = 0; i < m; i++)
		{
			ll day;
			scanf("%lld", &day);
			if (!possible) continue;
			if (day == 0) {
				//pair<ll, ll> tmp(n + 1, day);
				//forecast.push_back(make_pair(i,day));
				zeros.insert(make_pair(i,l));
				l++;
				dragon.push_back(0);
			}
			else {
				if (zeros.empty()) {
					possible = false;
					continue;
				}
				auto it = zeros.lower_bound(make_pair(days[day],0));
				if (it == zeros.end()) {
					possible = false;
					continue;
				}
				dragon[(*it).second] = day;
				//forecast.push_back(make_pair((*it).first, day));
				days[day] = i;
				zeros.erase(it);
			}
			
		}
		if (possible) {
			printf("YES\n");
			for (ll i = 0; i < l; ++i) {
				if (i > 0) printf(" ");
				printf("%lld", dragon[i]);
			}
		}
		else {
			printf("NO");
		}
		if (TC > 0) printf("\n");
	}
	printf("\n");
	return 0;
}
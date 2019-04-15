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
#define fr(i, n) for(auto i=0 ; i < n ; ++i)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
ll indx;
map<ll, ll> table;
void check(string mobile, ll depth){
	ll i=0;
	if (mobile[indx] == '[') {
		indx++;
		check(mobile,depth +1);
	}
	else {
		while (mobile[indx + i] != ',') {
			++i;
		}
		string val1_str = mobile.substr(indx, i);
		ll tmp = stoll(val1_str);
		table[tmp<<depth] += 1;
	}
	indx = indx + i + 1;
	i=0;
	if (mobile[indx] == '[') {
		indx++;
		check(mobile,depth+1);
	}
	else {
		while (mobile[indx + i] != ']') {
			++i;
		}
		string val2_str = mobile.substr(indx, i);
		ll tmp = stoll(val2_str);
		table[tmp<<depth] += 1;
	}
	indx = indx + i + 1;
	//return wt_chng;
}

int main() {
	ll TC;
	scanf("%lld", &TC);
		while (TC--) {
			indx = 0;
			string mobile;
			cin >> mobile;
			if (mobile[0] != '[') {
				printf("0\n");
				continue;
			}
			indx = 1;
			check(mobile,1);
			ll sum=0, best_fit=0;
			for (auto i = table.begin(); i != table.end(); ++i){
				sum += i->second;
				best_fit = (best_fit >= i->second) ? best_fit : i->second;
			}			
			printf("%lld\n",sum - best_fit);
			table.clear();
		}
	return 0;
}
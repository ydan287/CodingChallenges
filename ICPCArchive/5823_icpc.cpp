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
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;


double binom(double up, double down) {
	double res=1;
	for (double k = up-down+1 ; k <= up; ++k) {
		res *= k;
	}
	for (double k = 1; k <= down; ++k) {
		res /= k;
	}
	return res;
}


double bin_dist(double up, double down, double p) {
	return binom(up, down)*pow(p, down)*pow(1 - p, up - down);
}


double infinte_sigma(double p) {
	double last = p * p;
	double res=0;
	while (last > DBL_MIN) {
		res += last;
		last *= p * (1-p)*2;
	}
	return res;
}


int main() {
	double p;
	while (1) {
		cin >> p;
		if (p == -1) break;
		double game = bin_dist(4, 4, p) + 
			bin_dist(4, 3, p)*p + 
			bin_dist(5, 3, p)*p + 
			bin_dist(6, 3, p)*infinte_sigma(p);
		
		double tie_break =
			//7-0
			bin_dist(7, 7, p) +
			//7-1
			bin_dist(7, 6, p)*p +
			//7-2
			bin_dist(8, 6, p)*p +
			//7-3
			bin_dist(9, 6, p)*p +
			//7-4
			bin_dist(10, 6, p)*p +
			//7-5
			bin_dist(11, 6, p)*p +
			//any other:
			bin_dist(12, 6, p)*infinte_sigma(p);
		
		double _set =
			//6-0
			bin_dist(6, 6, game) +
			//6-1
			bin_dist(6, 5, game)*game +
			//6-2
			bin_dist(7, 5, game)*game +
			//6-3
			bin_dist(8, 5, game)*game +
			//6-4
			bin_dist(9, 5, game)*game +
			//7-5
			bin_dist(10, 5, game)*game*game +
			// 6-6 *tiebreak
			bin_dist(10, 5, game)*bin_dist(2, 1, game) *tie_break;

		double match = bin_dist(2, 2, _set) + bin_dist(2, 1, _set)*_set;
		
		printf("%.11lf %.11lf %.11lf\n",game, _set, match);


	}

	return 0;
}
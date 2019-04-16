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

#define fr(i,n) for(int i =0 ; i< n ; i+=1)
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
double sections[1000][2];
int main() {
	double n, t;
	while (cin >> n >> t) {
		double right = 1e9;
		double left = -1e9;
		fr(i, n) {
			cin >> sections[i][0] >> sections[i][1];
			left = max(left, -sections[i][1]);
		}

		while (right - left > 1e-9) {
			double mid = (right + left) / 2;
			double sum = 0;
			fr(i, n) sum += sections[i][0] / (sections[i][1] + mid);
			if (t >= sum) {
				right = mid;
			}
			else {
				left = mid;
			}
		}

		printf("%.9lf\n", left);
	}
	return 0;
}
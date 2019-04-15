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

double check(vector<double> xs, vector<double> ys, double x) {
	double value = 0;
	for (int i = 0; i < xs.size(); ++i) {
		double tmp2 = pow(xs[i] - x, 2) + pow(ys[i],2);
		if (value < tmp2) value = tmp2;
	}
	return sqrt(value);
}

int main(int argc, char **argv) {
	int c = 0;
	while (1) {
		int n;
		scanf("%d", &n);
		if (n == 0) break;
		vector<double> xs;
		vector<double> ys;
		for (int i = 0; i < n; ++i) {
			double x, y;
			scanf("%lf %lf", &x, &y);
			xs.push_back(x);
			ys.push_back(y);
		}
		auto tmp = minmax_element(xs.begin(), xs.end());
		double left = *(tmp.first);
		double right = *(tmp.second);
		while (abs(right - left) > 0.0000000001) {
			double mid_left = (2 * left + right) / 3;
			double mid_right = (left + 2 * right) / 3;
			if (check(xs, ys, mid_left) <= check(xs, ys, mid_right)) {
				right = mid_right;
			}
			else {
				left = mid_left;
			}
		}
		if (c++ > 0) printf("\n");
		printf("%.9lf %.9lf", left, check(xs, ys, left));
	}
	return 0;
}
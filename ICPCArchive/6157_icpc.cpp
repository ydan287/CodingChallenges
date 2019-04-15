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
#define TR(c,it) for(auto it = (c).begin() ; it != (c).end() ; ++it)
#define INF 2e9
#define NINF -2e9
#define F first
#define S second
#define MP make_pair
#define PB push_back

//memset(dp_memo, -1, sizeof dp_memo); // useful to initialize DP memoization table
//memset(arr, 0, sizeof arr); // useful to clear array of integers
//swapping a and b: a^=b; b^=a; a^=b;
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;


vector<double> water;
int d;
double p;
int main() {
	string s;
	bool first = true;
	while (getline(cin, s)) {
		stringstream ss(s);
		ss >> d >> p;
		water.clear();
		int i;
		int num = 0;
		while (ss >> i) {
			water.emplace_back(i); num++;
		}
		for (i = 0; i < num; ++i) {
			if (water[i] > p) break;
		}
		if (i == 0) {
			cout << "The spider is going to fall!\n";
			continue;
		}
		if (i < num) {
			cout << d - i + 1 << "\n"; continue;
		}
		if (num == d + 1) {
			cout << "The spider may fall!\n"; continue;
		}
		double dx, dy, det;
		det = water[num - 4] * water[num - 2] - water[num - 3] * water[num - 3];
		dx = water[num - 2] * water[num - 2] - water[num - 3] * water[num - 1];
		dy = water[num - 4] * water[num - 1] - water[num - 3] * water[num - 2];
		//return make_pair(dx / d, dy / d);
		//double determinant = water[num-4] * water[num-2] - water[num-3] * water[num-3];
		double x = dx / det, y = dy / det;
		double b = water.back(); water.pop_back();
		double a = water.back(); water.pop_back();
		while (i < d + 1) {
			double tmp = x * a + y * b;
			if (tmp - p > 1e-8) {
				break;
			}
			a = b;
			b = tmp;
			i++;
		}
		if (i < d + 1) {
			cout << d - i + 1 << "\n";
			continue;
		}
		cout << "The spider may fall!\n"; continue;

	}

	return 0;
}
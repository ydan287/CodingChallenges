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

struct PT {
	double x;
	double y;
};

struct SEG {
	PT p1;
	PT p2;
};

//intput 3 points a -> b -> c
//output: cross prduct:
//	if cross > 0 - a->b->c is a left turn
//	if cross < 0 - a->b->c is a right turn
// if cross = 0 - a-> b-> c is one segment - c is on the segment a-b.

double ccw(PT a, PT b, PT c) {
	return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}

double intresection(SEG s1, SEG s2) {
	if (ccw(s1.p1, s1.p2, s2.p1)*ccw(s1.p1, s1.p2, s2.p2) < 0
		&& ccw(s2.p1, s2.p2, s1.p1)*ccw(s2.p1, s2.p2, s1.p2) < 0) {
		//intersection is proper - full intersection.
	}
	else if (ccw(s1.p1, s1.p2, s2.p1) == 0
		&& ccw(s1.p1, s1.p2, s2.p2) == 0
		&& ccw(s2.p1, s2.p2, s1.p1) == 0
		&& ccw(s2.p1, s2.p2, s1.p2) == 0) {
		// the two segments are colliner. same line.
	}
}


int main(){
	
	return 0;
}
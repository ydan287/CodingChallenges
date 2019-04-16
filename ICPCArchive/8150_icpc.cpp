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
	int W;
	//int c = 0;
	while (scanf("%d", &W) != EOF) {
		int N;
		scanf("%d", &N);
		ll sum = 0;
		for (int i = 0; i < N; ++i) {
			int w, l;
			scanf("%d %d", &w, &l);
			sum += w * l;

		}
		//if (c++) printf("\n");
		printf("%ld\n", sum/W);

	}
}
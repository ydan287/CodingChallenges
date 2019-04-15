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
	int a, b;
	int c = 0;
	while (scanf("%d %d", &a, &b) != EOF)
	{
		if (c > 0) {
			printf("\n");
		}
		vector<int> hist(a +b+1 , 0);
		for (int i = 1; i <= a; ++i) {
			for (int j = 1; j <= b; ++j) {
				//printf("%d  %d\n", i, j);
				hist[i + j] += 1;
			}
		}
		int maxi= 0;
		for (int i = 0; i < hist.size(); i++) {
			maxi = max(hist[i], maxi);
		}
		for (int i = 0; i < hist.size(); ++i) {
			
			if (hist[i] == maxi) { 
				if (c++ > 0) {
					printf("\n");
				}
				printf("%d", i);
			}
		}
	}
	printf("\n");
	return 0;
}





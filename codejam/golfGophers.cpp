#include <iostream>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <random>
#include <numeric>
#include <vector>
#include <execution>

using namespace std;

// recursively calculate GCD of two numbers
int gcd(int a, int b)
{
	if (b == 0)
		return a;

	return gcd(b, a % b);
}

// function to determine if solution is possible or not
bool check(int b[], int n)
{
	for (int x = 0; x < n; x++)
	{
		for (int y = x + 1; y < n; y++)
			if (gcd(b[x], b[y]) != 1)
				return true;
	}
	return false;
}

// Chinese Remainder Theorem
int evaluate(int a[], int b[], int n)
{
	vector<int> Minv(n);
	int q, r, r1, r2, t, t1, t2;

	int total = 1;
	for (int k = 0; k < n; k++)
		total *= b[k];

	for (int k = 0; k < n; k++)
	{
		r1 = b[k];
		r2 = total / b[k];
		t1 = 0;
		t2 = 1;

		while (r2 > 0)
		{
			q = r1 / r2;
			r = r1 - q * r2;
			r1 = r2;
			r2 = r;

			t = t1 - q * t2;
			t1 = t2;
			t2 = t;
		}

		if (r1 == 1)
			Minv[k] = t1;

		if (Minv[k] < 0)
			Minv[k] = Minv[k] + b[k];
	}

	int x = 0;
	for (int k = 0; k < n; k++)
		x += (a[k] * total * Minv[k]) / b[k];

	return x;
}

int main() {
	int T,N,M;
	cin >> T, N, M;
	int num[7] = { 2, 3, 5, 7, 11, 13, 17};
	int rem[7] = { 0 };
	for (int tc = 1; tc <= T; tc++) {
		for (int j = 0; j < 7; ++j) {
			for (int i = 0; i < 18; ++i) {
				cout << num[j] << endl;
				fflush(stdout);
			}
			for (int i = 0; i < 18; ++i) {
				int tmp;
				cin >> tmp;
				if (tmp == -1) {
					return 0;
				}
				rem[j] += tmp;
			}
			rem[j] %= num[j];
		}
		cout << evaluate(num, rem, 7);
		
		int tmp;
		cin >> tmp;
		if (tmp = -1) {
			return 0;
		}
	}
		
	
	return 0;
}
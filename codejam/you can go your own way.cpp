
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
#define ADD(a, b) a = (a + (ll)b) % mod
#define MUL(a, b) a = (a * (ll)b) % mod
#define MAX(a, b) a = max(a, b)
#define MIN(a, b) a = min(a, b)
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define rer(i, a, b) for(int i = (a) - 1; i >= (b); i--)
#define all(a) (a).begin(), (a).end()
#define sz(v) (int)(v).size()
#define pb push_back
#define sec second
#define fst first
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<int, pi> ppi;
typedef vector<ll> vi;
typedef vector<vi> mat;

mat A;
mat B;
int N;

string dfs() {
	int r = 0, c = 0;
	string res = "";
	while (true) {
		if (r == N - 1 && c == N - 1)
			break;

		if (r < N - 1 &&(!A[r][c] || !A[r + 1][c]) && B[r][c] < 1) {
			res = res + "S";
			B[r][c] = 1;
			r++;
		}
		else if (c < N - 1 && (!A[r][c] || !A[r][c + 1]) && B[r][c] < 2) {
			B[r][c] = 2;
			res = res + "E";
			c++;
		}
		else {
			char last = res.back();
			res.pop_back();
			if (last == 'S') {
				r--;
			}
			else {
				c--;
			}
		}
	}
	return res;
}

int main() {
	int tc;
	cin >> tc;
	for (int i = 1; i <= tc; i++)
	{
		string lydia;
		cin >> N >> lydia;
		A = mat(N, vi(N,0));
		B = mat(N, vi(N, 0));
		int r = 0;
		int c = 0;
		A[r][c] = 1;
		for (int i = 0; i < lydia.length(); i++)
		{
			if (lydia[i] == 'S') {
				r++;
			}
			else {
				c++;
			}
			A[r][c] = 1;
		}
		cout << "Case #" << i << ": " + dfs() << endl;
	}
	return 0;
}
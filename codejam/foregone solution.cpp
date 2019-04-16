
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



int main() {
	int tc;
	cin >> tc;
	for (int i = 1; i <= tc; i++)
	{
		string N;
		cin >> N;
		string A = N;
		string B = "";
		bool flag = false;
		for (int i = 0; i < A.length(); ++i) {
			if (A[i] == '4') {
				B = B + "2";
				A[i] = '2';
				flag = true;
				continue;
			}
			if (flag) {
				B = B + '0';
			}
		}
		cout << "Case #"  << i  <<": " + A + " " + B << endl;
	}
	
	return 0;
}
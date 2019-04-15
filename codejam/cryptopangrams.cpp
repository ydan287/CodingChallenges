
#include <iomanip>
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

ll gcd(ll a, ll b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main() {
	int tc;
	cin >> tc;
	for (int j = 1; j <= tc; j++)
	{
		ll N;
		ll L;
		cin >> N >> L;
		//bigint N(tmp);
		vector<ll> arr(L);
		vector<ll> plain(L);
		set<ll>	primes;
		for (ll i = 0; i < L; i++)
		{
			cin >> arr[i];
			if (i > 0) {
				ll tmp = gcd(arr[i], arr[i - 1]);
				if (tmp == arr[i])
					tmp = sqrt(arr[i]);

				primes.insert(tmp);
				plain[i] = tmp;
			}
		}
		primes.insert(arr[0] / plain[1]);
		plain[0] = arr[0] / plain[1];
		primes.insert(arr[L - 1] / plain[L - 1]);
		plain.push_back(arr[L - 1] / plain[L - 1]);
		unordered_map<ll, char> mapping;
		char c = 'A';
		for (auto i : primes) {
			mapping[i] = c++;
		}
		string res = "";
		for (auto i : plain) {
			res += mapping[i];
		}
		cout << "Case #" << j << ": " << res << endl;
	}
	return 0;
}
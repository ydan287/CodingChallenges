
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

struct nd {
	int v;
	nd* left;
	nd* right;
	nd(int v = 0, nd* left = NULL, nd* right = NULL) : v(v), left(left), right(right) {}
};

struct tree {
	nd* root;
	void insert(int tmp) {
		nd* curr = root;
		nd* p = root;
		while (curr) {
			p = curr;
			curr = (tmp > curr->v) ? curr->right : curr->left;
		}
		if (p->v > tmp) {
			p->left = new nd(tmp);
		}
		else
		{
			p->right = new nd(tmp);
		}
	}
	string aux(nd* curr) {
		if (curr == NULL) {
			return "$";
		}
		string s = "1";
		s += aux(curr->left);
		delete curr->left;
		s += aux(curr->right);
		delete curr->right;
		return s;
	}
	string print() {
		string s = aux(root);
		delete root;
		return s;
	}

};

unordered_map<string, bool> um;

int main(){
	int n, k;
	while (cin >> n >> k) {
		um = unordered_map<string, bool>();
		REP(i, 0, n) {
			tree t;
			t.root = NULL;
			REP(j, 0, k) {
				int tmp;
				cin >> tmp;
				if (j == 0) {
					t.root = new nd(tmp);
				}
				else 
				{
					t.insert(tmp);
				}
			}
			um[t.print()] = true;
		}
		cout << um.size() << '\n';
	}
 	
	return 0;
}
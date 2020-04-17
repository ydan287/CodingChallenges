#include <iostream>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <random>
#include <numeric>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<int, pi> ppi;
typedef vector<ll> vi;
typedef vector<vi> mat;

int main () {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        stringstream res;
        res << "Case #" << tc << ": ";
        int dl = 0;
        string s;
        cin >> s;
        for (int i = 0; i < s.length(); i++)
        {
            int curr = int(s[i])-int('0');
            if (dl > curr) {
                res << string(dl-curr, ')') << curr;
            } else if (dl < curr) {
                res << string(curr-dl, '(') << curr;
            } else {
                res << curr;
            }
            dl = curr;
        }
        if (dl > 0){
            res << string(dl, ')');
        }
        cout << res.str() << endl;
    }
    

    return 0;
}
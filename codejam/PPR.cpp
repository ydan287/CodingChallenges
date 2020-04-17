#include <iostream>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <cstring>
#include <random>
#include <numeric>
#include <vector>
#include <string>
using namespace std;

typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<int, pi> ppi;
typedef vector<ll> vi;
typedef vector<vi> mat;

int main() {
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        bool possible = true;
        int N;
        cin >> N;
        vector<pair<pair<int, int>,int> > shifts;
        string res(N,'-');
        for (int n = 0; n < N; n++)
        {
            pair<pair<int, int>,int> curr;
            curr.second = n;
            cin >> curr.first.first >> curr.first.second;
            shifts.push_back(curr);
        }
        sort(shifts.begin(), shifts.end());
        int c = 0;
        int j = 0;
        
        for (int n = 0; n < N; n++)
        {
            if (c <= shifts[n].first.first) {
                c = shifts[n].first.second;
                res[shifts[n].second] = 'C';
            } else if ( j <= shifts[n].first.first){
                j = shifts[n].first.second;
                res[shifts[n].second] = 'J';
            } else {
                cout << "Case #" << tc << ": IMPOSSIBLE" << endl;
                possible = false;
                break;
            }
        }
        if (possible) {
            cout << "Case #" << tc << ": " << res << endl;
        }
        
    }
    
    return 0;
}
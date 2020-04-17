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
        int N;
        cin >> N;
        int r = 0;
        int c = 0;
        int trace = 0;
        int maxR = 0;
        int maxC = 0;
        vector <vector <int> > chist(N, vector<int>(N,0));
        vector<int> cflag(N, 1);
        for (int i = 0; i < N; i++)
        {
            vector<int> hist(N,0);
            int flag = 1;
            for (int j = 0; j < N; j++)
            {
                int curr;
                cin >> curr;
                if (i == j) {
                    trace += curr;
                }
                hist[curr-1]++;
                if (flag && hist[curr-1] > 1) {
                    maxR++;
                    flag = 0;
                }
                chist[j][curr-1]++; 
                if (cflag[j] && chist[j][curr-1]>1){
                    maxC++;
                    cflag[j] = 0;
                }
            }
        }
        printf("Case #%d: %d %d %d\n", tc, trace, maxR, maxC);
    }
    return 0;
}
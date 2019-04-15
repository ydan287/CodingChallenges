#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <cmath>
#include <map>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>
#include <list>

using namespace std;


int main() {

    cin.tie(0);
    cout.precision(10);
    cout << fixed;

    int x,y;
    int n;
    long double ret;
    while (cin >> x >> y>> n){
        int reg_dis = 0;
        double dis = 0;
        for(int i = 0; i < n; i++) {
            double l, u, factor;
            cin >> l >> u >> factor;
            dis += (u - l)*factor;
            reg_dis += (u - l);
        }
        reg_dis = y - reg_dis;
        ret = (x/(reg_dis+dis));
        cout << ret*1.0 << endl;
    }
    return 0;
}
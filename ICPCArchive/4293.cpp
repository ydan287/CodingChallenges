



#include <cassert>
#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include <functional>
#include <tuple>
#include <algorithm>
#include <math.h>
#include <queue>
#include <stack>
#include <string.h>


using namespace std;

#define MAXE ((int)1e5)

#define eps 1e-6



class point{
public:
    int x;
    int y;
    point(){};
    point(int x,int y): x(x),y(y){}
    bool operator<(const point &a) const {
        if(fabs(x-a.x) > eps)
            return x < a.x;
        return y < a.y;
    }
    point operator-(const point &a) const {
        point ret;
        ret.x = x - a.x;
        ret.y = y - a.y;
        return ret;
    }
};


enum LINE_TYPE {LINE, SEGMENT};
struct LINE2D {
    point s, e;
    LINE_TYPE type;
};
double dist(point a, point b) {
    return hypot(a.x - b.x, a.y - b.y);
}
double dot(point a, point b) {
    return a.x * b.x + a.y * b.y;
}
double cross2(point a, point b) {
    return a.x * b.y - a.y * b.x;
}
double cross(point o, point a, point b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int between(point a, point b, point c) {
    return dot(c - a, b - a) >= 0 && dot(c - b, a - b) >= 0;
}
int onSeg(point a, point b, point c) {
    return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
int intersection(point as, point at, point bs, point bt) {
    if(cross(as, at, bs) * cross(as, at, bt) < 0 &&
       cross(at, as, bs) * cross(at, as, bt) < 0 &&
       cross(bs, bt, as) * cross(bs, bt, at) < 0 &&
       cross(bt, bs, as) * cross(bt, bs, at) < 0)
        return 1;
    return 0;
}
double distProjection(point as, point at, point s) {
    int a, b, c;
    a = at.y - as.y;
    b = as.x - at.x;
    c = - (a * as.x + b * as.y);
    return fabs(a * s.x + b * s.y + c) / hypot(a, b);
}
double dist2Seg(point sa, point sb, point p) {
    double c = 1e+30;
    if(between(sa, sb, p))
        c = min(c, distProjection(sa, sb, p));
    else
        c = min(c, min(dist(sa, p), dist(sb, p)));
    return c;
}




int main() {
    int tastcase;
    cin >> tastcase;
    cout.precision(8);
    cout.setf(ios::fixed);
    while (tastcase--){
        int inner;
        cin >> inner;
        point in_vec[101];
        for(int i=0; i< inner; i++){
            cin >> in_vec[i].x >> in_vec[i].y;
        }
        int outer;
        cin >> outer;
        point outer_vec[101];
        for(int i=0; i < outer; i++){
            cin >> outer_vec[i].x >> outer_vec[i].y;
        }

        outer_vec[outer] = outer_vec[0];
        in_vec[inner] = in_vec[0];
        double min_dis = 1e+30;
        for (int i = 0; i < inner; i++) {
            for (int j = 0; j < outer; j++) {
                min_dis = min(min_dis, dist2Seg(outer_vec[j], outer_vec[j + 1], in_vec[i]));
                min_dis = min(min_dis, dist2Seg(in_vec[i], in_vec[i+1], outer_vec[j]));
            }
        }
        cout <<min_dis/2<<endl;
    }

    return 0;
}



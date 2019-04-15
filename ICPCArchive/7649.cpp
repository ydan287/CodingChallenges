#include <cassert>
#include <iostream>
#include <cstring>
#include <vector>
#include <list>
#include <functional>
#include <tuple>
#include <algorithm>

using namespace std;

#define MAXE ((int)1e5+42)

long long tree[2 * MAXE];

inline void modify(int n, long long t[], int p, int value) {  // set value at position p
    for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = t[p] + t[p ^ 1];
}

inline long long query(int n, long long t[], int l, int r) {  // sum on interval [l, r)
    long long res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += t[l++];
        if (r & 1) res += t[--r];
    }
    return res;
}


inline vector<long long> solve(const vector<int> &m, const vector<int> &r, const vector<int> &t) {
    const int e = (int) m.size();

    int root = -1;
    vector <list<int>> graph(e);

    for (int i = 0; i < e; ++i) {
        if (-1 == m[i]) {
            root = i;
        } else {
            graph[m[i] - 1].push_back(i);
        }
    }

    vector<int> left(e), right(e), center(e);
    int index;
    function<void(int)> dfs = [&](int vertex) {
        left[vertex] = index;

        for (int child : graph[vertex]) {
            dfs(child);
        }

        right[vertex] = index;
        ++index;
    };

    index = 0;
    dfs(root);

    assert(index == e);

    vector <tuple<int, int, int>> rankMinusRightIndex(e);


    for (int i = 0; i < e; ++i) {
        rankMinusRightIndex[i] = make_tuple(r[i], -right[i], i);
    }

    sort(rankMinusRightIndex.begin(), rankMinusRightIndex.end());
    memset(tree, 0, 2 * e * sizeof(*tree));

    vector<long long> answer(e);

    for (int i = 0; i < e; ++i) {
        int rank, index;
        tie(rank, ignore, index) = rankMinusRightIndex[i];

        answer[index] = query(e, tree, left[index], right[index]);
        modify(e, tree, right[index], t[index]);
    }

    return answer;
}

int main(int argc, const char *argv[]) {


    int e;

    while (cin >> e) {
        vector<int> m(e), r(e), t(e);

        for (int i = 0; i < e; ++i) {
            cin >> m[i] >> r[i] >> t[i];
        }

        vector<long long> answer = solve(m, r, t);

        for (int i = 0; i < e; ++i) {
            cout << answer[i] << endl;
        }
        //cout << endl;
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <algorithm>
#include <math.h>
#include <CMATH>
#include <iostream>     // std::cout, std::fixed
#include <iomanip>
using namespace std;
typedef long long ll;

using namespace std;

/////////trie
const int MaxN = 500500;
int sz = 0;

int nextn[27][MaxN];//containe next V
int endn[MaxN];//how many strings ends in this V
bool created[MaxN];//V already exist

void insert (string &s) {
    int v = 0;
    
    for (int i = 0; i < s.size(); ++i) {
        int c = s[i] - 'a';
        if (!created[nextn[c][v]]) {//if already exist just move to his son
            nextn[c][v] = ++sz; //else create new son
            created[sz] = true; //this son now exist
        }
        v = nextn[c][v];
    }
    ++endn[v]; //add one to strings end with this son
}

bool search (string tmp) {
    int v = 0;
    
    for (int i = 0; i < tmp.size(); ++i) {
        int c = tmp[i] - 'a';
        if (!created[nextn[c][v]])
            return false;
        v = nextn[c][v];
    }
    return endn[v] > 0;
}
/////////

//////segment tree
const int N = 1e5;  // limit for array size
int n;  // array size
int t[2 * N];

void build() {  // build the tree
    for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

void modify(int p, int value) {  // set value at position p
    for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
}

int query(int l, int r) {  // sum on interval [l, r)
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) res += t[l++];
        if (r&1) res += t[--r];
    }
    return res;
}
//////////

////union find
struct unionfind
{
    vector<int> rank;
    vector<int> parent;
    unionfind(int size)
    {
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++)
            parent[i]=i;
    }
    
    int find(int x){
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x)//for log*, not needed most of the time
        {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }
    void Union(int p, int q){
        p = find(p);
        q = find(q);
        if(q==p)
        {
            //alredy in the same group
            return;
        }
        if(rank[p] < rank[q]) parent[p] = q;
        else parent[q] = p;
        if(rank[p] == rank[q]) rank[p]++;
    }
};

////

int main () {
    
    //trie
    string keys[] = {"hi", "hello", "you", "ekta", "me"};
    string output[] = {"NO", "YES"};
    
    for (int i = 0; i < 5; ++i)
        insert (keys[i]);
    
    cout << output[search ("my")] << endl;
    cout << output[search ("me")] << endl;
    
    //segment tree
    n=15;//array size
    for (int i = 0; i < n; ++i)
        t[n + i]=1;//init array
    build();
    modify(0, 1);
    cout<< query(3, 11)<<endl;
    
    ///union find
    unionfind uf(10);
    uf.Union(1, 5);
    uf.Union(2, 5);
    if(uf.find(1)==uf.find(2))
        cout<<"1 and 2 in the same team"<<endl;
    if(uf.find(1)!=uf.find(7))
        cout<<"1 and 7 not in the same team";
    
    return 0;
}


#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_set>
#include  <iomanip>
#include <queue>
#include <stack>
using namespace std;
typedef long long ll;
#define v 5
#define e 5
#define inf 1000000
vector<vector<int>> g;

// BFS
// input: an adjacency list describing an undirected/directed graph (g)
// output: the distance of each node from s (dist)
// visible indicates which vertices where already seen
vector<int> visible;
vector<int> dist;
void bfs(int s)
{
    queue<int> q;
    q.push(s);
    visible[s]=1;
    dist[s]=0;
    while (!q.empty()) {
        int cur=q.front();
        q.pop();
        for(auto& ver :g[cur])
        {
            if(visible[ver]!=0)continue;
            visible[ver]=1;
            dist[ver]=dist[cur]+1;
            q.push(ver);
        }
    }
}

int max_ed(int s, int m, int t, VI seen) {
	seen[s] = 1;
	if (s == t) return m;
	for (auto e : edges[s]) {
		if (!seen[e]) {
			int res = max_ed(e, max(m, w[e][s]), t, seen);
			if (res >= 0) return res;
		}
	}
	return -1;
}
// DFS
// input: an adjacency list describing an undirected/directed graph (g)
// visible indicates which vertices where already seen
//mosty on trees..why?
void dfs(int s)
{
    cout<<s<<endl;
    visible[s]=1;
    for(auto x : g[s])
    {
        if(visible[x]==1)continue;
        dfs(x);
    }
}

// SCC (tarjan)
// input: an adjacency list describing a directed graph (adj)
// output: comp assigns each vertex to its scc number
//         size indicates the size of any scc
//         nc is the number of SCCs
// vis indicates which vertices where already seen
// root is the min id reachable from each vertex
//SCC tarjan on undirected adj
vector<int> vis;
vector<int> size;
vector<int> comp;
vector<int> root;
int nc;
stack<int> s;
vector<vector<int>> adj;
void tarjan(int cur, int d) {
    root[cur] = d; vis[cur]=1; s.push(cur);
    for (int i = 0; i < adj[cur].size(); ++i) {
        if (!vis[adj[cur][i]]) tarjan(adj[cur][i], d+1);
        if (comp[adj[cur][i]] == 0)
            root[cur] = min(root[cur], root[adj[cur][i]]);
    }
    //when finish with all the sons
    if (root[cur] == d) {
        comp[cur] = ++nc;
        for (size[nc] = 1; s.top() != cur; s.pop(), size[nc]++)
            comp[s.top()] = nc;
        s.pop();
    }
}
void SCC() {//updated
    vis=vector<int>(v,0);
    size=vector<int>(v+1,0);//the SCCs are 1 until v
    comp=vector<int>(v,0);
    root=vector<int>(v,0);
    nc = 0;
    for (int i = 0; i < v; ++i)//vertex 0 until v
        if (!vis[i]) tarjan(i, 0);
}
//explain wiki
//Nodes are placed on a stack in the order in which they are visited. When the depth-first search recursively visits a node v and its descendants, those nodes are not all necessarily popped from the stack when this recursive call returns. The crucial invariant property is that a node remains on the stack after it has been visited if and only if there exists a path in the input graph from it to some node earlier on the stack.

//At the end of the call that visits v and its descendants, we know whether v itself has a path to any node earlier on the stack. If so, the call returns, leaving v on the stack to preserve the invariant. If not, then v must be the root of its strongly connected component, which consists of v together with any nodes later on the stack than v (such nodes all have paths back to v but not to any earlier node, because if they had paths to earlier nodes then v would also have paths to earlier nodes which is false). The connected component rooted at v is then popped from the stack and returned, again preserving the invariant.

//Each node v is assigned a unique integer v.index, which numbers the nodes consecutively in the order in which they are discovered. It also maintains a value v.lowlink that represents (roughly speaking) the smallest index of any node known to be reachable from v, including v itself. Therefore v must be left on the stack if v.lowlink < v.index, whereas v must be removed as the root of a strongly connected component if v.lowlink == v.index. The value v.lowlink is computed during the depth-first search from v, as this finds the nodes that are reachable from v.



//Topological sort
// input: an adjacency list describing a directed graph (adj)
// output: ord is an ordered list of vertices which is a topological sort
// returns true if a topological sort exist, false if adj is not a DAG
//fg is a flag that indicates if the graph is DAG or not
//p is the next index in the order to assign
//visible holds 0 for unvisited nodes, 1 for nodes in proccess, 2 for exited nodes
int fg;
vector<int>ord;
int p;
void dfs_for_TS(int a)
{
    if(visible[a]==1) fg=1;//circle found
    if(visible[a]!=0) return;
    visible[a]=1;
    for(auto& x: adj[a])
        dfs_for_TS(x);
    visible[a]=2;
    ord[p]=a;p--;
}
bool TS()
{
    visible=vector<int>(v,0);
    ord=vector<int>(v,0);
    fg=0;
    p=v-1;
    for (int i=0; i<v; i++) {
        if(visible[i]==0)
            dfs_for_TS(i);
    }
    if(fg!=1)
        return true;
    return false;
}




int main() {
    
    g=vector<vector<int>>(v);
    for(int i=0;i<e;i++)
    {
        //get edges
        //int x,y;
        //cin>>x>>y;
        //g[x].push_back(y);
        //g[y].push_back(x);
    }
    cout<<"bfs"<<endl;
    g[0]={2,3};
    g[1]={2};
    g[2]={1,0,3};
    g[3]={0,2};
    visible=vector<int>(v,0);
    dist=vector<int>(v,inf);
    bfs(0);
    for(int i=0;i<v;i++)
        cout<<i<<" "<<dist[i]<<endl;
    cout<<"dfs"<<endl;
    visible=vector<int>(v,0);
    dfs(0);
    
    cout<<"scc"<<endl;
    adj=vector<vector<int>>(v);
    adj[0].push_back(1);
    adj[1].push_back(2);
    adj[2].push_back(0);
    adj[3].push_back(4);
    adj[4].push_back(3);
    SCC();
    for(int i=0;i<v;i++)
        cout<<i<<" "<<comp[i]<<endl;
    
    
    cout<<"Topological Sort"<<endl;
    adj=vector<vector<int>>(v);
    adj[0]={1,2};
    adj[1]={2};
    adj[2]={3,4};
    if(TS())
        for(auto& x:ord)
            cout<<x<<endl;
    
    cout<<"bellman-ford"<<endl;//o(nm)
    int source=0;
    //list of weighted edges
    vector<pair<pair<int, int>, int>> we={{{0,1},1},{{0,2},2},{{2,1},-2}};
    dist=vector<int>(v,inf);
    dist[source]=0;
    bool change=0;
    for(int i=0;i<v+1;i++)
    {
        change=0;
        for(auto& w_ed : we)
            if(dist[w_ed.first.second]>dist[w_ed.first.first]+w_ed.second)
            {
                change=1;
                dist[w_ed.first.second]=dist[w_ed.first.first]+w_ed.second;
            }
    }
    if(change==0)
    {
        for(int i=0;i<v;i++)
            cout<<i<<" "<<dist[i]<<endl;;
    }
    else
    {
        cout<<"negative cycle reachable from source"<<endl;
    }
    
    cout<<"Floyd-Warshall"<<endl;//(o(n^3))
    // Solves the all-pairs shortest path problem in O(n3) time.
    vector<vector<int>> r(v,vector<int>(v,inf));// r[i][j]=shortest path between i and j;
    for(int i=0;i<v;i++) r[i][i]=0;
    //fill r
    for(int k=0; k<v; k++)
        for(int i=0; i<v; i++)
            for(int j=0; j<v; j++)
                r[i][j]=min(r[i][j],r[i][k]+r[k][j]);
    //read more
    //there is a simple negative cycle C such that 0 can reach C and C can reach v.
    //• After n loops, r[i][j]<infinity iff there is a path from i to j.
    //• If i is involved in a simple negative cycle, then after n loops r[i][i]<0. (The converse is not necessarily true.)
    
    //if(r[i][j] is infinity) return "infinity" // no path
    // for(k=0; k<n; k++) if(r[k][k]<0 && r[i][k]<infinity && r[k][j]<infinity)
    //         return "-infinity";
    //return r[i][j];
    
    
    cout<<"Dijkstra"<<endl;// for graphs with non-negative weights.
    
    // Running time: O(|E| log |V|)
    /*One important restriction of this algorithm is that it only works for graphs with non-negative weights. The running time is O(n2). With a little effort it can be made into O(mlogn)
     It starts from the source vertex, in each stage there will be one new vertex marked. All the marked vertices consists of the civilized world, and the rest of the vertices consists on the unknown world. In each stage, we examine all the edges go from the civilized world to the unknown, to update the estimations of the distance of vertices in the unknown world. The one with the smallest estimation is the next vertex to mark.*/
    int N,s,t;
    cin>>N>>s>>t;
    vector<vector<pair<int, int>> > edges(N);
    for(int i=0;i<N;i++){
        int M;
        cin>>M;
        for (int j = 0; j < M; j++) {
            int vertex, dist;
            cin>>vertex>>dist;
            edges[i].push_back(make_pair(dist, vertex)); // note order of arguments here
        }
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > Q; //min_heap of pairs
    vector<int> dist(N, inf), dad(N, -1);
    
    
    Q.push(make_pair(0, s)); dist[s] = 0;
    while (!Q.empty()) {
        pair<int, int> p = Q.top();
        Q.pop();
        int here = p.second;
        //if (here == t) break;
        if (dist[here] != p.first)//check vertex only for the smallest dist that found
            continue;
        
        for (vector<pair<int, int>>::iterator it = edges[here].begin(); it != edges[here].end(); it++) {
            if (dist[here] + it->first < dist[it->second]) {
                dist[it->second] = dist[here] + it->first;
                dad[it->second] = here;
                Q.push(make_pair(dist[it->second], it->second));
            }
        }
    }
    
    printf("%d\n", dist[t]);
    if (dist[t] < inf)
        for (int i = t; i != -1; i = dad[i])
            printf("%d%c", i, (i == s ? '\n' : ' '));
    
    /*
     input structure:
     vertex_num source target
     (for each vertex:) num_of_neighbors (for each neighbor:) neighbor_id edge_weight
     Sample input:
     5 0 4
     2 1 2 3 1
     2 2 4 4 5
     3 1 4 3 3 4 1
     2 0 1 2 3
     2 1 5 2 1
     
     output:
     5
     4 2 3 0 */
    return 0;
}

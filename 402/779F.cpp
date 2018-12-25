#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

struct edge { int next; char c; };
struct tt {int node; int depth};


int convertGraphToTree(vector<vector<edge>> &graph, vector<vector<edge>> &tree, vector<vector<int>> &nodesByDepth, int n, int root) {
    vector<bool> found(n,false);
    vector<tt>   st;
    st.push_back({1,1});
    int deepest = 0;
    while (!st.empty) {
        tt current = st.back(); st.pop_back();
        found[current.node] = true;
        if (current.depth > deepest) { deepest = current.depth; }
        nodesByDepth[current.depth].push_back(current.node);
        for (auto e : graph[current.node]) {
            if (found[e.next]) continue;
            tree[current.node].push_back({e.next, e.c});
            st.push_back({e.next, current.depth+1});
        }
    }
    return deepest;
}




void solve() {
    int n; cin >> n;
    vector<vector<edge>> graph(n+1);
    vector<vector<edge>> tree(n+1);
    vector<vector<int>>  nodesByDepth(n+1);

    int n1,n2;
    char c;
    for (int i = 0; i < n-1; i++) {
        cin >> n1 >> n2 >> c;
        graph[n1].push_back({n2,c});
        graph[n2].push_back({n1,c});
    }

    int deepest = convertGraphToTree(graph,tree,nodesByDepth,n+1,1);
    ans = 0;

    convertGraphToTree()





    vector<vector<edge>> tree;




    // Convert Graph to Tree
    // Sort Nodes By Depth
    // Calculate Number of Deleted Nodes for Each Depth
    // Dump Output




int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("779C.in1","r",stdin);
  solve();
  return 0;
}
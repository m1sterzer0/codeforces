#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void dfs(int n, set<int> &visited, vector<int> &path, vector<vector<int>> &adj) {
    path.push_back(n);
    visited.insert(n);
    for (auto nn : adj[n]) {
        if (visited.find(nn) == visited.end()) {
            dfs(nn,visited,path,adj);
            path.push_back(n);
        }
    }
} 

void solve() {
    int n,m,k;  cin >> n >> m >> k;
    vector<vector<int>> adj(n+1);
    for (int i = 0; i < m; i++) {
        int x,y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    set<int> visited;
    vector<int> path;
    dfs(1,visited,path,adj);

    //Now just divide the path up into chunks
    int maxvertices = 2 * n / k;
    if (k * maxvertices < 2 * n) { maxvertices++; }
    int pidx = 0; int pathsize = (int) path.size();
    for (int i = 0; i < k; i++) {
        if (pidx == pathsize) {
            cout << "1 1" << endl;
        } else if (pidx + maxvertices > pathsize) {
            cout << pathsize - pidx;
            while (pidx < pathsize) { cout << " " << path[pidx++]; }
            cout << endl;
        } else {
            cout << maxvertices;
            for (int j = 0; j < maxvertices; j++) { cout << " " << path[pidx++]; }
            cout << endl;
        }
    }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("782E.in3","r",stdin);
  solve();
  return 0;
}
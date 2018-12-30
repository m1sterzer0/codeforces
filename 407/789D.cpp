#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

// * Widely know that a euler path exists in a graph if (a) graph is connected and (b) there are either 0 or 2 vertice with odd degree.
// * If we double up on all the edge, then all of the nodes have even degree.
// * We must find how many ways we can remove two edges and still have an edge of even degree
// * If one of the edges is a "loop edge", we can remove it and any other edge and be fine.
//   -- We handle these by just keeping a side count of the loop edges and not adding them into the graph.
// * Otherwise, we must remove two "connected" edges

struct S {
    int n;
    int m;
    int loops;
    vector<vector<int>> adj;
    vector<bool> visited;

    bool isConnected(int x) {
        connectedDfs(x);
        bool res = true;
        for (int i = 1; i <= n; i++) {
            if (visited[i]) continue;
            res = false;
            break;
        }
        return res;
    }

    void connectedDfs(int n) {
        visited[n] = true;
        for (auto nn : adj[n]) {
            if (!visited[nn]) { connectedDfs(nn); }
        }
    }

    ull findTwoPaths(int n) {
        // Here, n is the "middle node" in the two path
        ull degree = adj[n].size();
        if (degree < 2) { return 0 ;}
        return degree * (degree-1) / 2; 
    }
};

void solve() {
    S s;  
    cin >> s.n >> s.m;
    s.loops = 0;
    s.adj.clear(); s.adj.resize(s.n+1);
    s.visited.clear(); s.visited.resize(s.n+1,true);
    int x,y;
    for (int i = 0; i < s.m; i++) {
        cin >> x >> y;
        s.visited[x] = false;
        s.visited[y] = false;
        if (x == y) { s.loops += 1; }
        else        { s.adj[x].push_back(y); s.adj[y].push_back(x); }
    }
    if (!s.isConnected(x)) { cout << 0 << endl; return; }
    ull ans = 0;
    for (int i = 1; i <= s.n; i++) { ans += s.findTwoPaths(i); }
    ans += (ull) s.loops * (ull) (s.m - s.loops); // For pairing a loop path and a non-loop path
    if (s.loops >= 2) { ans += (ull) s.loops * (ull) (s.loops-1) / 2; }
    cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("789D.in1","r",stdin);
  solve();
  return 0;
}
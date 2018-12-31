#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

struct mysearch {
    int d;
    set<pair<int,int>> res;
    vector<vector<int>> adj;
    vector<int> parent;
    vector<int> police;
    queue<int> fifo;

    void doit() {
        for (auto p : police) {
            parent[p] = p;
            fifo.push(p);
        }
        bfs();
    }

    void bfs() {
        while (!fifo.empty()) {
            auto n = fifo.front(); fifo.pop();
            auto p = parent[n];
            for (auto nn : adj[n]) {
                if (parent[nn] > 0 && parent[nn] != p) {
                    if (n < nn) res.insert({n,nn});
                    else        res.insert({nn,n});
                }

                else if (parent[nn] < 0) {
                    parent[nn] = p;
                    fifo.push(nn);
                }
            }
        }
    }
};

void solve() {
    mysearch G;
    int n,k,d;
    cin >> n >> k >> d;
    G.d = d;
    G.police.resize(k);
    for (int i = 0; i < k; i++) { cin >> G.police[i]; }
    G.adj.clear();
    G.adj.resize(n+1);
    int x,y;
    vector<pair<int,int>> edges;
    for (int i = 0; i < n-1; i++) {
        cin >> x >> y;
        G.adj[x].push_back(y);
        G.adj[y].push_back(x);
        edges.push_back({x,y});
    }
    G.parent.clear();
    G.parent.resize(n+1,-1);
    G.doit();
    cout << G.res.size() << endl;
    bool firstflag = false;

    for (int i = 0; i < n-1; i++) {
        pair<int,int> e = edges[i];
        if (G.res.count(e) > 0 || G.res.count({e.second,e.first}) > 0) {
            if (firstflag) cout << " ";
            firstflag = true;
            cout << i+1;
        }
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("796D.in1","r",stdin);
    solve();
    return 0;
}

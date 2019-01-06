#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

struct node { ll r; ll c; };
bool operator<(const node &a, const node &b) { return a.r < b.r || (a.r == b.r && a.c < b.c); }
bool operator==(const node &a, const node &b) { return a.r == b.r && a.c == b.c; }
struct edge { ll d; ll v; };
bool operator<(const edge &a, const edge &b) { return a.d < b.d || (a.d == b.d && a.v < b.v); }
bool operator>(const edge &a, const edge &b) { return a.d > b.d || (a.d == b.d && a.v > b.v); }

void doDijkstra(ll start, ll end, ll maxnode, vector<ll> &dist, vector<vector<edge>> &adj) {
    priority_queue<edge, vector<edge>, greater<edge>> Q;
    dist.assign(maxnode+1,-1);
    Q.push({0,start});
    while (!Q.empty()) {
        edge p = Q.top(); Q.pop();
        if (dist[p.v] >= 0) { continue; }
        //cout << "DEBUG establishing " << p.d << " " << p.v << endl;
        dist[p.v] = p.d;
        if (p.v == end) break;
        for (auto e : adj[p.v]) {
            if (dist[e.v] >= 0) continue;
            //cout << "DEBUG pushing " << p.d+e.d << " " << e.v << endl;
            Q.push({p.d+e.d,e.v});
        }
    }
}

void solve() {
    // We make a "virtual node" for the rows/columns of lights.
    //    We charge 1 to get onto the highway and zero to get off.
    ll n, m, k;
    cin >> n >> m >> k;

    map<node,ll> nodeLookup;
    ll nodecnt = 0;

    for (ll i = 0; i < k; i++) {
        ll r,c; cin >> r >> c;
        nodeLookup[{r,c}] = nodecnt; nodecnt++;
    }

    // Virtual nodes for the row/column highways
    for (ll rr = 1; rr <= n; rr++) { nodeLookup[{rr,-1}] = nodecnt; nodecnt++; }
    for (ll cc = 1; cc <= m; cc++) { nodeLookup[{-1,cc}] = nodecnt; nodecnt++; }

    vector<vector<edge>> adj(nodecnt+1);

    for (auto const& x: nodeLookup) {
        auto nn = x.first;
        auto nnum = x.second;
        if (nn.r < 0 || nn.c < 0) continue; 
        //cout << "DEBUG: " << nn.r << " " << nn.c << " " << nnum << endl;
        if (nn.r < n && nodeLookup.count({nn.r+1,nn.c}) > 0) { adj[nnum].push_back({0LL,nodeLookup[{nn.r+1,nn.c}]}); }
        if (nn.r > 1 && nodeLookup.count({nn.r-1,nn.c}) > 0) { adj[nnum].push_back({0LL,nodeLookup[{nn.r-1,nn.c}]}); }
        if (nn.c < m && nodeLookup.count({nn.r,nn.c+1}) > 0) { adj[nnum].push_back({0LL,nodeLookup[{nn.r,nn.c+1}]}); }
        if (nn.c > 1 && nodeLookup.count({nn.r,nn.c-1}) > 0) { adj[nnum].push_back({0LL,nodeLookup[{nn.r,nn.c-1}]}); }

        if (true)     { adj[nnum].push_back({1LL,nodeLookup[{nn.r,-1}]});    adj[nodeLookup[{nn.r,-1}]].push_back({0LL, nnum}); }
        if (true)     { adj[nnum].push_back({1LL,nodeLookup[{-1,nn.c}]});    adj[nodeLookup[{-1,nn.c}]].push_back({0LL, nnum}); }
        if (nn.r < n) { adj[nnum].push_back({1LL,nodeLookup[{nn.r+1,-1}]});  adj[nodeLookup[{nn.r+1,-1}]].push_back({0LL, nnum}); }
        if (nn.r > 1) { adj[nnum].push_back({1LL,nodeLookup[{nn.r-1,-1}]});  adj[nodeLookup[{nn.r-1,-1}]].push_back({0LL, nnum}); }
        if (nn.c < m) { adj[nnum].push_back({1LL,nodeLookup[{-1,nn.c+1}]});  adj[nodeLookup[{-1,nn.c+1}]].push_back({0LL, nnum}); }
        if (nn.c > 1) { adj[nnum].push_back({1LL,nodeLookup[{-1,nn.c-1}]});  adj[nodeLookup[{-1,nn.c-1}]].push_back({0LL, nnum}); }
    }

    // Special case for the bottom right cell which is not guaranteed to be lit
    if (nodeLookup.count({n,m}) == 0) {
        nodeLookup[{n,m}] = nodecnt;
        adj[nodeLookup[{n,-1}]].push_back({0LL,nodecnt});
        adj[nodeLookup[{-1,m}]].push_back({0LL,nodecnt});
        //adj[nodeLookup[{n-1,-1}]].push_back({0LL,nodecnt}); //MAYBE???
        //adj[nodeLookup[{-1,m-1}]].push_back({0LL,nodecnt}); //MAYBE???
        nodecnt++;
    }

    ll start = nodeLookup[{1,1}];
    ll end   = nodeLookup[{n,m}];
    vector<ll> dist;
    doDijkstra(start,end,nodecnt-1,dist,adj);
    cout << dist[end] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("821D.in4","r",stdin);
    solve();
    return 0;
}

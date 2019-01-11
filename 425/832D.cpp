#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

// Starts from 1
// Assume less than 1000000
struct lcaStruct {
    ll n;
    ll root;
    bool prepFlag;
    vector<vector<ll>> adj;
    vector<ll> euler;
    vector<ll> depth;
    vector<ll> de;   // Depth from euler index
    vector<ll> fai;
    vector<ll> level;
    vector<array<ll,21>> dp;
    vector<ll> logn;
    array<ll,21> p2;

    void init(ll nin, ll r) {
        n = nin;
        root = r;
        prepFlag = false;
        adj.resize(n+1);
        for (ll i = 0; i <= n; i++) { adj[i].clear(); }
        euler.clear();
        logn.clear();
        fai.assign(n+1,-1);
        depth.assign(n+1,-1);

    }

    void _eulerDFS(ll nn, ll par, ll d) {
        euler.push_back(nn);
        if (depth[nn] == -1) { depth[nn] = d; }
        if (fai[nn] == -1)   { fai[nn] = (ll) euler.size()-1; }
        for (auto nn2 : adj[nn]) {
            if (nn2 == par) continue;
            _eulerDFS(nn2, nn, d+1);
            euler.push_back(nn);
        }
    }

    void _calcLog() {
        ll p2 = 2; ll logval = 0;
        for (ll i = 0; i < (ll) euler.size(); i++) {
            if (i == p2) { p2 *= 2; logval++; }
            logn.push_back(logval);
        }
    }

    void _calcp2() { p2[0] = 1; for (ll i = 1; i <= 20; i++) { p2[i] = 2 * p2[i-1]; }  }

    void _dodp() {
        ll sz = (ll) euler.size();
        for (auto e : euler) de.push_back(depth[e]);

        dp.resize(sz);
        for (ll i = 0; i < sz; i++) {
            for (ll j = 0; j <= 20; j++) { dp[i][j] = -1; }
        }

        for (ll i = 0; i+1 < sz; i++) { dp[i][0] = de[i] < de[i+1] ? i : i+1; }
        for (ll j = 1; j <= 20; j++) {
            for (ll i = 0; i+p2[j] < sz; i++) {
                dp[i][j] = de[dp[i][j-1]] < de[dp[i+p2[j-1]][j-1]] ? dp[i][j-1] : dp[i+p2[j-1]][j-1];
            }
        }
    }

    void _prep() {
        _eulerDFS(root,-1,1);
        _calcLog();
        _calcp2();
        _dodp();
    }

    ll lca(ll n1, ll n2) {
        if (!prepFlag) { _prep(); prepFlag = true; }
        if (n1 == n2) return n1;
        ll l = fai[n1];
        ll r = fai[n2];
        if (r < l) swap(r,l);
        ll dist = r - l;
        ll dx   = logn[dist];
        ll idx = de[dp[l][dx]] < de[dp[r-p2[dx]][dx]] ? dp[l][dx] : dp[r-p2[dx]][dx];
        return euler[idx];
    }
};

ll doit (lcaStruct &lcas, ll a, ll b, ll c, ll lca_ab, ll lca_bc, ll lca_ac) {
    ll d1 = lcas.depth[b] - lcas.depth[lca_ab];
    ll d2 = lcas.depth[b] - lcas.depth[lca_bc];
    if (d1 != d2) return min(d1,d2);
    else if (lca_ac == lca_bc) return min(d1,d2);
    else return d1 + lcas.depth[lca_ac] - lcas.depth[lca_bc];
}

void solve() {
    lcaStruct lcas;
    ll n, q; cin >> n >> q;
    lcas.init(n,1);
    for (ll i = 2; i <=n; i++) { ll p; cin >> p; lcas.adj[i].push_back(p); lcas.adj[p].push_back(i); }
    for (ll i = 0; i < q; i++) {
        ll a,b,c; cin >> a >> b >> c;
        ll best = 0;
        ll lca_ab = lcas.lca(a,b);
        ll lca_bc = lcas.lca(b,c);
        ll lca_ac = lcas.lca(a,c);
        best = max(best,doit(lcas,a,b,c,lca_ab,lca_bc,lca_ac));
        best = max(best,doit(lcas,a,c,b,lca_ac,lca_bc,lca_ab));
        best = max(best,doit(lcas,b,a,c,lca_ab,lca_ac,lca_bc));
        cout << best+1 << endl;
    }
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("832D.in1","r",stdin);
    solve();
    return 0;
}

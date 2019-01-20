#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;
#define PB push_back  
#define MP make_pair  
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  
#define REPE(i,n) FORE(i,0,n)  
#define FORSZ(i,a,v) FOR(i,a,SZ(v))  
#define REPSZ(i,v) REP(i,SZ(v)) 

struct solver {
    ll n;
    ll m;
    vector<ll> d;
    vector<vector<pair<ll,ll>>> adj;
    vector<vector<pair<ll,ll>>> adj2;
    vector<bool> visited;
    vector<ll> ans;


    void solve() {
        cin >> n >> m;
        d.resize(n+1);
        adj.resize(n+1);
        adj2.resize(n+1);
        visited.assign(n+1,false);
        ll x,y;
        FORE(i,1,n) { cin >> d[i]; }
        REP(i,m) { cin >> x >> y; adj[x].PB({y,i+1}); adj[y].PB({x,i+1});}

        // See if we can make this work
        ll lastneg1idx = -1;
        ll ss = 0;
        FORE(i,1,n) { 
            if (d[i] == -1) { d[i] = 0; lastneg1idx = i; }
            if (d[i] == 1)  ss++;
        }
        if (lastneg1idx == -1 && (ss & 1) == 1) { cout << "-1\n"; return; }
        if (ss & 1) { d[lastneg1idx] = 1; }
        makeSpanningTree(1,-1);
        dfs2(1,-1);
        printf("%lld\n", (ll) ans.size());
        for (auto p : ans) { printf("%lld\n", p); }
        //cout << ans.size() << "\n";
        //for (auto p : ans) { cout << p << "\n"; }
    }

    void makeSpanningTree(ll nn, ll par) {
        visited[nn] = true; // for first one
        for (auto pp : adj[nn]) {
            ll nn2 = pp.first;
            ll idx = pp.second;
            if (nn2 == par) continue;
            if (visited[nn2]) continue;
            visited[nn2] = true;
            adj2[nn].PB({nn2,idx});
            adj2[nn2].PB({nn,idx});
            makeSpanningTree(nn2,nn);
        }
    }
    
    void dfs2(ll nn, ll par) {
        ll paredge = -1;
        for (auto pp : adj2[nn]) {
            ll nn2 = pp.first;
            ll idx = pp.second;
            if (nn2 == par) { paredge = idx; }
            else            { dfs2(nn2,nn);  }
        }
        if (par >= 0) { // First node is correct by construction
            if ((ll) (adj2[nn].size() % 2) == d[nn]) { ans.push_back(paredge); }
            else                              { d[par] = (d[par] == 1 ? 0 : 1); }
        }
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("841D.in3","r",stdin);
    solver s;
    s.solve();
    return 0;
}

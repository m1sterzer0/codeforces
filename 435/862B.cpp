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
    vector<vector<ll>> adj;
    ll good;
    ll bad;

    void solve() {
        cin >> n;
        adj.resize(n+1);
        REP(i,n-1) { ll u,v; cin >> u >> v; adj[u].push_back(v); adj[v].push_back(u); }
        good = 0; bad = 0;
        dfs(1,-1,true);
        cout << good * bad - (n-1) << endl;
    }

    void dfs(ll nn, ll par, bool type) {
        if (type) good++;
        else      bad++;
        for (auto nn2 : adj[nn]) {
            if (nn2 == par) continue;
            dfs(nn2,nn,!type);
        }
    }

};

void solve() {
    solver s;
    s.solve();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

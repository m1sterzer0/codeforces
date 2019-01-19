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

    double dfs(ll nn, ll par) {
        double evsum = 0.0;
        ll numChildren = 0;
        for (auto nn2 : adj[nn]) {
            if (nn2 == par) continue;
            numChildren += 1;
            evsum += dfs(nn2,nn);
        }
        if (numChildren == 0) return 0.0;
        return 1.0 + evsum / (double) numChildren;
    }

    void solve() {
        cin >> n;
        adj.resize(n+1);
        REP(i,n-1) { ll x,y; cin >> x >> y; adj[x].PB(y); adj[y].PB(x); }
        double ans = dfs(1,-1);
        cout << ans << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solver s;
    s.solve();
    return 0;
}

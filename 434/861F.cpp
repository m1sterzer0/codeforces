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

struct tour { ll a; ll b; ll c;};

struct solver {
    ll n, m;
    vector<vector<ll>> adj;
    vector<tour> ans;
    vector<ll> visitOrder;
    ll order = 1;

    void solve() {
        cin >> n >> m;
        adj.resize(n+1);
        visitOrder.assign(n+1,-1);
        REP(i,m) { ll a, b; cin >> a >> b; adj[a].push_back(b); adj[b].push_back(a); }
        FORE(i,1,n) {
            if (visitOrder[i] < 0) dfs(i,-1);
        }
        printf("%lld\n", (ll) ans.size());
        for (auto aa : ans) {
            printf("%lld %lld %lld\n", aa.a, aa.b, aa.c);
        }
    }

   bool dfs(ll nn, ll par) {
       visitOrder[nn] = order; order++;
       ll ondeck  = -1;
       for (auto nn2 : adj[nn]) {
           if (nn2 == par) continue;
           if (visitOrder[nn2] < 0) {
               if (dfs(nn2,nn)) {
                   if (ondeck == -1) { ondeck = nn2; }
                   else              { ans.push_back({ondeck,nn,nn2}); ondeck=-1; }
               }
           }

           else if (visitOrder[nn2] > visitOrder[nn]) {
                if (ondeck == -1) { ondeck = nn2; }
                else              { ans.push_back({ondeck,nn,nn2}); ondeck=-1; }
           }
       }
       if (ondeck > 0 && par >= 0) { ans.push_back({ondeck,nn,par}); return false; }
       else                        { return true; }
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
    //freopen("861F.in1","r",stdin);
    solve();
    return 0;
}

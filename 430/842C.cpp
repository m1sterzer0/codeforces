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
    vector<ll> a;
    vector<vector<ll>> adj;
    vector<ll> ans1;
    vector<ll> ans;
    vector<ll> factors;
    ll numfactors;
    vector<ll> rootFactors;
    vector<ll> scoreboard;

    void solve() {
        cin >> n;
        a.resize(n+1);
        adj.resize(n+1);
        FORE(i,1,n) cin >> a[i];
        REP(i,n-1) { ll x,y; cin >> x >> y; adj[x].PB(y); adj[y].PB(x); }

        // Key observation: 0 node must be at root, or answer must be a factor of the root node
        ans1.resize(n+1);
        ans.resize(n+1);
        ans1[1] = a[1];
        for (auto nn2 : adj[1]) {
            if (nn2 == 1) continue;
            dfs1(nn2,1,0);
        }
        
        FORE(i,2,200000) { if (a[1] % i == 0) factors.PB(i); }
        reverse(factors.begin(),factors.end());
        numfactors = (ll) factors.size();
        scoreboard.assign(numfactors,0);
        dfs2(1,-1);

        FORE(i,1,n) { cout << ans[i] << " "; }
        cout << endl;
    }

    void dfs1(ll nn, ll par, ll prevgcd) {
        ans1[nn] = __gcd(prevgcd,a[nn]);
        for (auto nn2 : adj[nn]) {
            if (nn2 == par) continue;
            dfs1(nn2,nn,ans1[nn]);
        }
    }

    void dfs2(ll nn, ll par) {
        REP(i,numfactors) { if (a[nn] % factors[i] != 0) scoreboard[i]++; }
        ll ans2 = 1;
        REP(i,numfactors) { if (scoreboard[i] <= 1) { ans2 = factors[i]; break; } }
        ans[nn] = max(ans2,ans1[nn]);
        for (auto nn2 : adj[nn]) {
            if (nn2 == par) continue;
            dfs2(nn2,nn);
        }
        REP(i,numfactors) { if (a[nn] % factors[i] != 0) scoreboard[i]--; }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("842C.in1","r",stdin);
    solver s;
    s.solve();
    return 0;
}

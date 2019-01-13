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

const ll MAXN = 200001;
const ll MAXVAL = 200001;
ll n;
ll         a[MAXN];
bool       sieve[MAXVAL];
vector<ll> adj[MAXN];
vector<ll> pf[MAXN];  // Prime Factors
vector<ll> dp[MAXN];  // Best for each prime factor
ll ans;

void sieveFactors() {
    REP(i,MAXVAL) { sieve[i] = true; }
    for (ll j = 2; j < MAXVAL; j+=2) { sieve[j] = false; pf[j].PB(2); }
    for (ll i = 3; i < MAXVAL; i+=2) {
        if (!sieve[i]) continue;
        for (ll j = i; j < MAXVAL; j += i) { sieve[j] = false; pf[j].PB(i); }
    }
}

void dfs(ll nn, ll par) {
    if (a[nn] > 1) ans = max(ans,1LL);
    dp[nn].assign(SZ(pf[a[nn]]),1);
    for (auto nn2 : adj[nn]) {
        if (nn2 == par) continue;
        dfs(nn2,nn);
        ll lidx = 0;
        FORSZ(i,0,dp[nn2]) {
            ll pr = pf[a[nn2]][i];
            if (a[nn] % pr != 0) continue;
            while (pf[a[nn]][lidx] < pr) lidx++;
            ans = max(ans, dp[nn][lidx] + dp[nn2][i]);
            dp[nn][lidx] = max(dp[nn][lidx],1+dp[nn2][i]);
        }
    }
}

void solve() {
    sieveFactors();
    cin >> n;
    FORE(i,1,n) { cin >> a[i]; }
    REP(i,n-1) { ll x,y; cin >> x >> y; adj[x].PB(y); adj[y].PB(x); }
    ans = 0;
    dfs(1,-1);
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("1101D.in2","r",stdin);
    solve();
    return 0;
}

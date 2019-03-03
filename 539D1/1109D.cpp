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

// Modular Combinatorics
const ull mod = 1000000007;
inline ull madd(ull x, ull y) { ull r = x + y; if (r >= mod) { r -= mod; } return r; }
inline ull msub(ull x, ull y) { return x >= y ? x - y : x + mod - y; }
inline ull mmul(ull x, ull y) { return x * y % mod; }
inline ull mpow(ull x, ull p) { ull r=1; while (p) { if (p & 1) r = mmul(r,x); x = mmul(x,x); p = p >> 1; } return r; } 
inline ull minv(ull x) { return mpow(x,mod-2); }

struct modularCombinatorics {
    vector<ull> fact;
    vector<ull> ifact;
    void init(ull lim) {
        fact.clear(); fact.resize(lim+1,1);
        ifact.clear(); ifact.resize(lim+1,1);
        for (ull i = 2; i <= lim; i++) {
            fact[i] = mmul(fact[i-1],i);
            ifact[i] = minv(fact[i]);
        }
    }
    ull comb(ull n, ull k) {
        if (k > n) { return 0; }
        return mmul(mmul(fact[n],ifact[k]),ifact[n-k]);
    }
};

// Wikipedia for the win: https://en.wikipedia.org/wiki/Cayley%27s_formula
ll treecount(ll n, ll k) { return n == k ? 1LL : mmul(k,mpow(n,n-k-1)); }

void solve() {
    ll n, m, a, b; cin >> n >> m >> a >> b;
    ll ans = 0;
    modularCombinatorics mc;
    mc.init(1000000);
    FORE(k,1,min(m,n-1)) {
        ll lans = mc.comb(m-1,k-1);         // For the ordered partitions of the distance m into k parts -- stars and bars
        lans = mmul(lans,mc.fact[n-2]);     // For the way to pick the nodes on the path from a to b
        lans = mmul(lans,mc.ifact[n-1-k]);  
        lans = mmul(lans,mpow(m,n-k-1));    // For the remaining edges
        lans = mmul(lans,treecount(n,k+1));
        ans  = madd(ans,lans);
    }
    printf("%lld\n",ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("1109D.in1","r",stdin);
    solve();
    return 0;
}

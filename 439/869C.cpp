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
const ull mod = 998244353;
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

ll solveCase(modularCombinatorics &mc, ll a, ll b) {
    if (a > b) swap(a,b);
    ll ans = 0;
    FORE(i,0,a) {
        ll t1 = mc.comb(a,i);
        ll t2 = mc.comb(b,i);
        ll t3 = mc.fact[i];
        ll lans = mmul(mmul(t1,t2),t3);
        ans = madd(ans,lans);
    }
    return ans;
}


void solve() {
    modularCombinatorics mc;
    mc.init(5000);
    ll a,b,c; cin >> a >> b >> c;
    ll ans = 1;
    ans = mmul(ans,solveCase(mc,a,b));
    ans = mmul(ans,solveCase(mc,b,c));
    ans = mmul(ans,solveCase(mc,c,a));
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

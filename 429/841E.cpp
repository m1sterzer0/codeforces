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

// a*b is PerfSquare and b*c is PerfSquare implies a*c is PerfSquare
bool isPs(ll x) {
    ll l,r;
    l = 1;
    r = 1000000001;
    while (r-l > 1) {
        ll m = (r+l)/2;
        if (m*m <= x) l = m;
        else          r = m;
    }
    return l*l == x;
}


void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    REP(i,n) cin >> a[i];
    array<array<bool,300>,300> ps;
    REP(i,n) {
        FOR(j,i+1,n) {
            ps[i][j] = isPs(a[i]*a[j]);
        }
    }
    vector<bool> visited(n,false);
    vector<ll> groups;
    REP(i,n) {
        if (visited[i]) continue;
        visited[i] = true;
        ll newgrp = 1;
        for (ll j = i+1; j < n; j++) { 
            if (!ps[i][j]) continue;
            newgrp++;
            visited[j] = true;
        }
        groups.push_back(newgrp);
    }

    modularCombinatorics mc;
    mc.init(305);

    // Do the dp
    ll ngrp = (ll) groups.size();
    array<array<ll,302>,301> dp;
    REP(i,ngrp) {
        REP(j,n+2) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    ll sizeSoFar = 0;
    REP(i,ngrp) {
        ll totSlots = sizeSoFar+1;
        FORE(slots,1,min(totSlots,groups[i])) {
            ll ways = mc.comb(groups[i]-1,slots-1); // Stars and Bars
            FORE(badSlots,0,slots) {
                ll goodSlots = slots - badSlots;
                // goodSlots <= totSlots - j
                FORE(j,badSlots,totSlots-goodSlots) {
                    ll newBadSlots = j - badSlots + groups[i] - slots;
                    ll term1 = mmul(ways,mc.comb(j,badSlots));
                    ll term2 = mmul(dp[i][j],mc.comb(totSlots-j,goodSlots));
                    ll adder = mmul(term1,term2);
                    dp[i+1][newBadSlots] = madd(dp[i+1][newBadSlots],adder);
                }
            }
        }
        sizeSoFar += groups[i];
    }

    // Need to add the permutations for the members within a group
    ll ans = dp[ngrp][0];
    REP(i,ngrp) { 
        ans = mmul(ans,mc.fact[groups[i]]);
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("841E.in1","r",stdin);
    solve();
    return 0;
}

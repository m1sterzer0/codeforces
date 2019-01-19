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

// Sum r * (n choose r) is n * 2^(n-1)

void solve() {
    ll n; cin >> n;
    vector<ll> c(   1000001,0);
    vector<ll> cdiv(1000001,0);
    vector<ll> pow2(1000001,0);
    vector<ll> ans(1000001,0);
    pow2[0] = 1;
    FORE(i,1,1000000) { pow2[i] = mmul(pow2[i-1],2); }
    REP(i,n) { ll a; cin >> a; c[a]++; }
    FORE(i,1,1000000) {
        for(ll j = i; j <= 1000000; j += i) { cdiv[i] += c[j]; }
    }
    for(ll i = 1000000; i > 1; i--) {
        if (cdiv[i] == 0) continue;
        ans[i] = mmul(cdiv[i],pow2[cdiv[i]-1]);
        // Now we need to subtract off the sets that have already been counted because of a greater gcd
        for (ll j = 2*i; j <= 1000000; j += i) {
            if (ans[j] == 0) continue;
            ans[i] = msub(ans[i],ans[j]); 
        }
    }

    // Now to weight the answers by their GCD
    ll realans = 0;
    FORE(i,2,1000000) { 
        if (ans[i] > 0) realans = madd(realans,mmul(i,ans[i]));
    }

    cout << realans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

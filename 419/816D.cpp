#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

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

ull solveEven(vector<ll> &a, ll n) {
    modularCombinatorics mc;
    mc.init(200000);
    bool ff = ((n % 4) == 2);
    ll tot = n/2 -1;
    ull ans = 0;
    for (ll i = 0; i <= tot;  i++) {
        ans = madd(ans,mmul(mc.comb(tot,i),a[2*i]));
        if (ff) { ans = madd(ans,mmul(mc.comb(tot,i),a[2*i+1])); }
        else    { ans = msub(ans,mmul(mc.comb(tot,i),a[2*i+1])); }
    }
    return ans;
}


void solve() {
    ll n; cin >> n;
    vector<ll> ai(n);
    for (ll i = 0; i < n; i++) { cin >> ai[i]; }

    // Do some small caseas
    if (n == 1) { cout << ai[0] << endl;                             return; }
    if (n == 2) { cout << madd(ai[0],ai[1]) << endl;                 return; }
    if (n == 3) { cout << madd(madd(ai[0],ai[1]),msub(ai[1],ai[2])); return; } 

    if (n & 1) {
        bool flag = true;
        vector<ll> bi(n-1);
        for (ll i = 0; i < n-1; i++) {
            bi[i] = flag ? madd(ai[i],ai[i+1]) : msub(ai[i],ai[i+1]);
            flag = !flag;
        }
        ull ans = solveEven(bi,n-1);
        cout << ans << endl;
    } else {
        ull ans = solveEven(ai,n);
        cout << ans << endl;
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

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

void solve() {
    vector<int> smallPrimeDivisor(5000001);
    vector<ull>  modComp(5000001);
    for (int i = 2; i <= 5000000; i++)  { smallPrimeDivisor[i] = i; }
    for (int i = 2; i <= 5000000; i+=2) { smallPrimeDivisor[i] = 2; }
    for (int i = 3; i < 3000; i+=2) {
        if (smallPrimeDivisor[i] != i) { continue; }
        for (int j = i*i; j <= 5000000; j += 2*i) {
            if (smallPrimeDivisor[j] == j) { smallPrimeDivisor[j] = i; }
        }
    }

    for (ll i = 2; i <= 5000000; i++) {
        if (smallPrimeDivisor[i] == (int) i) { modComp[i] = (ull) i * (ull) (i-1) / 2ULL % mod; }
        else {
            ull p = (ull) smallPrimeDivisor[i];
            ull num = i/p;
            modComp[i] = madd(mmul(modComp[p],num),modComp[num]);
        }
    }
    ll t,l,r; cin >> t >> l >> r;
    ull ans = 0;
    for (ll i = r; i >= l; i--) {
        ans = madd(mmul(ans,t),modComp[i]);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

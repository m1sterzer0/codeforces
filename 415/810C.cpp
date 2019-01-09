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
    ull n; cin >> n;
    vector<ull> x(n);
    for (ll i = 0; i < (ll) n; i++) { cin >> x[i]; }
    sort(x.begin(),x.end());

    // Trick is f(a) = max_elem - min_elem, so sum(f(a)) = sum(max_elem) - sum(min_elem), each of which doesn't need O(n^2) to compute.
    ull summaxelem = 0;
    ull pow2 = 1;
    for (auto xx : x) {
        ll ss = mmul(xx,pow2-1);
        summaxelem = madd(summaxelem,ss);
        pow2 = mmul(2,pow2);
    }
    reverse(x.begin(),x.end());
    ull summinelem = 0;
    pow2 = 1;
    for (auto xx : x) {
        ll ss = mmul(xx,pow2-1);
        summinelem = madd(summinelem,ss);
        pow2 = mmul(2,pow2);
    }
    ull ans = msub(summaxelem,summinelem);
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

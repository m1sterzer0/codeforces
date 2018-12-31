#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

const ull mod = 1000000007;
inline ull madd(ull x, ull y) { ull r = x + y; if (r >= mod) { r -= mod; } return r; }
inline ull msub(ull x, ull y) { return x >= y ? x - y : x + mod - y; }
inline ull mmul(ull x, ull y) { return x * y % mod; }
inline ull mpow(ull x, ull p) { ull r=1; while (p) { if (p & 1) r = mmul(r,x); x = mmul(x,x); p = p >> 1; } return r; } 
inline ull minv(ull x) { return mpow(x,mod-2); }

void solve() {
    string s; cin >> s;
    int n; n = s.size();
    vector<ll> bs(n); ll b = 0;
    for (ll i = n-1; i >= 0; i--) {
        if (s[i] == 'b') b++;
        bs[i] = b;
    }
    ull pow2 = 1;
    ull ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'b') continue;
        ull lans = mmul(pow2,bs[i]);
        ans = madd(lans,ans);
        pow2 = mmul(pow2,2);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("782E.in3","r",stdin);
    solve();
    return 0;
}

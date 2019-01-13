#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

struct truck {
    ll s;
    ll f;
    ll c;
    ll r;
};

bool test(vector<ll> &a, truck &tt, ll v) {
    ll maxkm = v/tt.c;
    ll kmsofar = 0;
    ll refuelcnt = 0;
    if (tt.s == tt.f) return true;
    if (tt.s < tt.f) { 
        for (ll i = tt.s+1; i <= tt.f; i++) {
            if (kmsofar + (a[i] - a[i-1]) <= maxkm) { kmsofar += (a[i] - a[i-1]); }
            else if (maxkm >= (a[i] - a[i-1]) && refuelcnt < tt.r) { kmsofar = (a[i] - a[i-1]); refuelcnt++; }
            else return false;
        }
    }
    else {
        for (ll i = tt.f-1; i >= tt.s; i--) {
            if (kmsofar + (a[i+1] - a[i]) <= maxkm) { kmsofar += (a[i+1] - a[i]); }
            else if (maxkm <= (a[i+1] - a[i]) && refuelcnt < tt.r) { kmsofar = (a[i+1] - a[i]); refuelcnt++; }
            else return false;
        }
    }
    return true;
}

void solve() {
    ll n, m; cin >> n >> m;
    vector<ll> a(n+1);
    for (ll i = 1; i <= n; i++) { cin >> a[i]; }
    vector<truck> t(m);
    for (ll i = 0; i < m; i++) { cin >> t[i].s >> t[i].f >> t[i].c >> t[i].r; }
    ll minv = 0;
    for (auto tt: t) {
        if (test(a,tt,minv)) continue;
        ll l = minv;
        ll r = (a[n]-a[1]) * tt.c;
        while (r-l > 1) {
            ll m = (r+l)/2;
            if (test(a,tt,m)) r = m;
            else              l = m;
        }
        minv = r;
    }
    cout << minv << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("1101F.in1","r",stdin);
    solve();
    return 0;
}

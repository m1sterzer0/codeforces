#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll k, n;  cin >> k >> n;
    vector<ll> a(k);
    for (ll i = 0; i < k; i++) { cin >> a[i]; }
    vector<ll> s(k);  s[0] = a[0];
    for (ll i = 1; i < k; i++) { s[i] = s[i-1] +  a[i]; }
    sort(s.begin(),s.end());
    vector<ll> b(n);
    for (ll i = 0; i < n; i++) {cin >> b[i]; }
    sort(b.begin(),b.end());

    
    ll last = -1000000000;
    ll match = 0;
    for (ll i = 0; i < k; i++) {
        ll x = b[0] - s[i];
        if (x == last) continue;
        ll bidx = 0;
        for (ll i = 0; i < k; i++) {
            ll y = x + s[i];
            if (bidx < n && b[bidx] == y) { bidx++; }
        }
        if (bidx == n) match++;
        last = x;
    }

    cout << match << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("831C.in7","r",stdin);
    solve();
    return 0;
}

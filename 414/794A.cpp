#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

void solve() {
    ll a, b, c; cin >> a >> b >> c;
    ll n; cin >> n;
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        int x; cin >> x;
        if (x > b && x < c) ans++; 
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

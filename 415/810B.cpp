#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

void solve() {
    ll n, f; cin >> n >> f;
    priority_queue<ll> maxh;
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        ll k, l; cin >> k >> l;
        if (k >= l) { ans += l; }
        else { ans += k; maxh.push(l > 2*k ? k : l-k); }
    }
    for (ll i = 0; i < f; i++) {
        if (maxh.empty()) break;
        ans += maxh.top();
        maxh.pop();
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("810B.in1","r",stdin);
    solve();
    return 0;
}

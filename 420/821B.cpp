#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

void solve() {
    ll m, b;
    cin >> m >> b;
    ll ans = 0;
    for (ll y = 0; y <= b; y++) {
        ll x = m * (b-y);
        ll trial = 0;
        trial += y * (y+1) / 2 * (x+1);
        trial += x * (x+1) / 2 * (y+1);
        ans = max(trial,ans);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("821B.in1","r",stdin);
    solve();
    return 0;
}

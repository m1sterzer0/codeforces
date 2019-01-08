#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n, k;  cin >> n >> k;
    ll ans = (n + k - 2) / k * 2;
    if ((n - 2) % k == 0) ans--;
    cout << ans << endl;
    for (ll i = 2; i <= k+1; i++) cout << 1 << " " << i << endl;
    for (ll i = k+2; i <=n; i++)  cout << i-k << " " << i << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

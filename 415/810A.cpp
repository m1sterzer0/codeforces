#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n, k;  cin >> n >> k;
    ll ss = 0; ll x;
    for (int i = 0; i < n; i++) { cin >> x; ss += x; }
    ll ans = 0;
    while (ss < n*k - n/2) { ans += 1; n += 1; ss += k; }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("810A.in1","r",stdin);
    solve();
    return 0;
}

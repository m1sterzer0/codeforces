#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n, m;  cin >> n >> m;
    vector<ll> p(n+1);
    for (ll i = 1; i <= n; i++) { cin >> p[i]; }
    for (ll i = 0; i < m; i++) {
        ll l, r, x;
        cin >> l >> r >> x;
        ll numLess = 0;
        for (ll j = l; j <= r; j++) {
            if (p[j] < p[x]) numLess++;
        }
        if (x == numLess+l) cout << "Yes" << endl;
        else                cout << "No"  << endl;
    }

    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("811B.in1","r",stdin);
    solve();
    return 0;
}

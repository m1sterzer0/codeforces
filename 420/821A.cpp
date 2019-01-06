#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n; cin >> n;
    array<array<ll,50>,50> a;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            if (a[i][j] == 1) continue;
            bool good = false;
            for (ll ii = 0; ii < n; ii++) {
                for (ll jj = 0; jj < n; jj++) {
                    if (a[i][j] != a[ii][j] + a[i][jj]) continue;
                    good = true;
                    break;
                }
                if (good) break;
            }
            if (!good) {cout << "No" << endl; return; }
        }
    }
    cout << "Yes" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("821A.in1","r",stdin);
    solve();
    return 0;
}

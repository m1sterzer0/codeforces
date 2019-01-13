#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll q; cin >> q;
    for (ll i = 0; i < q; i++) {
        ll l,r,d;  cin >> l >> r >> d;
        if (d < l) cout << d << endl;
        else       cout << r/d * d + d << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

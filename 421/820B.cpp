#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n, a;
    cin >> n >> a;

    // Check bounds:
    ll err = infll; ll best = -1;
    for (ll s = 1; s <= n-2; s++) {
        ll locerr = n*a - 180*s;
        if (locerr < 0) {locerr = -locerr; }
        if (locerr < err) { best = s; err = locerr; }
    }
    cout << 1 << " " << n << " " << 1+best << endl; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

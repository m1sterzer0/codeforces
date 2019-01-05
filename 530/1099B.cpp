#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n; cin >> n;
    double droot = sqrt((double) n);
    ll x = (ll) droot;
    ll y = (ll) droot;
    while (x * y < n) { if (x > y) y++; else x++; }
    cout << x+y << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}
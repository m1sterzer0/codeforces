#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n, k; cin >> n >> k;
    n -=  n / (2*k) * (2*k);
    if (n >= k) cout << "YES" << endl;
    else        cout << "NO"  << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

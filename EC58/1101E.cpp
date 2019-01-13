#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n; cin >> n;
    ll s1 = 0; ll s2 = 1;
    for (ll i = 0; i < n; i++) {
        char c; ll l,w;  cin >> c >> l >> w;
        if (w > l) swap(l,w);
        if (c == '+') {
            s1 = max(s1,w);
            s2 = max(s2,l);
        }
        else {
            if (s1 <= w && s2 <= l) cout << "YES" << endl;
            else                    cout << "NO"  << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

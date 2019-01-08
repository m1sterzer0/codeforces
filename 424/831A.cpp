#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n; cin >> n;
    ll last = -1;
    ll state = 0;
    for (ll i = 0; i < n; i++ ) {
        ll cur; cin >> cur;
        if (state == 0) {
            if      (cur < last)  { state = 2; }
            else if (cur == last) { state = 1; }
            else                  { state = 0; }
        }
        else if (state == 1) {
            if      (cur < last)  { state = 2; }
            else if (cur == last) { state = 1; }
            else                  { cout << "NO" << endl; return; }
        }
        else if (state == 2) {
            if      (cur < last)  { state = 2; }
            else if (cur == last) { cout << "NO" << endl; return; }
            else                  { cout << "NO" << endl; return; }
        }
        last = cur;
    }
    cout << "YES" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

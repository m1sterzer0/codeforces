#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

void solve() {
    ll n, a, b; cin >> n >> a >> b;
    ll c = 0; //Singly occupied double tables
    ll denied =0;
    for (ll i = 0; i < n; i++) {
        ll t; cin >> t;

        if (t == 1) {
            if (a > 0) { a--; }
            else if (b > 0) { b--; c++; }
            else if (c > 0) { c--; }
            else denied++;
        }

        else {
            if (b>0) { b--; }
            else denied += 2;
        }
    }
    cout << denied << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

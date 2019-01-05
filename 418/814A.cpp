#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> a(n);
    ll minb = infll;
    ll maxb = 0;
    for (ll i = 0; i < n; i++ ) { cin >> a[i]; }
    for (ll i = 0; i < k; i++ ) { ll x; cin >> x; if (x < minb) minb = x; if (x > maxb) maxb = x; }

    if (a[0] == 0 && a[1] == 0)   { cout << "Yes" << endl; return; }
    if (a[0] == 0 && maxb >= a[1]) { cout << "Yes" << endl; return; }


    for (ll i = 0; i < n; i++) {
        if (a[i] == 0 && i > 0   && a[i-1] == 0)     { cout << "Yes" << endl; return; }
        if (a[i] == 0 && i > 0   && minb < a[i-1])   { cout << "Yes" << endl; return; }

        if (a[i] > 0 && i > 0 && a[i-1] > 0 && a[i] < a[i-1]) { cout << "Yes" << endl; return; }

        if (a[i] == 0 && i+1 < n && a[i+1] == 0)     { cout << "Yes" << endl; return; }
        if (a[i] == 0 && i+1 < n && maxb > a[i+1])   { cout << "Yes" << endl; return; }
    }

    cout << "No" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

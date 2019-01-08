#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n, k, p; cin >> n >> k >> p;
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) { cin >> a[i]; }
    sort(a.begin(),a.end());
    vector<ll> b(k);
    for (ll i = 0; i < k; i++) { cin >> b[i]; }
    sort(b.begin(),b.end());
    ll best = infll;
    for (ll i = 0; i <= k-n; i++) {
        ll curWorst = 0;
        for (ll j = 0; j < n; j++) {
            ll cur = abs(b[i+j]-p) + abs(b[i+j]-a[j]);
            curWorst = max(curWorst,cur);
        }
        best = min(best,curWorst);
    }
    cout << best << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

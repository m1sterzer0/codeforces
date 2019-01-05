#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n; cin >> n;
    vector<ll> a(n);
    vector<ll> b(n);
    vector<ll> ans(n);
    for (ll i = 0; i < n; i++) { cin >> a[i]; }
    for (ll i = 0; i < n; i++) { cin >> b[i]; }
    set<ll> avail;
    for (ll i = 1; i <=n; i++) { avail.insert(i); }
    ll firstidx = -1;
    ll secondidx = -1;
    for (ll i = 0; i < n; i++) {
        if (a[i] == b[i]  && avail.count(a[i]) > 0) { ans[i] = a[i]; avail.erase(a[i]); }
        else if (firstidx == -1) { firstidx = i; }
        else { secondidx = i; }
    }


    if (secondidx == -1)                                                                                   { ans[firstidx] = *avail.rbegin(); }
    else if (avail.count(a[firstidx]) > 0 && avail.count(b[secondidx]) > 0 && a[firstidx] != b[secondidx]) { ans[firstidx] = a[firstidx]; ans[secondidx] = b[secondidx]; }
    else                                                                                                   { ans[firstidx] = b[firstidx]; ans[secondidx] = a[secondidx]; }

    for (auto aa : ans) { cout << aa << " "; }
    cout << endl;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

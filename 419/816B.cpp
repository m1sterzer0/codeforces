#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

void solve() {
    ll n, k, q;
    cin >> n >> k >> q;
    vector<ll> li(n);
    vector<ll> ri(n);
    for (ll i = 0; i < n; i++) { cin >> li[i] >> ri[i]; }

    vector<ll> cumGood(200001); cumGood[0] = 0;
    sort(li.begin(),li.end());
    sort(ri.begin(),ri.end());
    ll idx1 = 0; ll idx2 = 0; ll runningOpen = 0; ll runningClosed = 0;
    for (ll i = 1; i <= 200000; i++) {
        while (idx1 < n && li[idx1] <= i) { idx1++; runningOpen++; }
        while (idx2 < n && ri[idx2] < i)  { idx2++; runningClosed++; }
        cumGood[i] = cumGood[i-1] + (runningOpen - runningClosed >= k ? 1LL : 0LL);
    }

    for (ll i = 0; i < q; i++) {
        ll a,b; cin >> a >> b;
        cout << cumGood[b] - cumGood[a-1] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("816B.in1","r",stdin);
    solve();
    return 0;
}

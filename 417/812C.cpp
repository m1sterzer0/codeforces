#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n, S; cin >> n >> S;
    vector<ll> a(n+1);
    for (int i = 1; i <=n; i++) { cin >> a[i]; }

    ll l = 0;
    ll r = n+1;
    ll bestcost = 0;
    while (r-l > 1) {
        ll m = (r+l)/2;
        priority_queue <ll, vector<ll>, greater<ll>> minh;
        for (int i = 1; i <= n; i++) {  minh.push(a[i] + i * m); }
        ll cost = 0;
        for (int i = 0; i < m; i++) { cost += minh.top(); minh.pop(); }
        if (cost <= S) { bestcost = cost; l = m; }
        else           { r = m; }
    }
    cout << l << " " << bestcost << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

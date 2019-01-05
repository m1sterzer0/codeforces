#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n; cin >> n;
    vector<vector<ll>> adj(n+1);
    for (ll i = 2; i <= n; i++) { 
        ll x; cin >> x;
        adj[i].push_back(x);
        adj[x].push_back(i);
    }
    vector<ll> s(n+1);
    for (ll i = 1; i <= n; i++) {
        cin >> s[i];
    } 

    ll ans = 0;
    ll good = true;

    function<void(ll,ll)> dfs = [&](ll nn, ll par) {
        if (s[nn] == -1) {
            ll parsum = -1;
            ll childmin = infll;
            for (auto nn2 : adj[nn]) {
                if (nn2 == par) parsum = s[nn2];
                else            childmin = min(childmin,s[nn2]);
            }
            if (childmin == infll) { s[nn] = s[par]; }
            else if (childmin >= parsum) { s[nn] = childmin; }  // maximizing a[nn] minimizes the sum, since othersie the a[i] of all the children would increase and there might be multiple children
            else { good = false; return; }
        }
        ans += (par == -1 ? s[nn] : s[nn] - s[par]);
        for (auto nn2 : adj[nn]) {
            if (nn2 != par) dfs(nn2,nn);
        }
    };    

    dfs(1,-1);
    if (!good) ans = -1;
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("1099D.in3","r",stdin);
    solve();
    return 0;
}

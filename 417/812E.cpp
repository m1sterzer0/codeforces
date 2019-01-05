#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n; cin >> n;
    vector<ll> a(n+1);
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<ll>> adj(n+1);
    for (ll i = 2; i <= n; i++) {
        ll x; cin >> x;
        adj[x].push_back(i);
        adj[i].push_back(x);
    }

    function<ll(ll,ll)> ds = [&](ll nn, ll par) {
        for (auto c : adj[nn]) {
             if (c == par) continue;
             return 1LL + ds(c,nn);
        }
        return 1LL;
    };

    ll depth=ds(1,-1);

    vector<ll> black;
    vector<ll> red;

    function<void(ll,ll,ll)> dfs = [&](ll nn, ll par, ll d) {
        if (d % 2 == depth % 2) { black.push_back(a[nn]); }
        else                    { red.push_back(a[nn]); }
        for (auto nn2 : adj[nn]) {
            if (nn2 == par) continue;
            dfs(nn2,nn,d+1);
        }
    };

    dfs(1,-1,1);

    ll startingXor = 0;
    for (auto x : black) startingXor = startingXor ^ x;
    for (ll i = 0; i < (ll) black.size(); i++) { black[i] = black[i] ^ startingXor; }

    map<ll,ll> redCount;
    for (auto r : red) { 
        if (redCount.count(r) == 0) redCount[r] = 1;
        else                        redCount[r] += 1;
    }


    ll ans = 0;
    // Case 1: Soliman already starts in a losing position, so we need to make a "dummy" move.
    ll redsize = red.size();
    ll blacksize = black.size();
    if (startingXor == 0) {
        ans += redsize * (redsize-1LL) / 2LL;
        ans += blacksize * (blacksize-1LL) / 2LL;
    }
    for (auto b : black) { ans += redCount.count(b) > 0 ? redCount[b] : 0LL; }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("812E.in10b","r",stdin);
    solve();
    return 0;
}

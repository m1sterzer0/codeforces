#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n; cin >> n;
    vector<vector<ll>> adj(n+1);
    vector<ll> primes({2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,
                       223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443});
    vector<ll> a(n+1);
    vector<ll> a2(n+1);
    for (ll i = 1; i <=n; i++) cin >> a[i];
    for (ll i = 0; i < n-1; i++) { ll x,y; cin >> x >> y; adj[x].push_back(y); adj[y].push_back(x); }
    ll best = 0;

    function<ll(vector<ll>&,ll,ll)> dfs = [&](vector<ll> &aa, ll nn, ll par) {
        ll best1 = 0;
        ll best2 = 0;
        for (auto nn2 : adj[nn]) {
            if (nn2 == par) continue;
            ll t = dfs(aa,nn2,nn);
            if (aa[nn2] != aa[nn]) continue;
            if (t >= best1)     { best2 = best1; best1 = t; }
            else if (t > best2) { best2 = t; }
        }
        if (aa[nn] > 1) { best = max(best,best1+1+best2); return best1+1; }
        else return 0LL;
    };

    for (auto p : primes) {
        // Could speed this up with precalc
        for (ll i = 1; i <= n; i++) { a2[i] = (a[i] % p == 0) ? p : 1; }
        for (ll i = 1; i <= n; i++) { a[i] /= a2[i]; }
        dfs(a2,1,-1);
    }
    dfs(a,1,-1);
    cout << best << endl;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

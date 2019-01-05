#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const double PI_D = 3.14159265358979323846;
const ll infll = 9223372036854775807LL;

struct circle {
    ll x;
    ll y;
    ll r;
};

bool operator<(const circle &a, const circle &b) { return a.r < b.r; }

inline bool isin(ll x1,ll y1,ll r1, ll x2,ll y2) { return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) <= r1*r1; }

void solve() {
    ll n; cin >> n;
    vector<circle> cc(n);
    for (ll i = 0; i < n; i++) {
        cin >> cc[i].x >> cc[i].y >> cc[i].r;
    }
    sort(cc.begin(),cc.end());
    reverse(cc.begin(),cc.end());

    // Build the tree
    vector<ll> roots;
    vector<vector<ll>> adj(n);
    for (ll i = 0; i < n; i++) {
        bool found = false;
        for (ll j = i-1; j >= 0; j--) {
            if (isin(cc[j].x, cc[j].y, cc[j].r, cc[i].x, cc[i].y)) {
                adj[i].push_back(j);
                adj[j].push_back(i);
                found = true;
                break;
            }
        }
        if (!found) {roots.push_back(i); }
    }

    vector<array<ll, 3>> dp(n);
    function<void(ll,ll)> dfs = [&](ll nn, ll par) {
        ll children = 0;
        for (auto nn2 : adj[nn]) {
            if (nn2 == par) continue;
            children++;
            dfs(nn2,nn);
        }
        ll xx = cc[nn].r * cc[nn].r;
        if (children == 0) {
            dp[nn][0] = xx;
            dp[nn][1] = xx;
            dp[nn][2] = -xx; 
        } else {
            dp[nn][0] = xx;  // Easy case.    Add our area + the "1 parent" area of the children.
            dp[nn][2] = -xx; // Easy case.    Add negative of our area + the "1 parent" area of the children.
            ll dp1a = xx;    // Harder case.  Add our area + the "2 parent" area of the children.
            ll dp1b = -xx;   // Harder case.  Add negative of our area + the "2 parent" area of the children.
            for (auto nn2 : adj[nn]) {
                if (nn2 == par) continue;
                dp[nn][0] += dp[nn2][1];
                dp[nn][2] += dp[nn2][1];
                dp1a += dp[nn2][2];
                dp1b += dp[nn2][0];
            }
            dp[nn][1] = max(dp1a,dp1b);
        }
    };

    ll rawans = 0;
    for (auto nn : roots) {
        dfs(nn,-1);
        rawans += dp[nn][0];
    }
    double ans = rawans * PI_D;
    printf("%.10e\n", ans);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("814D.in1","r",stdin);
    solve();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;


ll solveit(ll h, ll w, ll a, ll b, vector<ll> sizes) {
    // First, find the minimum index we definitely need.
    if (a <= h && b <= w) return 0;

    if (a <= h) {
        ll have   = w;
        ll needed = b;
        ll idx = 0;
        for (auto s : sizes) {
            have *= s; idx++;
            if (have >= needed) return idx;
        }
        return -1;
    }

    ll have = h * w;
    ll needed = a * b;
    ll idx = 0
    for (auto s : sizes) {
        have *= s; idx++;
        if (have > needed) break;
    }

}


void solve() {
    ll a,b,h,w,n;
    cin >> a >> b >> h >> w >> n;
    vector<ll> sizes()
    for (ll i = 0; i < n; i++) {
        ll x; cin >> x;
        if (x > 1) { sizes.push_back(x); }
    }
    sizes.sort(sizes.begin(),sizes.end(),greater<ll>);
    ll m1 = solveit(h,w,a,b,sizes);
    ll m2 = solveit(h,w,b,a,sizes);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("782E.in3","r",stdin);
    solve();
    return 0;
}

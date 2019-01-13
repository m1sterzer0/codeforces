#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

struct seg {
    ll idx;
    ll l;
    ll r;
};
bool operator<(const seg &a, const seg &b) { return (a.l < b.l) || (a.l == b.l && a.r < b.r); }


void solve() {
    ll T; cin >> T;
    while (T--) {
        ll n; cin >> n;
        vector<seg> arr(n);
        vector<ll>  a(n);
        for (ll i = 0; i < n; i++) {
            ll l,r; cin >> l >> r; arr[i] = { i, l, r};
        }
        sort(arr.begin(),arr.end());

        // Greedy assignment
        ll end1 = -1;
        ll end2 = -1;
        a[arr[0].idx] = 1;
        end1 = arr[0].r;
        bool twoflag = false;
        for (ll i = 1; i < n; i++) {
            if (arr[i].l <= end1)      { a[arr[i].idx] = 1; end1 = max(end1,arr[i].r); }
            else                       { twoflag = true; a[arr[i].idx] = 2; end2 = max(end2,arr[i].r); }
        }
        if (!twoflag) { cout << -1 << endl; }
        else {
            for (ll i = 0; i < n; i++) { cout << a[i] << " "; }
            cout << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

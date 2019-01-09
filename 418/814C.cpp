#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

// Key observation is that 26 * 1500 < 200,000

ll solveit(string &s, ll m, ll c) {
    ll n = s.size();
    ll best = 0;
    ll i = 0; ll j = 0; ll paintleft = m;
    while (j < n && (paintleft > 0 || s[j] == c)) {  if (s[j] != c) paintleft--; j++; }
    best = j-i;
    while (j < n) {
        if (s[i] != c) { paintleft += 1; }
        i++;
        while (j < n && (paintleft > 0 || s[j] == c)) {  if (s[j] != c) paintleft--; j++; }
        best = max(j-i,best);
    }
    return best;
}

void solve() {
    ll n; cin >> n;
    string s; cin >> s;
    vector<int> ans(26 * n);

    for (char c = 'a'; c <= 'z'; c++) {
        for (ll m = 1; m <= n; m++) {
            ll mykey = 26 * (m-1) + (c - 'a');
            ans[mykey] = (int) solveit(s,m,c);
        }
    }

    ll q; cin >> q;
    for (ll qq = 0; qq < q; qq++) {
        ll m; char c;  cin >> m >> c;
        ll mykey = 26 * (m-1) + (c - 'a');
        cout << ans[mykey] << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

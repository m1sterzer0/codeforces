#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n, m; cin >> n >> m;
    string s; cin >> s;
    string t; cin >> t;
    ll best = infll; ll bestidx = -1;
    for (ll i = 0; i <= m-n; i++) {
        ll mism = 0;
        for (ll j = 0; j < n; j++) {
            if (s[j] == t[i+j]) continue;
            mism++;
        }
        if (mism < best) {
            best = mism;
            bestidx = i;
        }
    }
    cout << best << endl;
    for (ll j = 0; j < n; j++) {
        if (s[j] == t[bestidx+j]) continue;
        cout << j+1 << " ";
    }
    cout << endl;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

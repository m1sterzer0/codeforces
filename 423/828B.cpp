#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n, m; cin >> n >> m;
    ll bcnt = 0;
    ll minx = m; ll maxx = -1;
    ll miny = n; ll maxy = -1;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            char c; cin >> c;
            if (c == 'B') {
                minx = min(minx,j);
                maxx = max(maxx,j);
                miny = min(miny,i);
                maxy = max(maxy,i);
                bcnt++;
            }
        }
    }
    if (bcnt == 0) { cout << 1 << endl; return; }
    ll ss = max(maxx-minx+1,maxy-miny+1);
    if (ss > n || ss > m) { cout << -1 << endl; return; }
    cout << ss*ss-bcnt << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

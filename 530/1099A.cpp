#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll w,h; cin >> w >> h;
    ll u1, d1; cin >> u1 >> d1;
    ll u2, d2; cin >> u2 >> d2;

    while (h > 0) {
        w += h;
        if (h == d1)      { w = max(w-u1,0LL); }
        else if (h == d2) { w = max(w-u2,0LL); }
        h--;
    }

    cout << w << endl;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

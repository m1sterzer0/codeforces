#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    array<int,4> l,s,r,p;
    for (int i = 0; i < 4; i++) { cin >> l[i] >> s[i] >> r[i] >> p[i]; }
    for (int i = 0; i < 4; i++ ) {
        if (l[i] & (p[i] || p[(i+3)%4])) { cout << "YES" << endl; return; }
        if (s[i] & (p[i] || p[(i+2)%4])) { cout << "YES" << endl; return; }
        if (r[i] & (p[i] || p[(i+1)%4])) { cout << "YES" << endl; return; }
    }
    cout << "NO" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll c, v0 ,v1, a, l;
    cin >> c >> v0 >> v1 >> a >> l;
    ll pagesRead = 0; ll days = 0;
    while (pagesRead < c) {
        if (days == 0) { pagesRead += v0; }
        else           { pagesRead += min(v0+a*days-l,v1-l); }
        days++;
    }
    cout << days << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

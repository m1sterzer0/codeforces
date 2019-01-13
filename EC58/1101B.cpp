#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    string s; cin >> s;
    ll f = 0;
    while (f < (ll) s.size() && s[f] != '[') f++;
    while (f < (ll) s.size() && s[f] != ':') f++;
    ll b = s.size() - 1;
    while (b >= 0 && s[b] != ']') b--;
    while (b >= 0 && s[b] != ':') b--;

    if (f >= b) { cout << -1 << endl; return; }

    ll lc = 0;
    for (ll i = f; i <= b; i++) { if (s[i] == '|') lc++; }

    cout << 4+lc << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

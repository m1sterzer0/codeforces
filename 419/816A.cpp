#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void nextTime(string &s) {
    if        (s[0] == '2' && s[1] == '3' && s[3] == '5' && s[4] == '9') { s[0] = '0'; s[1] = '0'; s[3] = '0'; s[4] = '0'; }
    else if   (               s[1] == '9' && s[3] == '5' && s[4] == '9') { s[0]++;     s[1] = '0'; s[3] = '0'; s[4] = '0'; }
    else if   (                              s[3] == '5' && s[4] == '9') {             s[1]++;     s[3] = '0'; s[4] = '0'; }
    else if   (                                             s[4] == '9') {                         s[3]++;     s[4] = '0'; }
    else                                                                 {                                     s[4]++;     }
}

void solve() {
    string s; cin >> s;
    ll ans = 0;
    while (s[0] != s[4] || s[1] != s[3]) { ans++; nextTime(s); }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

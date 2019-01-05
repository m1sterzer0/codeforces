#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    string s; cin >> s;
    ll k; cin >> k;
    string ans;
    ll natlen = 0;
    ll qmarks = 0;
    ll stars = 0;
    for (auto c : s) { 
        if (c == '?') qmarks++;
        else if (c == '*') stars++;
        else natlen++;
    }

    if (k < natlen - qmarks - stars) { cout << "Impossible" << endl; return; }
    if (k > natlen && stars == 0)    { cout << "Impossible" << endl; return; }

    if (k <= natlen) {
        ll gap = natlen - k;
        for (ll i = 0; i < (ll) s.size(); i++) {
            if (s[i] == '?' || s[i] == '*') continue;
            if (gap > 0 && i+1 < (ll) s.size() && (s[i+1] == '?' || s[i+1] == '*')) { gap--; continue; }
            ans.append(1,s[i]);
        }
    }

    else {
        ll extra = k - natlen;
        for (ll i = 0; i < (ll) s.size(); i++) {
            if (s[i] == '?' || s[i] == '*') continue;
            if (extra > 0 && i+1 < (ll) s.size() && (s[i+1] == '*')) { ans.append(1+extra,s[i]); extra = 0; continue; }
            ans.append(1,s[i]);
        }
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

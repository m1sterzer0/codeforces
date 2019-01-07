#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

string genAstring(string ans, ll a) {
    set<char> used;
    for (ll i = (ll) ans.size()-a; i < (ll) ans.size(); i++) { used.insert(ans[i]); }
    string res;
    for (char c = 'a'; c <= 'z'; c++) {
        if (used.count(c) > 0) continue;
        res += c;
        if ((ll) res.size() == a) break;
    }
    return res;
}

ll getAns(string s, ll start, ll end) {
    set<char> uniq;
    for (ll i = start; i <= end; i++) uniq.insert(s[i]);
    return (ll) uniq.size();
}


void solve() {
    ll a, b, l, r;
    cin >> a >> b >> l >> r; l--; r--;
    ll d1 = l / (a+b);
    ll d2 = r / (a+b);
    ll r1 = l % (a+b);
    ll r2 = r % (a+b);
    //misterb should just repeat the last character b times
    string alph = "abcdefghijklmnopqrstuvwxyz";
    string ans = alph.substr(0,a);
    ans += string(b,ans.back());
    for (ll i = 1; i <= 4; i++) {
        ans += genAstring(ans,a);
        ans += string(b,ans.back());
    }

    ll start = 0;
    ll end = ans.size()-1;
    if (d2-d1 < 4) {
        start = r1;
        end = (d2-d1)*(a+b) + r2;
    }
    cout << getAns(ans,start,end) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("820C.in3","r",stdin);
    solve();
    return 0;
}

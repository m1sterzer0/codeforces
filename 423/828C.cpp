#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

struct strcopy { ll start; ll sidx; };
bool operator<(const strcopy &a, const strcopy &b) { return a.start < b.start; }

void solve() {
    ll n; cin >> n;
    vector<string> ss;
    vector<strcopy> sc;
    for (ll i = 0; i < n; i++) {
        string s; cin >> s;
        ll k; cin >> k;
        ss.push_back(s);
        for (ll j = 0; j < k; j++) {
            ll x; cin >> x; x--;
            sc.push_back({x,i});
        }
    }        
    sort(sc.begin(),sc.end());
    string ans;
    ll ansidx = 0;
    for (auto s : sc) {
        string *pstr = &(ss[s.sidx]);
        if (ansidx >= s.start + (ll) (*pstr).size()) continue;
        if (ansidx < s.start) { ans += string(s.start-ansidx,'a'); ansidx = s.start; }
        ans += (*pstr).substr(ansidx-s.start, (ll) (*pstr).size()-(ansidx-s.start));
        ansidx = (ll) ans.size();
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

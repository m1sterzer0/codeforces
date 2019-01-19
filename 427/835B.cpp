#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;
#define PB push_back  
#define MP make_pair  
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  
#define REPE(i,n) FORE(i,0,n)  
#define FORSZ(i,a,v) FOR(i,a,SZ(v))  
#define REPSZ(i,v) REP(i,SZ(v)) 

void solve() {
    ll k; cin >> k;
    string s; cin >> s;
    vector<ll> opp(10);
    ll nDigSum = 0;
    for (auto c : s) { nDigSum += (ll) (c-'0'); opp[('9'-c)]++; }
    if (nDigSum >= k) { cout << 0 << endl; return; }
    ll ans = 0;
    for (ll inc = 9; inc >= 1; inc--) {
        if (nDigSum + inc * opp[inc] < k) { nDigSum += opp[inc] * inc; ans += opp[inc]; }
        else { ans += (k - nDigSum + inc - 1) / inc; cout << ans << endl; return; }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("835B.in1","r",stdin);
    solve();
    return 0;
}
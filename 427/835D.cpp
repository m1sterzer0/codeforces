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
    string s; cin >> s;
    array<array<int,5001>,5001> dp;
    REP(i,5001) dp[i].fill(0);
    array<ll, 5001> ans;
    ans.fill(0);
    FOR(lenm1,0,SZ(s)) {
        ll len = lenm1 + 1;
        ll slen = len/2;
        ll sidx = slen-1;
        FOR(l,0,SZ(s)-lenm1) {
            ll r = l + lenm1;
            if      (lenm1 == 0) { dp[l][r] = 1; ans[1] += 1; }
            else if (lenm1 == 1) { 
                if (s[r] == s[l]) { dp[l][r] = 2; ans[2] += 1; }
            }
            else {
                if (s[r] != s[l]) continue;
                else if (dp[l+1][r-1] == 0) continue;
                else { dp[l][r] = dp[l][l+sidx] + 1; ans[dp[l][r]]++; }
            }
        }
    }
    for (ll i = 4999; i >= 1; i--) { ans[i] += ans[i+1]; }
    for (ll i = 1; i <= SZ(s); i++) { cout << ans[i] << " "; }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("835D.in1","r",stdin);
    solve();
    return 0;
}

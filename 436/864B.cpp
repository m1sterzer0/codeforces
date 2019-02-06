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
    vector<bool> sb(26,false);
    ll cnt = 0;
    ll maxcnt = 0;
    ll n; cin >> n;
    string s; cin >> s;
    for (auto c : s) {
        if (c >= 'a' && c <= 'z') {
            if (!sb[c-'a']) {cnt++; maxcnt = max(maxcnt,cnt); }
            sb[c-'a'] = true;
        }

        else { cnt = 0; sb.assign(26,false); }
    }
    cout << maxcnt << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

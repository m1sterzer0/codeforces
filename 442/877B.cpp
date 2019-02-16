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
    ll n = (ll) s.size();
    vector<ll> nota(n+1,0LL);
    vector<ll> notb(n+1,0LL);
    REP(i,n) {
        if (s[i] == 'a') nota[i+1] = nota[i];
        else             nota[i+1] = nota[i] + 1;
        if (s[i] == 'b') notb[i+1] = notb[i];
        else             notb[i+1] = notb[i] + 1;
    }
    ll best = 0LL;
    FORE(i,0,n) {
        FORE(j,0,n-i) {
            ll changes = nota[i] + (notb[i+j] - notb[i]) + (nota[n] - nota[i+j]);
            best = max(best,n-changes);
        }
    }
    printf("%lld\n", best);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("877B.in1","r",stdin);
    solve();
    return 0;
}

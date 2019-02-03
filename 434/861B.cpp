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
    ll n,m; cin >> n >> m;
    ll globmin = 1;
    ll globmax = 200;
    // Let p be the number of rooms per floor
    // With each (k,f) pair, we know that
    // ---  (f-1)*p < k --> p < k/(f-1)
    // ---  f*p >= k --> p >= k/f
    REP(i,m) {
        ll k,f;  cin >> k >> f;
        ll locmin = (k+f-1)/ f;
        ll locmax = globmax;
        if (f > 1) { locmax = (k % (f-1) == 0) ? k/(f-1)-1 : k/(f-1); }
        globmin = max(locmin,globmin);
        globmax = min(locmax,globmax);
    }

    ll ans = 0;
    FORE(p,globmin,globmax) {
        ll locans = (n+p-1)/p;
        if (ans == locans) continue;
        if (ans == 0) { ans = locans; }
        else { ans = -1; break; }
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("861B.in1","r",stdin);
    solve();
    return 0;
}

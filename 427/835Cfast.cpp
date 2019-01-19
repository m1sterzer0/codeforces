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
    ll n,q,c; cin >> n >> q >> c;
    array<array<array<ll, 11>,101>,101> dp1,dp2;
    REP(i,101) { 
        REP(j,101) {
            REP(k,11) {
                dp1[i][j][k] = 0;
                dp2[i][j][k] = 0;
            }
        }
    }
    REP(i,n) {
        ll x,y,s;
        cin >> x >> y >> s;
        REP(j,c+1) dp1[x][y][j] += (s+j) % (c+1);
    }
    // Do the aggregate sums from 1,1 to x,y
    FORE(i,1,100) {
        FORE(j,1,100) {
            REP(k,c+1) {
                dp2[i][j][k] = dp1[i][j][k];
                if (i > 1) { dp2[i][j][k] += dp2[i-1][j][k]; }
                if (j > 1) { dp2[i][j][k] += dp2[i][j-1][k]; }
                if (i>1 && j>1) { dp2[i][j][k] -= dp2[i-1][j-1][k]; }
            }
        }
    }

    // Now for the queries
    REP(i,q) {
        ll t,x1,y1,x2,y2;
        cin >> t >> x1 >> y1 >> x2 >> y2;
        ll k = t % (c+1);
        ll ans = dp2[x2][y2][k];
        if (x1 > 1) { ans -= dp2[x1-1][y2][k]; }
        if (y1 > 1) { ans -= dp2[x2][y1-1][k]; }
        if (x1 > 1 && y1 > 1) { ans += dp2[x1-1][y1-1][k]; }
        printf("%lld\n", ans);
    } 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("835C.in2","r",stdin);
    solve();
    return 0;
}

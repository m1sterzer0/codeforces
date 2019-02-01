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
    ll n; cin >> n;
    vector<ll> a(n), b(n), c(n), d(n), e(n);
    REP(i,n) { cin >> a[i] >> b[i] >> c[i] >> d[i] >> e[i]; }
    if (n > 20) { cout << 0 << endl; return; }  // Real limit is like 11 I think, but I'm just being safe;
    ll numGood = 0;
    vector<ll> goodidx;
    REP(i,n) {
        bool good = true;
        REP(j,n) {
            if (j == i) continue;
            ll x1 = a[j]-a[i];
            ll x2 = b[j]-b[i];
            ll x3 = c[j]-c[i];
            ll x4 = d[j]-d[i];
            ll x5 = e[j]-e[i];
            FOR(k,j+1,n) {
                if (k == i) continue;
                ll y1 = a[k]-a[i];
                ll y2 = b[k]-b[i];
                ll y3 = c[k]-c[i];
                ll y4 = d[k]-d[i];
                ll y5 = e[k]-e[i];
                if (x1*y1+x2*y2+x3*y3+x4*y4+x5*y5 > 0) good = false;
            }
        }
        if (good) { numGood++; goodidx.push_back(i+1); }
    }
    cout << numGood << endl;
    REP(i,numGood) { cout << goodidx[i] << endl; }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

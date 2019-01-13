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

struct truck { ll s; ll f; ll c; ll r;};
bool operator<(const truck &a, const truck &b) { return a.s<b.s || (a.s==b.s && a.f<b.f); }

void solve() {
    ll n, m; cin >> n >> m;
    vector<ll> a(n+1);
    FORE(i,1,n) { cin >> a[i]; }
    vector<truck> trucks(m);
    REP(i,m) { cin >> trucks[i].s >> trucks[i].f >> trucks[i].c >> trucks[i].r; }
    sort(trucks.begin(),trucks.end());

    ll ans = 0;
    ll tidx = 0;
    vector<vector<ll>> dp(n+1);
    REP(i,n+1) { dp[i].assign(n+1,0); }
    vector<ll> lastRefuel(n+1);
    FORE(l,1,n) {
        if (trucks[tidx].s != l) continue;

        FORE(r,l,n) {
            dp[r][0] = a[r] - a[l];
            lastRefuel[r] = l;
        }

        FORE(k,1,n) {
            FORE(r,l,n) {
                ll lr = lastRefuel[r];
                ll best = max(dp[lr][k-1],a[r]-a[lr]);
                while (lr < r && best > max(dp[lr+1][k-1],a[r]-a[lr+1])) { best = max(dp[lr+1][k-1],a[r]-a[lr+1]); lr++; }
                dp[r][k] = best; lastRefuel[r] = lr;
                //cout << "DEBUG: l=" << l << " r=" << r << " k=" << k << " dp[r][k]=" << dp[r][k] << " lastRefuel[r]" << lastRefuel[r] << endl;
            }
        }

        while (tidx < m && trucks[tidx].s == l) {
            ll mindist = dp[trucks[tidx].f][trucks[tidx].r]; 
            ll minv    = trucks[tidx].c * mindist;
            //cout << "DEBUG: " << trucks[tidx].s << " " << trucks[tidx].f << " " << trucks[tidx].c << " " << trucks[tidx].r << " " << mindist << " " << minv << " " << endl;
            ans = max(ans,minv);
            tidx++;
        }
        if (tidx == m) break;
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("1101F.in1","r",stdin);
    solve();
    return 0;
}

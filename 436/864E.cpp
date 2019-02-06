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

struct item {
    ll t; ll d; ll p; ll idx;
};
bool operator<(const item &a, const item &b) { return a.d < b.d; }


void solve() {
    ll n; cin >> n;
    vector<item> a(n);
    ll dmax = 0;
    REP(i,n) { cin >> a[i].t >> a[i].d >> a[i].p; a[i].idx = i+1; dmax=max(dmax,a[i].d); }
    sort(a.begin(),a.end());
    vector<vector<ll>> dp(dmax+1);
    FORE(i,0,dmax) {
        dp[i].resize(n+1);
    }

    FORE(i,0,dmax) {
        FORE(j,0,n) {
            if (i == 0 || j == 0) { dp[i][j] = 0; }
            else {
                ll idx = j-1;
                dp[i][j] = max(dp[i][j-1],dp[i-1][j]);
                if (i >= a[idx].t && i < a[idx].d) { dp[i][j] = max(dp[i][j], a[idx].p + dp[i-a[idx].t][j-1]); }
            }
        }
    }

    // Lets backtrack to figure out which items we picked
    vector<ll> picked;
    ll j = n;
    ll i = dmax;
    while (i > 0 && j > 0) {
        if (dp[i][j] != dp[i][j-1]) { 
            picked.push_back(a[j-1].idx);
            i = min(i,a[j-1].d-1);
            i -= a[j-1].t;
        }
        j--;
    }
    reverse(picked.begin(),picked.end());
    cout << dp[dmax][n] << endl;
    cout << (ll) picked.size() << endl;
    for (auto pp : picked) { cout << pp << " "; }
    if (picked.size() > 0) cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("864E.in3","r",stdin);
    solve();
    return 0;
}

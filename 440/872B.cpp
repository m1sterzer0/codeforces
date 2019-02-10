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
    ll n, k; cin >> n >> k;
    vector<ll> a(n);
    REP(i,n) cin >> a[i];
    if (k == 1) {  
        cout << *min_element(a.begin(),a.end()) << endl;
    }
    else if (k >= 3) { 
        cout << *max_element(a.begin(),a.end()) << endl;
    }
    else {
        vector<ll> prefixmin(n);
        vector<ll> suffixmin(n);
        prefixmin[0] = a[0];
        FOR(i,1,n) { prefixmin[i] = min(prefixmin[i-1],a[i]); }
        suffixmin[n-1] = a[n-1];
        for (ll i = n-2; i >= 0; i--) suffixmin[i] = min(suffixmin[i+1],a[i]);
        ll ans = LLONG_MIN;
        REP(i,n-1) ans = max(ans, max(prefixmin[i],suffixmin[i+1]));
        cout << ans << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("872B.in1","r",stdin);
    solve();
    return 0;
}

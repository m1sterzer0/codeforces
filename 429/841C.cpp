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

// F(n,k) = (n+1)/(k+1)
// Rearrangement theorem
void solve() {
    ll m; cin >> m;
    vector<pair<ll,ll>> a(m);
    vector<pair<ll,ll>> b(m);
    vector<ll> ans(m);
    ll x;
    REP(i,m) { cin >> x; a[i] = {x,i}; }
    REP(i,m) { cin >> x; b[i] = {x,i}; }
    sort(b.begin(),b.end());
    sort(a.begin(),a.end());
    reverse(a.begin(),a.end());
    REP(i,m) { ll idx = b[i].second; ans[idx] = a[i].first; }
    for (auto x : ans) { cout << x << " "; }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("841C.in1","r",stdin);
    solve();
    return 0;
}

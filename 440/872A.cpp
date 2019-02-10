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
    ll n, m; cin >> n >> m;
    set<ll> aa;
    set<ll> bb;
    REP(i,n) { ll a; cin >> a; aa.insert(a); }
    REP(i,m) { ll b; cin >> b; bb.insert(b); }
    FORE(i,1,9) { if (aa.count(i) > 0 && bb.count(i) > 0) { cout << i << endl; return; } }
    ll d1 = *aa.begin();
    ll d2 = *bb.begin();
    if (d2 < d1) swap(d1,d2);
    cout << 10 * d1 + d2 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

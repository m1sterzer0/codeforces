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
    ll n, x; cin >> n >> x;
    if (n == 1) { cout << "YES\n"; cout << x << endl; return; }
    if (n == 2 &&  x == 0) { cout << "NO\n"; return; }
    mt19937 rng;
    rng.seed(1234567);
    uniform_int_distribution<ll> dist(0,(1<<19)-1);
    REP(i,1000) { 
        set<ll> picks;
        ll runningXor = 0;
        REP(i,n-1) {
            ll a = dist(rng);
            while (picks.count(a) > 0) { a = dist(rng); }
            runningXor ^= a;
            picks.insert(a); 
        }
        ll ans = runningXor ^ x;
        if (picks.count(ans) > 0) continue;
        picks.insert(ans);
        cout << "YES\n";
        for (auto p : picks) { cout << p << " "; }
        cout << endl;
        return;
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

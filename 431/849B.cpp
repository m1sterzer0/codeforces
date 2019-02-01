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

bool test (vector<ll> &a, ll n, ll m, ll x0, ll y0) {
    ll offset = 0;
    FORE(i,1,n) {
        ll y = y0 + (i-x0) * m;
        ll off = a[i] - y;
        if (off == 0 || off == offset) continue;
        if (offset == 0) { offset = off; }
        else { return false; }
    }
    return (offset == 0 ? false : true);
}

void solve() {
    ll n; cin >> n;
    vector<ll> a(n+1);
    FORE(i,1,n) { cin >> a[i]; a[i] += a[i]; } // Multiply the Y's by 2 -- helps with the slope
    if      (test(a, n, a[2]-a[1],     1, a[1])) { cout << "Yes\n"; }
    else if (test(a, n, (a[3]-a[1])/2, 1, a[1])) { cout << "Yes\n"; }
    else if (test(a, n, a[3]-a[2],     2, a[2])) { cout << "Yes\n"; }
    else                                         { cout << "No\n";  }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("849B.in1","r",stdin);
    solve();
    return 0;
}

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

// Let 1's represent the new coins that need to move to the right of the order.
// Key insight is that the old coins (0's) will each move at most 1 spot in each rotation.
// Thus, we just keep track of the rightmost 0's distance from its target location.

void solve() {
    ll n; cin >> n;
    printf("1 ");
    vector<ll> a(n,0LL);
    ll right0 = n-1;
    ll num0   = n;
    FORE(i,1,n) {
        ll p; cin >> p; a[p-1] = 1;
        num0--;
        if (num0 == 0) { printf("1\n"); return; }
        else {
            while (a[right0] == 1) right0--;
            printf("%lld ", right0 - (num0-1) + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

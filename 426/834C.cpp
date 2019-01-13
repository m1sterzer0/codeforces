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

ll cubeRoot(ll x) {
    ll l = 1; ll r = 1000001;
    while (r-l > 1) {
        ll m = (r+l) >> 1;
        if (m*m*m <= x) l = m;
        else            r = m;
    }
    return l;
}

void solve() {
    ll n; cin >> n;
    while (n--) {
        ll a,b; cin >> a >> b;
        ll prod = a * b;
        ll cr = cubeRoot(prod);
        if (cr*cr*cr != prod || a % cr != 0 || b % cr != 0) printf("No\n");
        else printf("Yes\n");
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    //freopen("834C.in1","r",stdin);
    solve();
    return 0;
}

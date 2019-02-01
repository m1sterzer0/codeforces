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
    ll k; cin >> k;
    if (k == 0) { cout << 'a' << endl; return; }
    ll n = 1;
    while ( n * (n-1) / 2 < k ) { n++; }
    char c = 'a';
    while (k > 0) {
        while (n * (n-1) / 2 > k) { n--; }
        ll inc = n * (n-1) / 2;
        REP(i,n) { cout << c; }
        k -= inc;
        c++;
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

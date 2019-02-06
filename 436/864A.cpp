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
    ll n; cin >> n;
    ll first = -1;
    ll second = -1;
    ll firstcnt = 0;
    ll secondcnt = 0;
    REP(i,n) {
        ll a; cin >> a;
        if (first == -1)       { first = a; firstcnt = 1; }
        else if (a == first)   { firstcnt++; }
        else if (second == -1) { second = a; secondcnt++; }
        else if (a == second)  { secondcnt++; }
        else                   { cout << "NO\n"; return; } 
    }
    if (second >= 0 && firstcnt == secondcnt) { cout << "YES\n"; cout << first << " " << second << endl; }
    else                                      { cout << "NO\n";  }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

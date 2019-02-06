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
    ll a, b, f, k;  cin >> a >> b >> f >> k;

    // Cases that don't work
    if (b < f || b < a-f)         { cout << -1 << endl; return; }
    if (k >  1 && b < 2 * (a-f) ) { cout << -1 << endl; return; }
    if (k >  2 && b < 2 * f )     { cout << -1 << endl; return; }

    ll gas = b;

    // Cases that work
    ll refuel = 0;
    REP(i,k) {
        if (i % 2 == 0) {
            gas -= f;
            if (i == (k-1)) {
                if (gas < a-f) { gas = b; refuel++; }
            }
            else {
                if (gas < 2*(a-f)) { gas = b; refuel++; }
            }
            gas -= (a-f);
        }

        else {
            gas -= (a-f);
            if (i == (k-1)) {
                if (gas < f) { gas = b; refuel++; }
            }
            else {
                if (gas < 2*f) { gas = b; refuel++; }
            }
            gas -= f;
        }
    }

    cout << refuel << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("864C.in2","r",stdin);
    solve();
    return 0;
}

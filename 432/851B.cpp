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
    // We need a, b, and c all to lie on the same circle
    // Moreover, we need ab = bc
    // Thus, we just need to make sure ab = bc and that the three points are not colinear
    ll ax, ay, bx, by, cx, cy;
    cin >> ax >> ay >> bx >> by >> cx >> cy;
    ll absquared = (bx-ax)*(bx-ax) + (by-ay)*(by-ay); // max of 8e18 -- ll should be fine
    ll bcsquared = (cx-bx)*(cx-bx) + (cy-by)*(cy-by); 
    ll areatimes2 = abs( ax*by + bx*cy + cx*ay - ay*bx - by*cx - cy*ax);
    if (absquared == bcsquared && areatimes2 > 0) cout << "Yes\n";
    else cout << "No\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

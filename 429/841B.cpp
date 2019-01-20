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
    // If all of the numebrs are even, the first player loses
    // Otherwise the first player wins
    // -- If sum is odd, take the whole thing
    // -- If not, there must be an even number of odd numbers.  Take one and sum will be odd, second player will take something, and the resulting sum will still be odd.
    bool allEven = true;
    ll n, a; cin >> n;
    REP(i,n) { cin >> a; if (a & 1) { allEven = false; break; } }
    string ans = allEven ? "Second" : "First";
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

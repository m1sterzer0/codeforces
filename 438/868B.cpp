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
    ll h, m , s, t1, t2; cin >> h >> m >> s >> t1 >> t2;
    t1 = (t1 == 12) ? 0 : 2 * t1;
    t2 = (t2 == 12) ? 0 : 2 * t2;
    vector<bool> barrier(24,false);
    h = (h == 12) ? 1 : 2 * h + 1;
    m  = 2 * (m / 5) + 1;
    s =  2 * (s / 5) + 1;
    barrier[h] = true;
    barrier[m] = true;
    barrier[s] = true;
    ll i = t1;
    while (i != t2) {
        i = (i + 1) % 24;
        if (i == t2) { cout << "YES\n"; return; }
        if (barrier[i]) break;
    }

    i = t1;
    while (i != t2) {
        i = (i == 0) ? 23 : i-1;
        if (i == t2) { cout << "YES\n"; return; }
        if (barrier[i]) break;
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

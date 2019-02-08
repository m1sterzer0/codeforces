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
    string pw; cin >> pw;
    ll n; cin >> n;
    bool first = false;
    bool last = false;
    REP(i,n) {
        string w; cin >> w;
        if (w == pw) { cout << "YES\n"; return; }
        else {
            if (w[1] == pw[0]) first = true;
            if (w[0] == pw[1]) last  = true;
        }
    }
    if (first && last) { cout << "YES\n"; }
    else               { cout << "NO\n";  }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

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
    ll n, k; cin >> n >> k;
    vector<bool> probs(16,false);
    REP(i,n) {
        ll idx = 0;
        ll adder = 1;
        REP(j,k) {
            ll p; cin >> p;
            if (p == 0) idx += adder;
            adder += adder;
        }
        probs[idx] = true;
    }
    ll mask = (1 << k) - 1;
    if (probs[mask]) { cout << "YES\n"; return; }
    FORE(i,1,mask-2) {
        if (!probs[i]) continue;
        FORE(j,i+1,mask-1) {
            if (!probs[j]) continue;
            if ((i | j) != mask) continue;
            cout << "YES\n";
            return;
        }
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

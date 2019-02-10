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
    vector<ll> p0xorbj(n);
    REP(j,n) {
        printf("? %lld %lld\n", 0LL, j);
        fflush(stdout);
        cin >> p0xorbj[j];
    }

    vector<ll> pixorb0(n);
    REP(i,n) {
        printf("? %lld %lld\n", i, 0LL);
        fflush(stdout);
        cin >> pixorb0[i];
    }

    ll numans = 0;
    vector<ll> ptest(n);
    vector<ll> pans;

    REP(b0,n) {
        bool good = true;
        REP(i,n) {
            ll pi = pixorb0[i] ^ b0;
            if (pi >= n || pi < 0) { good = false; break; }
            ptest[i] = pi; 
        }
        if (!good) continue;
        FOR(j,1,n) {
            ll bj = p0xorbj[j] ^ ptest[0];
            if (bj >= n || bj < 0 || ptest[bj] != j) { good = false; break; }
        }
        if (good) {
            numans++;
            pans = ptest;
        }
    }
    printf("!\n%lld\n", numans);
    for (auto pp : pans) { printf("%lld ", pp); }
    printf("\n");
    fflush(stdout);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

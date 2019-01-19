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
    ll n, k; cin >> n >>  k;
    vector<ll> a(k);
    REP(i,k) { cin >> a[i]; }
    ll groupsOf4 = n;
    ll groupsOf2 = 2*n;
    ll singleton = 0;

    // Pass 1 -- assign groups of 4 to groups of 4
    // Pass 2 -- assign groups of 4 to groups of 3
    // Pass 3 -- assign groups of 4 + groups of 2 to 2
    // Pass 4 -- assign groups of 4 + groups of 2 to singletons.
    REP(i,k) { 
        while (a[i] >= 4 && groupsOf4 > 0 ) { a[i] -= 4; groupsOf4 -= 1; }
    }

    REP(i,k) { 
        while (a[i] >= 3 && groupsOf4 > 0 ) { a[i] -= 3; groupsOf4 -= 1; }
    }

    REP(i,k) { 
        while (a[i] >= 2 && (groupsOf4 > 0 || groupsOf2 > 0)) {
            if (groupsOf4 > 0) { a[i] -= 2; groupsOf4 -= 1; singleton += 1;}
            else               { a[i] -= 2; groupsOf2 -= 1; }
        }
    }

    REP(i,k) { 
        while (a[i] >= 1) {
            if (groupsOf4 > 0)      { a[i] -= 1; groupsOf4 -= 1; singleton += 1;}
            else if (singleton > 0) { a[i] -= 1; singleton -= 1; }
            else                    { a[i] -= 1; groupsOf2 -= 1; }
        }
    }

    cout << (groupsOf2 >= 0 ? "YES" : "NO") << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("839B.in43","r",stdin);
    solve();
    return 0;
}

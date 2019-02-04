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


struct solver {
    ll n;
    ll onepos;
    ll zeropos;
    ll numOnes;

    string genstr(ll l, ll m) {
        string s(n,'0');
        FORE(i,l,m) { s[i] = '1'; }
        return s;
    }

    void solve() {
        cin >> n;
        string q(n,'0');
        printf("? %s\n", q.c_str());
        fflush(stdout);
        cin >> numOnes;
        onepos = -1; zeropos = -1;
        search(0,n-1);
        printf("! %lld %lld\n", zeropos+1, onepos+1);
        fflush(stdout);
    }

    void search(ll l, ll r) {
        ll m = (l+r)/2;
        printf("? %s\n", genstr(l,m).c_str());
        fflush(stdout);
        ll searchRes;
        cin >> searchRes;
        // All 1s case
        if (searchRes == numOnes - (m-l+1)) {
            onepos = l;
            if (zeropos < 0) search(m+1,r);
        }

        // All 0s case
        else if (searchRes == numOnes + (m-l+1)) {
            zeropos = l;
            if (onepos < 0) search(m+1,r);
        }

        else { search(l,m); }
    }

};

void solve() {
    solver s;
    s.solve();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

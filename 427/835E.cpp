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
    // Use 10 queries to find the bit positions where they are different -- there will be at least 1
    // Use up to 9 additional queries to find the value of the bit positions where they match
    ll n, x, y; cin >> n >> x >> y;
    ll firstdiff = 0;
    ll alldiff = 0;

    vector<ll> guesses;
    REP(i,10) {
        ll mask = 1 << i;
        guesses.clear();
        FORE(j,1,n) { if (j & mask) guesses.PB(j); }
        if (SZ(guesses) > 0) {
            cout << "? " << guesses.size() << " ";
            for (auto g : guesses) cout << g << " ";
            cout << endl;
            fflush(stdout);
            ll res; cin >> res;
            if (res == -1) exit(0);
            if (res == 0 || res == x) continue;
            if (firstdiff == 0) firstdiff = mask;
            alldiff |= mask;
        }
    }

    ll ans1 = firstdiff;  // Has a 1 in the position of the fistdiff mask
    ll ans2 = 0;          // Has a 0 in the position of the fistdiff mask
    REP(i,10) {
        ll mask = 1 << i;
        if (mask == firstdiff) continue;
        guesses.clear();
        FORE(j,1,n) { if ((j & mask) && (j & firstdiff)) guesses.PB(j); }
        if (SZ(guesses) > 0) {
            cout << "? " << guesses.size() << " ";
            for (auto g : guesses) cout << g << " ";
            cout << endl;
            fflush(stdout);
            ll res; cin >> res;
            if (res == -1) exit(0);
            if (res == 0 || res == x) continue;
            ans1 = ans1 | mask;
        }
    }
    ans2 = ans1 ^ alldiff;
    if (ans1 > ans2) { swap(ans1,ans2); }
    cout << "! " << ans1 << " " << ans2 << endl;
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

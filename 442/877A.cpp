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
    string s; cin >> s;
    ll matches = 0;
    array<string,5> names({"Danil","Olya","Slava","Ann","Nikita"});
    for (auto name : names) {
        for (ll i = 0; i <= (ll) s.size() - (ll) name.size(); i++) {
            bool match = true;
            for (ll j = 0; j < (ll) name.size(); j++) {
                if (s[i+j] != name[j]) { match = false; break; }
            }
            if (match) matches++;
        }
    }
    if (matches == 1) printf("YES\n");
    else              printf("NO\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

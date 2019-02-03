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
    // Try with strings to deal with zeros
    unordered_map<string,ll> cnt;
    ll n; cin >> n;
    vector<string> phoneBook;
    REP(i,n) { string s; cin >> s; phoneBook.push_back(s); }
    for (auto s : phoneBook) {
        FORE(slen,1,9) {
            set<string> seen;
            for (ll i = 0; i+slen <= 9; i++) {
                string c = s.substr(i,slen);
                if (seen.count(c) > 0) continue;
                seen.insert(c);
                if (cnt.count(c) == 0) cnt[c] = 1;
                else                   cnt[c]++;
            }
        }
    }

    for (auto s : phoneBook) {
        FORE(slen,1,9) {
            bool done = false;
            for (ll i = 0; i+slen <= 9; i++) {
                string c = s.substr(i,slen);
                if (cnt[c] > 1) continue;
                done = true;
                cout << c << '\n';
                break;
            }
            if (done) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("861D.in1","r",stdin);
    solve();
    return 0;
}

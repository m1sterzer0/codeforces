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
    string s; cin >> s;
    vector<ll> score(26,0);
    ll last = '!';
    ll lastcnt = 0;
    ll level = 0;
    for (auto c : s) {
        if (c == last) { lastcnt++; }
        else           { last = c; lastcnt = 1; }
        if (lastcnt == k) { 
            score[c-'a']++;
            level = max(score[c-'a'],level);
            lastcnt = 0; 
        }
    }
    cout << level << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

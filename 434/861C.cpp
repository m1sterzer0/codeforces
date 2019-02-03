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
    ll n; n = (ll) s.size();
    vector<bool> vowel(n,false);
    REP(i,n) { if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') vowel[i] = true; }
    ll beg = 0;
    REP(i,n) {
        if (i - beg < 2) continue;
        if (vowel[i-2] || vowel[i-1] || vowel[i]) continue;
        if (s[i-2] == s[i-1] && s[i-1] == s[i]) continue;
        cout << s.substr(beg, i-beg) << " ";
        beg = i;
    }
    cout << s.substr(beg,n-beg) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

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
    vector<ll> cnt(n+1,0);
    vector<ll> perm(n);
    REP(i,n) { cin >> perm[i]; }
    for (auto aa : perm) { cnt[aa]++; }
    vector<ll> filler;
    FORE(i,1,n) { if (cnt[i] == 0) filler.push_back(i); }
    ll num2change = (ll) filler.size();
    reverse(filler.begin(),filler.end());
    vector<bool> used(n+1,false);
    vector<ll> ans;
    for (auto pp : perm) {
        if (used[pp])          { ans.push_back(filler.back()); filler.pop_back(); }
        else if (cnt[pp] == 1) { ans.push_back(pp); }
        else if (filler.empty() || pp < filler.back()) { ans.push_back(pp); used[pp] = true; }
        else  { ans.push_back(filler.back()); filler.pop_back(); cnt[pp]--; }                                        
    }
    cout << num2change << endl;
    for (auto aa : ans) { cout << aa << " "; }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

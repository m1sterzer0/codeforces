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
    ll even = n / 2;
    ll odd = n - n/2;
    // Can always do even -- odd -- even
    printf("%lld\n", even + odd + even);
    vector<ll> ans;
    for (ll i = 1; i <= even; i++) ans.push_back(2*i);
    for (ll i = 0; i < odd; i++)   ans.push_back(2*i+1);
    for (ll i = 1; i <= even; i++) ans.push_back(2*i);
    for (auto a : ans) { printf("%lld ", a); }
    printf("\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

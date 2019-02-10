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
    // The most that the digits can sum to is the number of digits of n * 9;
    ll nn = n;
    ll digits = 0;
    while (nn > 0) { digits++; nn /= 10; }
    vector<ll> ans;
    for (ll k = n - 9 * digits; k <= n; k++) {
        ll digsum = 0;
        ll kk = k;
        while (kk > 0) {
            digsum += kk % 10;
            kk /= 10;
        }
        if (k + digsum == n) { ans.push_back(k); }
    }
    cout << ans.size() << '\n';
    for (auto kk : ans) { 
        cout << kk << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

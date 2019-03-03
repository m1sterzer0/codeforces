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


ll countXorSubarrays(vector<ll> &a, ll val) {
    ll n = (ll) a.size();
    if (n == 0) return 0LL;
    vector<ll> prefixXor(n,0LL);
    unordered_map<ll,ll> found;
    ll prev = 0;
    REP(i,n) { prev ^= a[i]; prefixXor[i] = prev; }
    ll ans = 0;
    REP(i, n) {
        ll targ = val ^ prefixXor[i];
        if (found.count(targ)) ans += found[targ];
        if (prefixXor[i] == val) ans++; // Special case of whole array
        found[prefixXor[i]]++; 
    }
    return ans;
}

void solve() {
    ll n; cin >> n;
    vector<ll> a(n);
    REP(i,n) cin >> a[i];
    vector<ll> a1;
    vector<ll> a2;
    a1.resize(n/2);
    a2.resize( n & 1 ? n/2 : n/2 - 1);
    REP(i, (ll) a1.size()) a1[i] = a[2*i]   ^ a[2*i+1];
    REP(i, (ll) a2.size()) a2[i] = a[2*i+1] ^ a[2*i+2];
    ll ans1 = countXorSubarrays(a1,0);
    ll ans2 = countXorSubarrays(a2,0);
    printf("%lld\n", ans1+ans2);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

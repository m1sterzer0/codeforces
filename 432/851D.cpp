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
    // Prime sieve
    ll maxn = 1000000;
    ll sqrtmaxn = 1000;
    vector<bool> sieve(maxn+1,true);
    for (ll i = 4; i<= maxn; i += 2) { sieve[i] = false; }
    for (ll i = 3; i <= sqrtmaxn; i += 2) {
        if (!sieve[i]) continue;
        for (ll j = i*i; j <= maxn; j += 2*i) { sieve[j] = false; }
    }
    vector<ll> primes;
    primes.push_back(2);
    for (ll i = 3; i <= maxn; i += 2) { if (sieve[i]) { primes.push_back(i); } }

    ll n, x, y;
    cin >> n >> x >> y;
    vector<ll> a(n);
    REP(i,n) { cin >> a[i]; }

    vector<ll> cnt(maxn+1,0);
    vector<ll> cumcnt(maxn+1,0);
    vector<ll> cumsum(maxn+1,0);
    for (auto aa : a) { cnt[aa]++; }
    FORE(i,1,maxn) { cumcnt[i] = cumcnt[i-1] + cnt[i]; cumsum[i] = cumsum[i-1] + i * cnt[i]; }
    ll maxincs = x/y;
    ll bestcost = infll;
    for (auto p : primes) {
        ll cost = 0;
        ll targ = p;
        ll r = p;
        ll m = max(0LL, p-maxincs-1);
        ll l = 0;
        while (l < maxn) {
            cost += y * (targ * (cumcnt[r]-cumcnt[m]) - (cumsum[r] - cumsum[m]) );
            cost += x * (cumcnt[m]-cumcnt[l]);
            if (cost > bestcost) break;
            l += p; targ += p; m += p; r += p;
            m = min(m,maxn);
            r = min(r,maxn);
        }
        bestcost = min(bestcost,cost);
    }
    cout << bestcost << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("851D.in1","r",stdin);
    solve();
    return 0;
}

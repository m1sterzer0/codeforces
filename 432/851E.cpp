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

ll calcGrundy(ll sig, map<ll,ll> &g) {
    if (g.count(sig) == 0) {
        vector<ll> gcount(31,0);
        FORE(i,1,30) {
            ll mask = 1 << i;
            if (mask > sig) break;
            ll child = (sig >> i) | (sig & (mask-1));
            gcount[calcGrundy(child,g)]++;
        }
        FORE(i,0,30) {
            if (gcount[i] > 0) continue;
            g[sig] = i;
            break;
        }
    }
    return g[sig];
}

void solve() {
    // Prime sieve
    ll maxn = 32000;
    ll sqrtmaxn = 179;
    vector<bool> sieve(maxn+1,true);
    for (ll i = 3; i <= sqrtmaxn; i += 2) {
        if (!sieve[i]) continue;
        ll inc = i+i;
        for (ll j = i*i; j <= maxn; j += inc) { sieve[j] = false; }
    }
    vector<ll> primes;
    primes.push_back(2);
    for (ll i = 3; i <= maxn; i += 2) { if (sieve[i]) { primes.push_back(i); } }

    ll n; cin >> n;
    vector<ll> a(n);
    REP(i,n) { cin >> a[i]; }
    
    /// Need to calculate the grundy number for each prime.
    ll grundyxor = 0;
    map<ll,ll> grundyCache;
    grundyCache[0] = 0;
    grundyCache[1] = 0;
    for (auto p : primes) {
        ll sig = 0;
        REP(i,n) {
            ll pp = 0;
            while (a[i] % p == 0) {
                pp += 1;
                a[i] /= p;
            }
            sig = sig | (1 << pp);
        }
        grundyxor = grundyxor ^ calcGrundy(sig,grundyCache);
    }

    // Now do the primes that are left over
    set<ll> bigprimes;
    for (auto aa : a) {
        if (aa == 1) continue;
        if (bigprimes.count(aa) > 0) continue;
        grundyxor = grundyxor ^ 1;
        bigprimes.insert(aa);
    }

    cout << (grundyxor == 0 ? "Arpa\n" : "Mojtaba\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

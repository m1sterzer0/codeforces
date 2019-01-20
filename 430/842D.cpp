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


struct solver {
    vector<ll> cnt;
    ll sz;
    ll n;
    ll m;

    void add(ll nn) { __add(1,nn,0,1 << 18); }

    void __add(ll idx, ll num, ll base, ll bitmask) {
        if (bitmask == 0) { cnt[idx] = 1; return; }
        if ( num >= base + bitmask ) { __add(2*idx+1, num, base+bitmask, bitmask>>1); }
        else                         { __add(2*idx,   num, base,         bitmask>>1); }
        cnt[idx] = cnt[2*idx] + cnt[2*idx+1];
    }

    ll mex(ll tag) {
        ll idx = (1 << 19) + tag;
        if (cnt[idx] == 0) return 0;
        idx = idx >> 1;
        ll found = 1;
        ll expected = 2;
        while (cnt[idx] == expected) { found *= 2; expected *= 2; idx = idx >> 1; }
        if (found == 1) return found;
        return found + mex(tag ^ found);
    }

    void solve() {
        cnt.assign(1 << 20,0);
        cin >> n >> m;
        REP(i,n) { ll x; cin >> x; add(x); }
        ll tag = 0;
        //cout << cnt[524288] << " " << cnt[524289] << " " << cnt[524290] << " " << cnt[524291] << endl;
        REP(i,m) {
            ll x; cin >> x; tag = tag ^ x;
            ll ans = mex(tag);
            printf("%lld\n", ans);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("842D.in1","r",stdin);
    solver s;
    s.solve();
    return 0;
}

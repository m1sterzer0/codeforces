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

ll solveCase(ll x, vector<ll> &v) {
    if (v.front() >= x) return abs(x-v.front());
    if (v.back() <= x)  return abs(x-v.back());
    ll l = 0;
    ll r = v.size()-1;
    while (r-l > 1) {
        ll m = (r+l)/2;
        if (v[m] > x) r = m;
        else          l = m;
    }
    return min(abs(x-v[l]),abs(x-v[r]));
}

void solve() {
    ll n, m, q; cin >> n >> m >> q;
    ll sign = 1;
    ll asum = 0;
    vector<ll> b(m);
    vector<ll> bsums;
    REP(i,n) { ll a; cin >> a; asum += sign*a; sign *= -1; }
    REP(i,m) { cin >> b[i]; }

    sign = 1;
    ll endsign = n & 1 ? 1 : -1;
    ll bsum = 0;
    REP(i,n) { bsum += sign*b[i]; sign *= -1; }
    bsums.push_back(bsum);

    FORE(i,n,m-1) {
        bsum = -1 * (bsum - b[i-n]) + endsign*b[i];
        bsums.push_back(bsum);
    }

    sort(bsums.begin(),bsums.end());

    printf("%lld\n", solveCase(asum,bsums));
    REP(i,q) {
        ll l,r,x; cin >> l >> r >> x;
        if ((l & 1) && (r & 1)) { asum += x; }
        else if  (!(l & 1) && !(r & 1)) { asum -= x; }
        printf("%lld\n", solveCase(asum,bsums));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("862E.in1","r",stdin);
    solve();
    return 0;
}

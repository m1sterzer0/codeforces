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

struct segTree {
    vector<ll> c;
    vector<ll> l;
    vector<ll> r;
    void init(ll lin, ll rin) {
        ll n = rin-lin+1;
        c.assign(4*n+7,0);
        l.assign(4*n+7,0);
        r.assign(4*n+7,0);
        _init(1,lin,rin);
    }

    void _init(ll idx, ll lin, ll rin) {
        l[idx] = lin;
        r[idx] = rin;
        if (lin != rin) {
            ll m = (lin+rin)/2;
            _init(idx+idx,lin,m);
            _init(idx+idx+1,m+1,rin);
        }
    }

    void add(ll x) { _add(1,x); }

    void _add(ll idx, ll x) {
        if (x < l[idx]) return;
        if (x > r[idx]) return;
        c[idx]++;
        if (l[idx] != r[idx]) {
            _add(idx+idx,x);
            _add(idx+idx+1,x);
        }
    }

    ll query(ll lin, ll rin) {
        return _query(1, lin, rin); }

    ll _query(ll idx, ll lin, ll rin) {
        if (rin < l[idx]) return 0;
        if (lin > r[idx]) return 0;
        if (lin <= l[idx] && r[idx] <= rin) return c[idx];
        return _query(idx+idx,lin,rin) + _query(idx+idx+1,lin,rin); 
    }
};

struct query { ll type; ll idx; ll b; ll t; ll r; };
bool operator<(const query &a, const query &b) { return a.r < b.r; }

inline ll choose2(ll x) { return x * (x-1) / 2; }

void solve() {
    ll n, q; cin >> n >> q;
    vector<query> qarr;
    vector<ll> ans(q,n * (n-1) / 2);
    vector<ll> p(n+1);
    FORE(i,1,n) cin >> p[i];
    segTree st;
    st.init(1,n);
    qarr.reserve(4*q);
    REP(i,q) {
        ll l,d,r,u; cin >> l >> d >> r >> u;
        ans[i] -= choose2(l-1);
        ans[i] -= choose2(n-r);
        ans[i] -= choose2(d-1);
        ans[i] -= choose2(n-u);
        if (l > 1 && d > 1) { qarr.push_back({1, i, 1,   d-1, l-1}); }
        if (l > 1 && u < n) { qarr.push_back({1, i, u+1, n,   l-1}); }
        if (r < n && d > 1) { qarr.push_back({2, i, 1,   d-1,   r}); }
        if (r < n && u < n) { qarr.push_back({2, i, u+1, n,     r}); }
    }
    sort(qarr.begin(),qarr.end());
    ll j = 0;
    FORE(i,1,n) {
        st.add(p[i]);
        while (j < (ll) qarr.size() && qarr[j].r == i) {
            ll cnt = st.query(qarr[j].b,qarr[j].t);
            ll idx = qarr[j].idx;
            if (qarr[j].type == 1) { ans[idx] += choose2(cnt); }
            else                   { ans[idx] += choose2(qarr[j].t - qarr[j].b + 1 - cnt); }
            j++;
        }
    }

//    REP(i,q) {cout << ans[i] << "\n"; }
    REP(i,q) {printf("%lld\n", ans[i]); } 

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("854E.myin2","r",stdin);
    solve();
    return 0;
}

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

struct rect {
    ll x1, y1, x2, y2;
    array<ll,11> ans;
};

struct segmentTree2D {
    vector<rect> t;
    ll maxx;
    ll maxy;
    ll c;

    void _init(ll idx, ll x1, ll y1, ll x2, ll y2) {
        t[idx].x1 = x1;
        t[idx].y1 = y1;
        t[idx].x2 = x2;
        t[idx].y2 = y2;
        REP(i,11) t[idx].ans[i] = 0;
        if (x2-x1 >= 1 && (x2-x1) >= (y2-y1)) {
            ll m = (x1+x2)/2;
            _init(2*idx,x1,y1,m,y2);
            _init(2*idx+1,m+1,y1,x2,y2);
        }
        else if (y2-y1 >= 1) {
            ll m = (y1+y2)/2;
            _init(2*idx,x1,y1,x2,m);
            _init(2*idx+1,x1,m+1,x2,y2);
        }
    }

    void _add(ll idx, ll x, ll y, ll b) {
        if       (x < t[idx].x1 || x > t[idx].x2) return;
        else if  (y < t[idx].y1 || y > t[idx].y2) return;
        REP(i,c) { t[idx].ans[i] += (b+i) % c; }
        if (t[idx].x1 == t[idx].x2 && t[idx].y1 == t[idx].y2) return;
        _add(2*idx,x,y,b);
        _add(2*idx+1,x,y,b); 
    }

    ll _sum(ll idx, ll x1, ll y1, ll x2, ll y2, ll tt) {
        if (x2 < t[idx].x1 || x1 > t[idx].x2) return 0LL;
        if (y2 < t[idx].y1 || y1 > t[idx].y2) return 0LL;
        if (x1 <= t[idx].x1 && x2 >= t[idx].x2 && y1 <= t[idx].y1 && y2 >= t[idx].y2) return t[idx].ans[tt%c];
        if (t[idx].x1 == t[idx].x2 && t[idx].y1 == t[idx].y2) { cerr << "Should not get here" << endl; exit(1); }
        return _sum(2*idx,x1,y1,x2,y2,tt) + _sum(2*idx+1,x1,y1,x2,y2,tt);
    }
    void init(ll n, ll x, ll y, ll cc) { t.resize(4*n+1); maxx = x; maxy=y; c = cc; _init(1,1,1,maxx,maxy); }
    void add(ll x, ll y, ll b)         { _add(1,x,y,b); }
    ll sum(ll x1, ll y1, ll x2, ll y2, ll tt) { return _sum(1,x1,y1,x2,y2,tt); }
};

void solve() {
    ll n,q,c; cin >> n >> q >> c;
    segmentTree2D z;
    z.init(10000,100,100,c+1);
    REP(i,n) { 
        ll x,y,s;
        cin >> x >> y >> s;
        z.add(x,y,s);
    }
    REP(i,q) {
        ll t,x1,y1,x2,y2;
        cin >> t >> x1 >> y1 >> x2 >> y2;
        ll ans = z.sum(x1,y1,x2,y2,t);
        printf("%lld\n", ans);
    } 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("835C.in1","r",stdin);
    solve();
    return 0;
}

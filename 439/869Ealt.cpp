#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
typedef int32_t  myint;
typedef int16_t  si;
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


struct COMPACTSEGTREE2DXOR {
    ll n;
    ll m;
    vector<ll> leftOffset;
    vector<vector<ll>> arr;
    vector<ll> xarr;  //Scratch for finding indices
    vector<ll> yarr;  //Scratch for finding indices

    COMPACTSEGTREE2DXOR(ll nin, ll min) {
        n = nin;
        m = min;
        calcSplits(max(m,n));
        arr.resize(2*n);
        REP(i,2*n) arr[i].assign(2*m,0LL);
    }

    // Midpoint split is a bit inefficient.
    // By modulating splits, we can shrink the size of the segment tree, which is
    // important for this problem
    void calcSplits(ll maxn) {
        leftOffset.assign(maxn+1,0LL);
        ll powa = 2;
        ll powb = 1;
        if (maxn >= 1) leftOffset[1] = 0;
        FORE(i,2,maxn) {
            ll s = i+1;
            if (s > 2 * powa)     { powa *= 2; powb *= 2; }
            if (s <= powa + powb) { leftOffset[i] = s - powb - 1; }
            else                  { leftOffset[i] = powa - 1;}
        }
    }

    void segTreeSearch(ll idx, ll l, ll r, ll r1, ll r2, vector<ll> &indices) {
        if (r2 < l || r1 > r) return;
        if (r1 <= l && r <= r2) { indices.push_back(idx); return; }
        ll m = l + leftOffset[r-l];
        segTreeSearch(idx << 1, l, m, r1, r2, indices);
        segTreeSearch((idx << 1) + 1, m+1, r, r1, r2, indices);
    }

    void segTreeSearch2(ll idx, ll l, ll r, ll r1, vector<ll> &indices) {
        indices.push_back(idx);
        if (l != r) {
            ll m = l + leftOffset[r-l];
            if (r1 <= m) segTreeSearch2(idx << 1,     l,   m, r1, indices);
            else         segTreeSearch2((idx << 1)+1, m+1, r, r1, indices);
        }
    }

    void add(ll r1, ll c1, ll r2, ll c2, ll val) {
        xarr.clear();
        yarr.clear();
        segTreeSearch(1,1,n,r1,r2,xarr);
        segTreeSearch(1,1,m,c1,c2,yarr);
        for (auto x : xarr) {
            for (auto y : yarr) {
                arr[x][y] ^= val;
            }
        }
        return;
    }

    ll query(ll r1, ll c1) {
        ll ans = 0;
        xarr.clear();
        yarr.clear();
        segTreeSearch2(1,1,n,r1,xarr);
        segTreeSearch2(1,1,m,c1,yarr);
        for (auto x : xarr) {
            for (auto y : yarr) {
                ans ^= arr[x][y];
            }
        }
        return ans;
    }
};


struct rect { ll r1; ll c1; ll r2; ll c2;};
bool operator< (const rect &a, const rect &b) { 
    if (a.r1 != b.r1) return a.r1 < b.r1;
    if (a.c1 != b.c1) return a.c1 < b.c1;
    if (a.r2 != b.r2) return a.r2 < b.r2;
    if (a.c2 != b.c2) return a.c2 < b.c2;
    return false;
}

void solve() {
    ll n, m, q; cin >> n >> m >> q;
    COMPACTSEGTREE2DXOR bb(n,m);
    map<rect,ll> rmap;
    mt19937 rng1(8161);
    uniform_int_distribution<ll> rdist(LLONG_MIN,LLONG_MAX);

    REP(i,q) {
        si t, r1, c1, r2, c2;
        cin >> t >> r1 >> c1 >> r2 >> c2;
        if (t == 1) {
            if (r2 < r1) swap(r1,r2);
            if (c2 < c1) swap(c1,c2);
            ll kk = rdist(rng1);
            rmap[{r1,c1,r2,c2}] = kk;
            bb.add(r1,c1,r2,c2,kk);
        }

        else if (t == 2) {
            if (r2 < r1) swap(r1,r2);
            if (c2 < c1) swap(c1,c2);
            ll kk = rmap[{r1,c1,r2,c2}];
            bb.add(r1,c1,r2,c2,kk);
        }

        else {
            ll q1 = bb.query(r1,c1);
            ll q2 = bb.query(r2,c2);
            cout << (q1 == q2 ? "Yes\n" : "No\n");
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("869E.in2","r",stdin);
    solve();
    return 0;
}

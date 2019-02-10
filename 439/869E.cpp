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


struct BIT2DXOR {
    ll n;
    ll m;
    vector<vector<ll>> arr;

    BIT2DXOR(ll nin, ll min) {
        n = nin;
        m = min;
        arr.resize(n+1);
        FORE(i,0,n) { arr[i].assign(m+1,0LL); }
    } 

    // Updates all rectangles from x,y to n,m with value (add or xor both work)
    void add(ll x, ll y, ll v) {
        for (ll xx = x; xx <= n; xx += (xx & -xx)) {
            for (ll yy = y; yy <= m; yy += (yy & -yy)) {
                arr[xx][yy] ^= v;
            }
        }
        return;
    }

    ll query(ll x, ll y) {
        ll ans = 0;
        for (ll xx = x; xx > 0; xx -= (xx & -xx)) {
            for (ll yy = y; yy > 0; yy -= (yy & -yy)) {
                ans ^= arr[xx][yy];
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
    BIT2DXOR bb1(n,m);
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
            bb1.add(r1,c1,kk);
            bb1.add(r1,c2+1,kk);
            bb1.add(r2+1,c1,kk);
            bb1.add(r2+1,c2+1,kk);
        }

        else if (t == 2) {
            if (r2 < r1) swap(r1,r2);
            if (c2 < c1) swap(c1,c2);
            ll kk = rmap[{r1,c1,r2,c2}];
            bb1.add(r1,c1,kk);
            bb1.add(r1,c2+1,kk);
            bb1.add(r2+1,c1,kk);
            bb1.add(r2+1,c2+1,kk);
        }

        else {
            ll q1 = bb1.query(r1,c1);
            ll q2 = bb1.query(r2,c2);
            cout << (q1 == q2 ? "Yes\n" : "No\n");
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("869E.in1","r",stdin);
    solve();
    return 0;
}

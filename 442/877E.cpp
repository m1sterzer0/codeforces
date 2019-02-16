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

struct CompactSegTree {
    ll n;
    vector<ll> leftOffset;
    vector<bool> invert;
    vector<ll>   on;
    CompactSegTree(ll nin) {
        n = nin;
        calcSplits(n);
        invert.assign(2*n,false);
        on.assign(2*n,0LL);
    }

    // Midpoint split is a bit space inefficient (esp for 2d seg tree)
    // By modulating splits, we can shrink the size of the segment tree.
    // This way, we always use exaclt 2n storage elements for segment tree
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


    void flip(ll left, ll right) { myflip(1,0,n-1,left,right); }
    ll query(ll left, ll right) { return myquery(1,0,n-1,left,right,false); }

    void myflip(ll idx, ll l, ll r, ll r1, ll r2) {
        if (r2 < l || r1 > r) return;
        if (r1 <= l && r <= r2) {
            invert[idx] = !invert[idx];
            on[idx] = (r-l+1) - on[idx];
            return;
        }
        ll m = l + leftOffset[r-l];
        myflip(idx << 1, l, m, r1, r2);
        myflip((idx << 1)+1, m+1, r, r1, r2);
        ll ssum = on[idx<<1] + on[(idx<<1) + 1];
        on[idx] = invert[idx] ? (r-l+1) - ssum : ssum;
    }

    ll myquery(ll idx, ll l, ll r, ll r1, ll r2, bool flip) {
        if (r2 < l || r1 > r) return 0LL;
        if (r1 <= l && r <= r2) { return flip ? (r-l+1) - on[idx] : on[idx]; }
        ll m = l + leftOffset[r-l];
        ll ans1 = myquery(idx << 1, l, m, r1, r2, flip ^ invert[idx]);
        ll ans2 = myquery((idx << 1) + 1, m+1, r, r1, r2, flip ^ invert[idx]);
        return ans1+ans2;
    }
};

void solve() {
    ll n; cin >> n;
    vector<vector<ll>> adj(n+1);
    FORE(j,2,n) { ll pi; cin >> pi; adj[j].push_back(pi); adj[pi].push_back(j); }
    vector<ll> eulerTour;
    vector<ll> eFirst(n+1);
    vector<ll> eLast(n+1);

    function<void(ll,ll)> dfs = [&](ll nn, ll par) {
        eFirst[nn] = (ll) eulerTour.size();
        eulerTour.push_back(nn);
        for (auto nn2 : adj[nn]) {
            if (nn2 == par) continue;
            dfs(nn2,nn);
        }
        eLast[nn] = (ll) eulerTour.size() - 1;
    };
    dfs(1,-1); // Do the euler tour;
    CompactSegTree st(n);
    FORE(i,1,n) { 
        ll ti;
        cin >> ti;
        if (ti == 1) st.flip(eFirst[i],eFirst[i]);
    }

    ll q; cin >> q;
    REP(i,q) {
        string s; ll nn;
        cin >> s >> nn;
        if (s[0] == 'g') { 
            ll ans = st.query(eFirst[nn],eLast[nn]);
            printf("%lld\n", ans);
        }
        else {
            st.flip(eFirst[nn],eLast[nn]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("877E.in7","r",stdin);
    solve();
    return 0;
}

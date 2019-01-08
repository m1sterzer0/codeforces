#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


// Assumes interval from 0 to n-1
struct sumQuerySegmentTree {
    ll n;
    vector<ll> t;

    void _buildVal(ll val, ll idx, ll l, ll r) { 
        if (l==r) t[idx] = val;
        else { ll m = (l+r)/2; _buildVal(val,2*idx,l,m); _buildVal(val,2*idx,m+1,r); t[idx] = t[2*idx] + t[2*idx+1]; } 
    }

    void _buildArr(vector<ll> &a, ll idx, ll l, ll r) { 
        if (l==r) t[idx] = a[l];
        else { ll m = (l+r)/2; _buildArr(a,2*idx,l,m); _buildArr(a,2*idx,m+1,r); t[idx] = t[2*idx] + t[2*idx+1]; } 
    }

    ll _sum(ll idx, ll l, ll r, ll ql, ll qr) {
        if (l == ql && r==qr) { return t[idx]; }
        ll m = (l+r)/2;
        return (ql <= m ? _sum(2*idx, l, m, ql, min(qr,m)) : 0LL) + (qr >= m+1 ? _sum(2*idx+1, m+1, r, max(ql,m+1), qr) : 0LL);
    }

    void _update(ll idx, ll l, ll r, ll uidx, ll val) {
        if (l == r) { t[idx] = val; }
        else { ll m = (l+r)/2; if (uidx <= m) _update(2*idx,l,m,uidx,val); else _update(2*idx+1,m+1,r,uidx,val); t[idx] = t[2*idx] + t[2*idx+1]; }
    }

    void initToValue(ll nin, ll val)         { n = nin; t.assign(4*n+1,0); _buildVal(val,1,0,n-1); }
    void initFromArr(ll nin , vector<ll> &a) { n = nin; t.assign(4*n+1,0); _buildArr(a,1,0,n-1); }
    ll sum(ll l, ll r)                       { return l>r ? 0LL : _sum(1, 0, n-1, l, r); }
    void update(ll idx, ll val)              { _update(1,0,n-1,idx,val); }

};

void solve() {
    ll n; cin >> n;
    map<ll,vector<ll>> posByValue;
    for (ll i = 0; i < n; i++) { ll v; cin >> v; posByValue[v].push_back(i); }
    ll last = n-1;
    ll ans = 0;
    sumQuerySegmentTree tr;
    tr.initToValue(n,0);
    for (const auto &myPair : posByValue) {
        auto v = myPair.first;
        ll bidx = -1;
        ll best = 0;
        for (auto p : posByValue[v]) {
            ll dist = (p - last + n) % n;
            if (dist == 0) dist = n;  // Special case for the first one.
            if (dist > best) { best = dist; bidx = p; }
        }
        //cout << "DEBUG: " << v << " " << best << " " << bidx << endl;

        if (bidx > last)      { ans += bidx - last -  tr.sum(last+1,bidx); }
        else if (last == n-1) { ans += 1LL + bidx - tr.sum(0,bidx); }
        else                  { ans += n - last + bidx - tr.sum(last+1,n-1) - tr.sum(0,bidx); }
        for (auto p : posByValue[v]) { tr.update(p,1); }
        last = bidx;
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("831E.in2","r",stdin);
    solve();
    return 0;
}

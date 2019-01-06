#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


// Modular Combinatorics
const ull mod = 1000000007;
inline ull madd(ull x, ull y) { ull r = x + y; if (r >= mod) { r -= mod; } return r; }
inline ull msub(ull x, ull y) { return x >= y ? x - y : x + mod - y; }
inline ull mmul(ull x, ull y) { return x * y % mod; }
inline ull mpow(ull x, ull p) { ull r=1; while (p) { if (p & 1) r = mmul(r,x); x = mmul(x,x); p = p >> 1; } return r; } 
inline ull minv(ull x) { return mpow(x,mod-2); }

void matrixmul(vector<vector<ull>> &a, vector<vector<ull>> &b, vector<vector<ull>> &ans) {
    ll n = (ll) a.size();
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            ull ss = 0;
            for (ll k = 0; k < n; k++) { ss = madd(ss,mmul(a[i][k], b[k][j])); }
            ans[i][j] = ss;
        }
    }
}

void matrixcopy(vector<vector<ull>> &a, vector<vector<ull>> &b) {
    ll n = (ll) a.size();
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            b[i][j] = a[i][j];
        }
    }
}

void assignIdentity(vector<vector<ull>> &a) {
    ll n = (ll) a.size();
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            a[i][j] = (i==j) ? 1 : 0;
        }
    }
}

void createSegmentTot(vector<vector<ull>> &ans, ll x, ll ci) {
    ll n = (ll) ans.size();
    vector<vector<ull>> segment(n);
    vector<vector<ull>> tempres(n);
    for (int i = 0; i < n; i++) { segment[i].assign(n,0); tempres[i].assign(n,0); }
    for (int i = 0; i <= ci; i++) {
        segment[i][i] = 1;
        if (i+1 < n) segment[i][i+1] = 1;
        if (i > 0)   segment[i][i-1] = 1;
    }
    assignIdentity(ans);
    while (x > 0) {
        if (x & 1) { matrixmul(segment,ans,tempres); matrixcopy(tempres,ans); }
        matrixmul(segment,segment,tempres); matrixcopy(tempres,segment);
        x = x >> 1;
    }
}

void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> a(n), b(n), c(n);
    for (ll i = 0; i < n; i++) { cin >> a[i] >> b[i] >> c[i]; }
    ll currentX = 0;
    ll segmentLen;
    vector<vector<ull>> running(16);
    vector<vector<ull>> running2(16);
    vector<vector<ull>> segmentTot(16);
    for (ll i = 0; i < 16; i++) { 
        running[i].assign(16,0);
        running2[i].assign(16,0);
        segmentTot[i].assign(16,0);
    } 
    assignIdentity(running);
    // Assume no zero-length segments
    for (ll i = 0; i < n; i++) {
        if (i == n-1) { segmentLen = k - currentX; }
        else          { segmentLen = (c[i] <= c[i+1]) ? (b[i] - currentX) : (b[i]-1-currentX); }
        if (segmentLen > 0) {
            createSegmentTot(segmentTot,segmentLen,c[i]);
            matrixmul(segmentTot,running,running2);
            matrixcopy(running2,running);
            currentX += segmentLen;
        }
    }
    cout << running[0][0] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("821E.in2","r",stdin);
    solve();
    return 0;
}

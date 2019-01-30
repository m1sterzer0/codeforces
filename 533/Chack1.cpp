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

//const ull mod = 1000000007;
//inline ull madd(ull x, ull y) { ull r = x + y; if (r >= mod) { r -= mod; } return r; }
//inline ull msub(ull x, ull y) { return x >= y ? x - y : x + mod - y; }
//inline ull mmul(ull x, ull y) { return x * y % mod; }
//inline ull mpow(ull x, ull p) { ull r=1; while (p) { if (p & 1) r = mmul(r,x); x = mmul(x,x); p = p >> 1; } return r; } 
//inline ull minv(ull x) { return mpow(x,mod-2); }

#define MOD 1000000007
ll mod(ll a, ll m=MOD) { a %=m; if (a<0) a += m; return a; }

void solve() {
    ll i,j,k,l,n,test_case,r;
    cin >> n >> l >> r;
    k = 1ll * n * l;
    l = r-l;
    k = k % 3;
    k = (3-k) % 3;
    ll c0,c1,c2;
    c0 = (l/3)+1;
    if (l % 3 == 0) { c1 = c0-1; c2 = c0-1; }
    else if (l % 3 == 1) { c1 = c0; c2 = c0-1; }
    else { c1 = c0; c2 = c0; }
    ll dp[n+1][3];
    memset(dp,0,sizeof dp);
    dp[0][0] = 1





    ll n, l , r;  cin >> n >> l >> r;
    vector<array<ll,3>> dp(n+1);
    REP(i,n+1) {
        REP (j,3) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    array<ll,3> opt;
    ll sz = r-l+1;
    opt[0] = sz/3;
    opt[1] = sz/3;
    opt[2] = sz/3;
    if (sz % 3 >= 1) { opt[l%3]++; }
    if (sz % 3 == 2) { opt[(l+1)%3]++; }
    REP(i,n) {
        dp[i+1][0] = madd(madd(mmul(dp[i][0],opt[0]),mmul(dp[i][1],opt[2])),mmul(dp[i][2],opt[1]));
        dp[i+1][1] = madd(madd(mmul(dp[i][1],opt[0]),mmul(dp[i][2],opt[2])),mmul(dp[i][0],opt[1]));
        dp[i+1][2] = madd(madd(mmul(dp[i][2],opt[0]),mmul(dp[i][0],opt[2])),mmul(dp[i][1],opt[1]));
    }
    cout << dp[n][0] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

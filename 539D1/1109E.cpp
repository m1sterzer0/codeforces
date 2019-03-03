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


// Modular Inverse Code from Geeks2Geeks
bool modInverse(ll a, ll m, ll &res) {
    ll x,y;
    ll g = gcdExtended(a,m,x,y);
    if (g != 1) return false;
    res = (x % m + m) % m;
    return true;
}

ll gcdExtended(ll a, ll b, ll &x, ll &y) {
    if (a == 0) { x = 0; y = 1; return b; }
    ll x1,y1;
    ll gcd = gcdExtended(b % a, a, x1, y1);
    x = y1 - (b/a) * x1;
    y = x1;
    return gcd;
}

struct CompactSegTree {
    ll n;
    ll mod;
    vector<ll> modPrimes;
    ll modPrimeLen;
    vector<ll> leftOffset;
    vector<vector<ll>> valModPrimes;
    vector<ll> multExtra;
    vector<vector<ll>> modPowArr;
    vector<ll> modInvArr;

    vector<vector<ll>> valModPrimeVals;
    vector<ll> multExtraVals;

    vector<ll> mult;
    vector<ll> sum;

    void init(ll nin, ll modin, vector<ll> &modPrimesIn) {
        n = nin;
        mod = modin;
        modPrimes = modPrimesIn;
        modPrimeLen = (ll) modPrimes.size();
        calcSplits(n);
        mult.assign(2*n,1LL);
        sum.assign(2*n,0LL);
        multExtra.assign(2*n,1LL);
        valModPrimes.resize(2*n);
        REP(i,2*n) { valModPrimes[i].assign(modPrimeLen,0LL); }

        multExtraVals.assign(100001,1LL);
        valModPrimeVals.resize(100001);

        FORE(i,2,100000) {
            valModPrimes[i].assign(modPrimeLen,0LL);
            ll v = i;
            bool found = false;
            REP(j,modPrimeLen) {
                if (i % modPrimes[j] == 0) {
                    found = true;
                    ll v = i / modPrimes[j];
                    valModPrimes[i] = valModPrimes[v];
                    valModPrimes[i][j]++;
                    multExtraVals[i] = multExtraVals[v];
                    break;
                }
            }
            if (!found) { multExtraVals[i] = i % mod; }
        }
        initModInv();
        initModPow();
    }

    void initModInv() {
        modInvArr.assign(1000001,-1);
        modInvArr[1] = 1;
        FORE(i,2,min(mod-1,100000LL)) {
            ll res;
            if (modInverse(i,mod,res)) modInvArr[i] = res;
        }
    }

    void initModPow() {
        modPowArr.resize(modPrimeLen);
        REP(i,modPrimeLen) {
            ll p = modPrimes[i];
            ll cnt = 0; ll x = p;
            while (x <= 100000L) { cnt++; x *= p; }
            modPowArr[i].assign(100000L * cnt + 1,1LL);
            FORE(j,1,cnt) modPowArr[i][j] = (modPowArr[i][j-1] * p) % mod;
        }
    }

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

    void populate(ll idx, ll val) { mypopulate(1,1,n,idx,val); }
    void mypopulate(ll idx, ll l, ll r, ll x, ll val) {
        if (l == r) {
            sum[idx] = val % mod;
            mult[idx] = val % mod;
            multExtra[idx] = multExtraVals[val];
            valModPrimes[idx] = valModPrimeVals[val];
        }

        else {
            ll m = l + leftOffset[r-l];
            ll lidx = idx << 1;
            ll ridx = lidx + 1;
            if (x <= m) { mypopulate(lidx, l, m, x, val); }
            else        { mypopulate(ridx, m+1, r, x, val); }
            sum[idx] = (sum[lidx] + sum[ridx]) % mod;
        }
    }

    void query1(ll left, ll right, ll x) { myquery1(1,1,n,left,right,x); }
    void myquery1(ll idx, ll l, ll r, ll xl, ll xr, ll x) {
        if (r < xl || xr < l) return;
        ll lidx = idx << 1;
        ll ridx = lidx + 1;
        if (xl <= l && r <= xr) {
            mult[idx] = (mult[idx] * x) % mod;
            multExtra[idx] = (multExtra[idx] * multExtraVals[x]) % mod;
            REP(j,modPrimeLen) { valModPrimes[idx][j] += valModPrimeVals[x][j]; }
            if (l == r) { sum[idx] = mult[idx]; }
            else  {
                sum[idx] = (sum[lidx] + sum[ridx]) % mod;
                sum[idx] = (sum[idx] * mult[idx]) % mod;
            }
        }
        else {
            ll m = l + leftOffset[r-l];
            myquery1(lidx,l,m,xl,xr,x);
            myquery1(ridx,m+1,r,xl,xr,x);
            sum[idx] = (sum[lidx] + sum[ridx]) % mod;
            sum[idx] = (sum[idx] * mult[idx]) % mod;
        }
    }

    void query2(ll p, ll x) { myquery2(1,1,n,p,x); }
    void myquery2(ll idx, ll l, ll r, ll p, ll x) {
        if (l == r) {
            multExtra[idx] = (multExtra[idx] * modInvArr[multExtraVals[x]]) % mod;
            REP(j,modPrimeLen) { valModPrimes[idx][j] -= valModPrimeVals[x][j]; }
            mult[idx] = 1LL;
            REP(j,modPrimeLen) mult[idx] = mult[idx] * modPowArr[j][valModPrimes[idx][j]] % mod;
            mult[idx] = mult[idx] * multExtra[idx] % mod;
            sum[idx] = mult[idx];
        }

        else {
            // Push Down Flow -- could do this based on a flag
            ll lidx = idx << 1;
            ll ridx = lidx + 1;
            ll m = l + leftOffset[r-l];
            multPushdown(lidx,idx);
            multPushdown(ridx,idx);
            mult[idx] = 1LL;
            multExtra[idx] = 1LL;
            REP(j,modPrimeLen) valModPrimes[idx][j] = 0LL;
            if (p <= m) {
                myquery2(lidx,l,m,p,x);
                multEval(ridx,m+1,r);
            }
            else {
                multEval(lidx,l,m);
                myquery2(ridx,m+1,r,p,x);
            }
            sum[idx] = (sum[lidx] + sum[ridx]) % mod;
        }
    }

    void multPushdown(ll c, ll p) {
        mult[c] = (mult[c] * mult[p]) % mod;
        multExtra[c] = (multExtra[c] * multExtra[p]) % mod;
        REP(j,modPrimeLen) valModPrimes[c][j] += valModPrimes[p][j];
    }

    void multEval(ll idx, ll l, ll r) {
        if (l == r) { sum[idx] = mult[idx]; }
        else { 
            ll lidx = idx << 1;
            ll ridx = lidx + 1;
            sum[idx] = (sum[lidx] + sum[ridx]) % mod;
            sum[idx] = (sum[idx] * mult[idx]) % mod;
        }
    }

    ll query3(ll left, ll right) { return myquery3(1,1,n,left,right); }
    ll myquery3(ll idx, ll l, ll r, ll xl, ll xr) {
        if (r < xl || xr < l)   return 0LL;
        if (xl <= l && r <= xr) return sum[idx];
         ll lidx = idx << 1;
        ll ridx = lidx + 1;
        ll m = l + leftOffset[r-l];
        return (myquery3(lidx,l,m,xl,xr) + myquery3(ridx,m+1,r,xl,xr)) % mod;
    }

};

struct factorSieve {
    vector<ll> factor;
    vector<ll> primes;
    void doit(ll n) {
        factor.resize(n+1);
        FORE(i,1,n) { factor[i] = i; }
        for (ll i = 4; i <= n; i += 2) { factor[i] = 2; }
        for (ll i = 9; i <= n; i += 6) { factor[i] = 3; }
        for (ll i = 5; i <= 100; i += 2) {
            if (factor[i] < i) { continue; }
            for (ll j = i * i; j <= n; j += i+i) { factor[j] = min(factor[j],i); }
        }
        primes.push_back(2LL);
        for (ll i = 3; i <= n; i += 2) {
            if (factor[i] < i) continue;
            primes.push_back(i);
        }
    }
};

struct solver {
    factorSieve fs;
    vector<ll> modPrimes;
    vector<ll> a;
    CompactSegTree st;
    void solve() {
        fs.doit(100000LL);
        ll n, mod;
        cin >> n >> mod;
        populateModPrimes(mod);
        st.init(n,mod,modPrimes);
        a.resize(n+1);
        FORE(i,1,n) { cin >> a[i]; st.populate(i,a[i]); }
        ll q; cin >> q;
        REP(i,q) {
            ll t; cin >> t;
            if (t == 1) {
                ll l,r,x;
                cin >> l >> r >> x;
                st.query1(l,r,x);
            }
            else if (t == 2) {
                ll p,x;
                cin >> p >> x;
                st.query2(p,x);
            }
            else if (t == 3) {
                ll l,r; cin >> l >> r;
                ll ans = st.query3(l,r);
                printf("%lld\n",ans);
            }
        }
    }

    void populateModPrimes(ll mod) {
        for (auto p : fs.primes) {
            if (mod % p == 0) {
                modPrimes.push_back(p);
                while (mod % p == 0) mod /= p;
                if (mod == 1) break;
            }
        }
        if (mod > 1) { modPrimes.push_back(mod); }
    }
};

void solve() {
    solver s;
    s.solve();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

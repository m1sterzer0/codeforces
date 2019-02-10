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

void calcLeftMax(ll n, vector<ll> &a, vector<ll> &leftMax) {
    vector<ll> st;
    REP(i,n) {
        while (!st.empty() && a[i] > a[st.back()]) st.pop_back();
        if (st.empty()) leftMax[i] = i;
        else            leftMax[i] = i - st.back() - 1; 
        st.push_back(i);
    }
}

void calcRightMax(ll n, vector<ll> &a, vector<ll> &rightMax) {
    vector<ll> st;
    for (ll i = n-1; i >= 0; i--) {
        while (!st.empty() && a[i] >= a[st.back()]) st.pop_back();
        if (st.empty()) rightMax[i] = n-1-i;
        else            rightMax[i] = st.back() - i -1;
        st.push_back(i);
    }
}

void calcLeftBoost(ll n, vector<ll> &a, vector<ll> &leftBoost) {
    array<ll,32> mask,best;
    REP(i,32) { mask[i] = 1 << i; best[i] = -1; }
    REP(i,n) {
        ll ans = -1;
        REP(j,32) {
            if ((mask[j] & a[i]) != 0) { best[j] = i; }
            else ans = max(ans,best[j]);
        }
        if (ans < 0) leftBoost[i] = infll;
        else         leftBoost[i] = i-ans;
    }
}

void calcRightBoost(ll n, vector<ll> &a, vector<ll> &rightBoost) {
    array<ll,32> mask,best;
    REP(i,32) { mask[i] = 1 << i; best[i] = infll; }
    for(ll i = n-1; i >= 0; i--) {
        ll ans = infll;
        REP(j,32) {
            if ((mask[j] & a[i]) != 0) { best[j] = i; }
            else ans = min(ans,best[j]);
        }
        if (ans > n) rightBoost[i] = infll;
        else         rightBoost[i] = ans-i;
    }
}

ll countCase(ll l, ll r, ll lb, ll rb) {
    ll ans = 0;
    if (l > 0 && lb <= l) ans += (l-lb+1) * (r+1);
    if (r > 0 && rb <= r) ans += (r-rb+1) * (l+1);
    if (l > 0 && lb <= l && r > 0 && rb <= r) ans -= (l-lb+1) * (r-rb+1);
    return ans;
}

void solve() {
    ll n; cin >> n;
    vector<ll> a(n);
    REP(i,n) { cin >> a[i]; }
    vector<ll> leftMax(n,-1), rightMax(n,-1), leftBoost(n,-1), rightBoost(n,-1);
    calcLeftMax(n,a,leftMax);
    calcRightMax(n,a,rightMax);
    calcLeftBoost(n,a,leftBoost);
    calcRightBoost(n,a,rightBoost);

    ll ans = 0;
    REP(i,n) { 
        ans += countCase(leftMax[i],rightMax[i],leftBoost[i],rightBoost[i]);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("876F.in1","r",stdin);
    solve();
    return 0;
}

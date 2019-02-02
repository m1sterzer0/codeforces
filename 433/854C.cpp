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

struct plane {
    ll idx;
    ll cost;
};
bool operator< (const plane &a, const plane &b) { return a.cost < b.cost; }

void solve() {
    ll n, k;
    cin >> n >> k;
    vector<ll> c(n+1);
    vector<ll> ans(n+1);
    priority_queue<plane, vector<plane>, less<plane>> mh;
    FORE(i,1,n) { cin >> c[i]; }
    FORE(i,1,n+k) {
        if (i <= n) { mh.push({i,c[i]}); }
        if (i > k) { 
            ll idx = mh.top().idx;
            mh.pop();
            ans[idx] = i;
        }
    }
    ll totcost = 0;
    FORE(i,1,n) { totcost += c[i] * (ans[i] - i); }
    cout << totcost << endl;
    FORE(i,1,n) { cout << ans[i] << " "; }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

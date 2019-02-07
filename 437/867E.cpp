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

void solve() {
    priority_queue<ll,vector<ll>,greater<ll>> mh;
    ll n; cin >> n;
    ll profit = 0;
    REP(i,n) {
        ll p; cin >> p; mh.push(p);
        if (p - mh.top() > 0) {
            // Here there is profit to be taken, but we don't know if we buy, hold, or sell today
            // We take the proft as if we sell today, but we put two copies of ourselves on the stack
            // If only one is popped, then we did nothing today, and we just broke the transaction into two pieces
            // If both are popped, than we actually bought today AND we broke a sell transaction into two pieces 
            profit += p - mh.top(); mh.pop(); mh.push(p);  } 
    }
    cout << profit << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("867E.in2","r",stdin);
    solve();
    return 0;
}

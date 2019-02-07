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


struct person {
    ll h;
    ll s;
};
bool operator< (const person &a, const person &b) { return a.h < b.h || (a.h == b.h && a.s < b.s); }

ll solveCase(ll s, vector<person> &p) {
    ll ans = 0;
    for (auto pp : p) {
        if (s > pp.s) { s -= pp.s; ans += pp.s * pp.h; }
        else          { ans += s * pp.h; break; }
    }
    return ans;
}

void solve() {
    ll N, S; cin >> N >> S;
    vector<person> pizza1;
    vector<person> pizza2;
    ll baseHappiness = 0;
    ll stot = 0;
    ll idealP1slices = 0;
    ll idealP2slices = 0;
    REP(i,N) {
        ll s,a,b; cin >> s >> a >> b;
        stot += s;
        baseHappiness += s * min(a,b);
        if (a > b) { pizza1.push_back({a-b,s}); idealP1slices += s;}
        else       { pizza2.push_back({b-a,s}); idealP2slices += s;}
    }
    sort(pizza1.begin(),pizza1.end());
    sort(pizza2.begin(),pizza2.end());
    reverse(pizza1.begin(),pizza1.end());
    reverse(pizza2.begin(),pizza2.end());

    ll ans;
    ll numPizzas = (stot + S - 1) / S;
    ll minPizza1 = idealP1slices / S;
    ll minPizza2 = idealP2slices / S;
    if      (minPizza1 + minPizza2     == numPizzas) { ans = baseHappiness + solveCase(minPizza1*S,     pizza1) + solveCase(minPizza2*S,     pizza2); }
    else if (minPizza1 + minPizza2 + 2 == numPizzas) { ans = baseHappiness + solveCase(minPizza1*S + S, pizza1) + solveCase(minPizza2*S + S, pizza2); }
    else {
        ll ans1 = baseHappiness + solveCase(minPizza1*S + S, pizza1) + solveCase(minPizza2*S, pizza2);
        ll ans2 = baseHappiness + solveCase(minPizza1*S, pizza1) + solveCase(minPizza2*S + S, pizza2);
        ans = max(ans1,ans2);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

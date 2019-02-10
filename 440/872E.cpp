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

// Modular Combinatorics
const ull mod = 1000000007;
inline ull madd(ull x, ull y) { ull r = x + y; if (r >= mod) { r -= mod; } return r; }
inline ull msub(ull x, ull y) { return x >= y ? x - y : x + mod - y; }
inline ull mmul(ull x, ull y) { return x * y % mod; }
inline ull mpow(ull x, ull p) { ull r=1; while (p) { if (p & 1) r = mmul(r,x); x = mmul(x,x); p = p >> 1; } return r; } 
inline ull minv(ull x) { return mpow(x,mod-2); }

struct solver {
    ll n;
    vector<ll> px, py;
    vector<bool> visited;
    ll ans = 1;
    set<ll> xvals;
    set<ll> yvals;
    map<ll,set<ll>> x2points;
    map<ll,set<ll>> y2points;
    ll points;

    void solve() {
        cin >> n;
        px.assign(n,0);
        py.assign(n,0);
        visited.assign(n,false);
        REP(i,n) { cin >> px[i] >> py[i]; x2points[px[i]].insert(i); y2points[py[i]].insert(i); }
        REP(i,n) {
            if (visited[i]) continue;
            xvals.clear();
            yvals.clear();
            points = 0;
            dfs(i);
            ll lines = (ll) xvals.size() + (ll) yvals.size();
            ll w = mpow(2,lines);
            if (lines > points) w = msub(w,1); // If we don't have enough points to activate all of the lines, we lose the case where all the lines are on, but that is it.
            ans = mmul(ans,w);
        }
        cout << ans << endl;
    }

    void dfs(ll nn) {
        visited[nn] = true;
        points++;
        if (xvals.count(px[nn]) == 0) {
            xvals.insert(px[nn]);
            for (auto nn2 : x2points[px[nn]]) {
                if (visited[nn2]) continue;
                dfs(nn2);
            }
        }
        if (yvals.count(py[nn]) == 0) {
            yvals.insert(py[nn]);
            for (auto nn2 : y2points[py[nn]]) {
                if (visited[nn2]) continue;
                dfs(nn2);
            }
        }
    } 
};

void solve() {
    solver sv;
    sv.solve();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

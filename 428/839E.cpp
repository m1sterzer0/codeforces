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

struct solver {
    vector<ll> nodeStack;
    array<array<ll,41>,41> gmat;
    ll n, k;
    ll minFound;

    // Dumb max clique size finder
    void dfs(ll nn) {
        bool good = true;
        if (minFound >= (ll) nodeStack.size() + (n-nn+1)) return;
        for (auto k : nodeStack) {
            if (gmat[k][nn] == 0) { good = false; break; }
        }
        if (good) {
            nodeStack.push_back(nn);
            minFound = max(minFound,(ll) nodeStack.size());
            if (nn < n) dfs(nn+1);
            nodeStack.pop_back();
        }
        if (nn < n) dfs(nn+1);
    }

    void solve() {
        cin >> n >> k;
        FORE(i,1,n) {
            FORE(j,1,n) {
                cin >> gmat[i][j];
            }
        }
        minFound = 0;
        dfs(1);
        //cout << "DEBUG: " << minFound << endl;
        double ans = (double) k * (double) k * 0.5 * (double) (minFound - 1) / (double) minFound;
        cout << ans << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("839E.in4","r",stdin);
    //solve();
    solver s;
    s.solve();
    return 0;
}

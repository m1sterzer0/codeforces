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


struct twoSat {
    ll n;
    vector<vector<ll>> adj;
    vector<vector<ll>> adjInv;
    vector<bool> visited;
    vector<ll> sscnum;
    vector<ll> s;
    ll counter;

    bool doit (ll nin, vector<pair<ll,ll>> &orterms, vector<bool> &sol) {
        // Step 1, set up the graph.
        // Coming in, positives represent true variables and negatives represent false variables
        // Internally, variables 1-n represent true variables and variables n+1-2n represent false variables
        n = nin;
        adj.clear();
        adj.resize(2*n+1);
        sscnum.assign(2*n+1,0);
        for (auto p : orterms) {
            ll first     = p.first > 0 ? p.first : n - p.first;
            ll second    = p.second > 0 ? p.second : n - p.second;
            ll notfirst  = first <= n ? first + n : first - n;
            ll notsecond = second <= n ? second + n : second - n;
            adj[notfirst].push_back(second);
            adj[notsecond].push_back(first); 
        }

        // Step 2, do kosaraju
        kosaraju();

        // Step 3, do variable assignments
        sol.assign(2*n+1,false);
        vector<vector<ll>> ssc(counter);
        FORE(i,1,n)   { if (sscnum[i] == sscnum[n+i]) return false; }
        FORE(i,1,2*n) { ssc[sscnum[i]].push_back(i); }
        REP(i,counter) {
            bool sscval = false;
            for (auto nn : ssc[i]) {
                if (sol[nn]) { sscval = true; break; } 
            }
            for (auto nn : ssc[i]) {
                sol[nn] = sscval;
                if (nn <= n) sol[nn+n] = !sscval;
                else         sol[nn-n] = !sscval;
            }
        }
        sol.resize(n+1);  //Discard the "false" variables -- don't need them
        return true;
    }

    void kosaraju() {
        visited.assign(2*n+1,false);
        s.clear();
        counter = 0;
        makeInv();
        FORE(nn,1,2*n) { if (!visited[nn]) dfs1(nn); }
        visited.assign(2*n+1,false);
        reverse(s.begin(),s.end());
        for (auto nn : s) { if (!visited[nn]) { dfs2(nn); counter++; } }
    }

    void makeInv() {
        adjInv.clear();
        adjInv.resize(2*n+1);
        FORE(nn,1,2*n) {
            for (auto nn2 : adj[nn]) { adjInv[nn2].push_back(nn); }
        }
    } 

    void dfs1(ll nn) {
        if (visited[nn]) return;
        visited[nn] = true;
        for (auto nn2 : adj[nn]) dfs1(nn2);
        s.push_back(nn);
    }

    void dfs2(ll nn) {
        if (visited[nn]) return;
        visited[nn] = true;
        for (auto nn2 : adjInv[nn]) dfs2(nn2);
        sscnum[nn] = counter;
    }
};

// This is just a 2sat problem -- so just haul out the infrastructure
void solve() {
    ll n, m; cin >> n >> m;
    vector<pair<ll,ll>> orterms;
    vector<ll> lb, cb;
    ll li; cin >> li;
    REP(i,li) { ll c; cin >> c; lb.push_back(c); }
    FOR(b,1,n) {
        cin >> li;
        REP(i,li) { ll c; cin >> c; cb.push_back(c); }

        bool good = false;
        ll comChars = min((ll) lb.size(), (ll) cb.size());
        REP(i,comChars) {
            if (lb[i] == cb[i]) continue;
            good = true;
            if (lb[i] < cb[i]) {
                // Here, we either need to NOT capitalize cb[i] OR we need to capitalize lb[i]
                orterms.push_back({lb[i],-cb[i]});
            }
            else {
                // Here we MUST capitalize lb[i], AND we must NOT capitalize cb[i]
                orterms.push_back({lb[i],lb[i]});
                orterms.push_back({-cb[i],-cb[i]});
            }
            break;
        }
        if (!good && cb.size() < lb.size()) { printf("No\n"); return; }
        lb = cb;
        cb.clear();
    }
    
    vector<bool> sol;
    twoSat ts;
    bool res = ts.doit(m,orterms,sol);
    if (!res) { printf("No\n"); return; }
    printf("Yes\n");
    ll ncaps = 0;
    FORE(i,1,m) { if (sol[i]) ncaps++; }
    printf("%lld\n", ncaps);
    FORE(i,1,m) { if (sol[i]) printf("%lld ", i); }
    printf("\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("876E.in1","r",stdin);
    solve();
    return 0;
}

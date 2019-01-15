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

struct diag { ll a; ll b; ll sz; };
bool operator< (const diag &a, const diag &b) { return a.sz < b.sz || (a.sz == b.sz && a.a < b.a) || (a.sz == b.sz && a.a == b.a && a.b < b.b); }
struct region { ll idx; vector<ll> v; ll color;};
bool regionCmp (const region &a, const region &b) { return a.v[0] < b.v[0] || (a.v[0] == b.v[0] && a.v[1] < b.v[1]) || (a.v[0] == b.v[0] && a.v[1] == b.v[1] && a.v[2] < b.v[2]); }

// Dividing polygon into region tree
struct solver {
    ll n; ll m;
    vector<bool>       blocked;
    vector<vector<ll>> regTree;
    vector<vector<ll>> cdt;
    ll                 cdtRoot;
    vector<ll>         cdtNodeSize;
    vector<diag>       diags;
    vector<region>     regions;
    map<pair<ll,ll>,ll> diagToRegion;

    void read() {
        cin >> n >> m;
        diags.resize(m);
        REP(i,m) { 
            ll a,b;
            cin >> a >> b;
            if (a > b) swap(a,b);
            diags[i].a = a;
            diags[i].b = b;
            diags[i].sz = min(b-a,n+a-b);
        }
    }

    void genRegionTree() {
        regTree.resize(m+1);
        regions.resize(m+1);
        REP(i,m+1) regions[i].idx = i;
        vector<ll> nxt(n+1);
        FORE(i,1,n) nxt[i] = i == n ? 1 : i+1;
        sort(diags.begin(),diags.end());
        ll regidx = 0;
        ll start,end,node,otherRegion;
        for (auto d : diags) {
            diagToRegion[{d.a,d.b}] = regidx;
            diagToRegion[{d.b,d.a}] = regidx;
            if (d.b - d.a == d.sz) { start=d.a; end=d.b; }
            else                   { start=d.b; end=d.a; }
            regions[regidx].v.PB(end);
            ll node = start;
            while (node != end) {
                regions[regidx].v.PB(node);
                ll nextNode = nxt[node];
                if (nextNode - node != 1 && !(node == n && nextNode == 1)) { // Found a diagonal, so need an edge to another region
                    otherRegion = diagToRegion[{node,nextNode}];
                    regTree[regidx].PB(otherRegion);
                    regTree[otherRegion].PB(regidx);
                }
                node = nextNode;
            }
            nxt[start] = end;
            regidx++;
        } 
        // One more loop for the remaining region index;
        swap(start,end);
        regTree[regidx].PB(regidx-1);
        regTree[regidx-1].PB(regidx);
        node = start;
        regions[regidx].v.PB(end);
        while (node != end) {
            regions[regidx].v.PB(node);
            ll nextNode = nxt[node];
            if (nextNode - node != 1 && !(node == n && nextNode == 1)) { // Found a diagonal, so need an edge to another region
                otherRegion = diagToRegion[{node,nextNode}];
                regTree[regidx].PB(otherRegion);
                regTree[otherRegion].PB(regidx);
            }
            node = nextNode;
        }
    }

    void cdt1(ll nn, ll par) {
        cdtNodeSize[nn] = 1;
        for (auto nn2 : regTree[nn]) {
            if (nn2 == par || blocked[nn2]) continue;
            cdt1(nn2,nn);
            cdtNodeSize[nn] += cdtNodeSize[nn2];
        }
    }

    ll cdt2(ll nn, ll par, ll szlim) {
        for (auto nn2 : regTree[nn]) {
            if (nn2 == par || blocked[nn2]) continue;
            if (cdtNodeSize[nn2] > szlim) return cdt2(nn2, nn, szlim);
        }
        return nn;
    }

    void genCetroidDecompTree() {
        blocked.resize(m+1);
        cdtNodeSize.resize(m+1);
        cdt.resize(m+1);
        REP(i,m+1) blocked[i] = false;
        vector<pair<ll,ll>> st;
        st.PB({0,-1});
        while (!st.empty()) {
            ll nn = st.back().first;
            ll par = st.back().second;
            st.pop_back();
            if (blocked[nn]) continue;
            cdt1(nn,-1);
            ll centroid = cdt2(nn,-1,cdtNodeSize[nn]/2);
            blocked[centroid] = true;
            if (par == -1) cdtRoot = centroid;
            else           cdt[par].PB(centroid);
            for (auto nn2 : regTree[centroid]) { st.PB({nn2,centroid}); }
        }
    }

    void assignColors() {
        vector<pair<ll,ll>> st;
        st.PB({cdtRoot,1});
        while (!st.empty()) {
            ll nn = st.back().first;
            ll cc = st.back().second;
            st.pop_back();
            regions[nn].color = cc;
            for (auto nn2 : cdt[nn]) { st.PB({nn2,cc+1}); }
        }
    }

    // TODO: Need to sort based on importance now
    void dealWithImportance() {
        for (auto &r : regions) { sort(r.v.begin(),r.v.end()); reverse(r.v.begin(),r.v.end()); }
        sort(regions.begin(),regions.end(),regionCmp);
    }

    void solve() {
        read();
        if (m == 0) { cout << 1 << endl; return; }
        genRegionTree();
        genCetroidDecompTree();
        assignColors();
        dealWithImportance();
        for (auto r : regions) { cout << r.color << " "; }
        cout << endl;
    }

};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    solver s;
    //freopen("776F.in2","r",stdin);
    s.solve(); 
    return 0;
}

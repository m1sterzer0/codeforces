#include <bits/stdc++.h>
using namespace std;

// Convention is to used unsigned ints for nodes
// Inverse nodes are given by node + offset

struct twoSatStruct {
    uint32_t offset;
    map<uint32_t,set<uint32_t>> adj;
    map<uint32_t,set<uint32_t>> adjInv;
    set<uint32_t> visited;
    vector<uint32_t> nodevec;
    map<uint32_t,uint32_t> sscnum;
    vector<uint32_t> s;
    uint32_t counter;

    bool twoSat(vector<pair<uint32_t,uint32_t>> &orterms,
                uint32_t offsetin,
                map<uint32_t,bool> &sol);

    private: 
    void prework(vector<pair<uint32_t,uint32_t>> &orterms);
    void kosaraju();
    void makeInv();
    void dfs1(uint32_t n);
    void dfs2(uint32_t n);
    bool postwork(map<uint32_t,bool> &sol);
};

bool twoSatStruct::twoSat(vector<pair<uint32_t,uint32_t>> &orterms,
                          uint32_t offsetin,
                          map<uint32_t,bool> &sol) {
    offset = offsetin;
    prework(orterms);
    kosaraju();
    bool res = postwork(sol);
    return res;
}

void twoSatStruct::prework(vector<pair<uint32_t,uint32_t>> &orterms) {
    set<uint32_t> nodes;
    adj.clear();
    for (auto p : orterms) {
        uint32_t notfirst  = p.first  < offset ? p.first  + offset : p.first  - offset;
        uint32_t notsecond = p.second < offset ? p.second + offset : p.second - offset;
        adj[notfirst].insert(p.second);
        adj[notsecond].insert(p.first);
        nodes.insert(p.first);
        nodes.insert(p.second);
        nodes.insert(notfirst);
        nodes.insert(notsecond);
    }
    nodevec.clear();
    for (auto n : nodes) { nodevec.push_back(n); }
}

void twoSatStruct::kosaraju() {
    visited.clear();
    s.clear();
    sscnum.clear();
    counter = 0;
    makeInv();
    for (auto n : nodevec) { if (visited.find(n) == visited.end()) dfs1(n); }
    visited.clear();
    for (auto it = s.rbegin(); it != s.rend(); it++) {
        auto n = *it;
        if (visited.find(n) == visited.end()) { dfs2(n); counter += 1;}
    }
}

void twoSatStruct::makeInv() {
    adjInv.clear();
    for (auto const& x : adj) {
        auto n = x.first;
        for (auto nn : x.second) {
            adjInv[nn].insert(n);
        }
    }
}

void twoSatStruct::dfs1(uint32_t n) {
    if (visited.find(n) != visited.end()) { return; }
    visited.insert(n);
    for (auto nn : adj[n]) dfs1(nn);
    s.push_back(n);
}

void twoSatStruct::dfs2(uint32_t n) {
    if (visited.find(n) != visited.end()) { return; }
    visited.insert(n);
    for (auto nn : adjInv[n]) dfs2(nn);
    sscnum[n] = counter;
}

bool twoSatStruct::postwork(map<uint32_t,bool> &sol) {
    sol.clear();
    vector<set<uint32_t>> ssc(counter);
    // This checks for the failure of the twosat
    for (auto n : nodevec) {
        if (n < offset  && sscnum[n] == sscnum[n+offset]) return false;
        if (n >= offset && sscnum[n] == sscnum[n-offset]) return false;
    }

    // Now we know we are satisfyable, so we initialize everything to false and then
    // only set loops to true as we must 
    for (auto n : nodevec) { ssc[sscnum[n]].insert(n); sol[n] = false; }

    for (int i = 0; i < counter; i++) {
        bool sscval = false;
        for (auto n : ssc[i]) {
            if (sol[n]) { sscval = true; break; }
        }
        for (auto n : ssc[i]) {
            sol[n] = sscval;
            if (n < offset) { sol[n+offset] = !sscval; }
            else            { sol[n-offset] = !sscval; }
        }
    }
    return true;
}

void solve() {
    uint32_t n,m; cin >> n >> m;
    int x,y;
    vector<bool> roomStart(n+1);
    for (uint32_t i = 1; i <= n; i++) { cin >> x; roomStart[i] = (x == 1); }
    vector<vector<uint32_t>> roomSwitches(n+1);
    for (uint32_t i = 0; i < m; i++) { 
        cin >> x;
        for (uint32_t j = 0; j < x; j++) {
            cin >> y;
            //cout << "DEBUG " << i << " " << x << " " << j << " " << y << endl;
            roomSwitches[y].push_back(i);
        }
    }
    vector<pair<uint32_t,uint32_t>> orterms;
    for (uint32_t i = 1; i <= n; i++) {
        if (roomStart[i]) {
            orterms.push_back({roomSwitches[i][0],   roomSwitches[i][1]+m} );
            orterms.push_back({roomSwitches[i][0]+m, roomSwitches[i][1]}   );
        } else {
            orterms.push_back({roomSwitches[i][0],   roomSwitches[i][1]}   );
            orterms.push_back({roomSwitches[i][0]+m, roomSwitches[i][1]+m} );
        }
    }
    twoSatStruct t;
    map<uint32_t,bool> sol;
    bool res = t.twoSat(orterms,m,sol);
    cout << (res ? "YES" : "NO") << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("776C.in1","r",stdin);
    solve();
    return 0;
}
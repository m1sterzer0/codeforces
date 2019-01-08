#include <bits/stdc++.h>
using namespace std;


// Here, we expect nodes from 0 to 2*offset-1
struct twoSatStruct {
    uint32_t offset;
    vector<vector<uint32_t>> adj;
    vector<vector<uint32_t>> adjInv;
    set<uint32_t> visited;
    vector<uint32_t> sscnum;
    vector<uint32_t> s;
    uint32_t counter;
    bool errflag;

    bool twoSat(vector<pair<uint32_t,uint32_t>> &orterms,
                uint32_t offsetin,
                vector<bool> &sol);

    bool twoSatXOR(vector<pair<uint32_t,uint32_t>> &orterms,
                   uint32_t offsetin,
                   vector<bool> &sol);

    private: 
    void prework(vector<pair<uint32_t,uint32_t>> &orterms);
    void kosaraju();
    bool greedyAssignment(vector<bool> &sol);
    void makeInv();
    void dfs1(uint32_t n);
    void dfs2(uint32_t n);
    void dfs3(uint32_t n, vector<bool> &sol);
    bool postwork(vector<bool> &sol);
};

bool twoSatStruct::twoSat(vector<pair<uint32_t,uint32_t>> &orterms,
                          uint32_t offsetin,
                          vector<bool> &sol) {
    offset = offsetin;
    prework(orterms);
    kosaraju();
    bool res = postwork(sol);
    return res;
}

bool twoSatStruct::twoSatXOR(vector<pair<uint32_t,uint32_t>> &orterms,
                             uint32_t offsetin,
                             vector<bool> &sol) {
    offset = offsetin;
    prework(orterms);
    return greedyAssignment(sol);
}

void twoSatStruct::prework(vector<pair<uint32_t,uint32_t>> &orterms) {
    adj.clear();
    adj.resize(2*offset);
    for (auto p : orterms) {
        uint32_t notfirst  = p.first  < offset ? p.first  + offset : p.first  - offset;
        uint32_t notsecond = p.second < offset ? p.second + offset : p.second - offset;
        adj[notfirst].push_back(p.second);
        adj[notsecond].push_back(p.first);
    }
}

bool twoSatStruct::greedyAssignment(vector<bool> &sol) {
    visited.clear();
    sol.clear();
    sol.resize(2*offset,false);
    errflag = false;
    for (uint32_t n = 0; n < 2*offset; n++) {sol[n] = false; } 
    for (uint32_t n = 0; n < 2*offset; n++) { 
        if (visited.find(n) == visited.end()) { dfs3(n,sol); }
        if (errflag) { return false; }
    }
    return true;
}

void twoSatStruct::kosaraju() {
    visited.clear();
    s.clear();
    sscnum.clear();
    counter = 0;
    makeInv();
    for (uint32_t n = 0; n < 2*offset; n++) {
        if (visited.find(n) == visited.end()) dfs1(n);
    }
    visited.clear();
    for (auto it = s.rbegin(); it != s.rend(); it++) {
        auto n = *it;
        if (visited.find(n) == visited.end()) { dfs2(n); counter += 1;}
    }
}

void twoSatStruct::makeInv() {
    adjInv.clear();
    adjInv.resize(2*offset);
    for (uint32_t n = 0; n < 2*offset; n++) {
        for (auto nn : adj[n]) {
            adjInv[nn].push_back(n);
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

void twoSatStruct::dfs3(uint32_t n, vector<bool> &sol) {
    //cout << "DEBUG " << n << endl;
    sol[n] = true;
    if (n < offset) {
        if (sol[n+offset]) { errflag = true; return; }
        else               { visited.insert(n); visited.insert(n+offset); }
    }  else {
        if (sol[n-offset]) { errflag = true; return; }
        else               { visited.insert(n); visited.insert(n-offset); }
    }
    for (auto nn : adj[n]) {
        if (visited.find(nn) == visited.end()) { dfs3(nn,sol); if (errflag) return; }
        else if (!sol[nn]) { errflag = true; return; }
    }
}

bool twoSatStruct::postwork(vector<bool> &sol) {
    sol.clear();
    vector<vector<uint32_t>> ssc(counter);
    // This checks for the failure of the twosat
    for (uint32_t n = 0; n < 2*offset; n++) {
        if (n < offset  && sscnum[n] == sscnum[n+offset]) return false;
        if (n >= offset && sscnum[n] == sscnum[n-offset]) return false;
    }

    // Now we know we are satisfyable, so we initialize everything to false and then
    // only set loops to true as we must 
    for (uint32_t n = 0; n < 2*offset; n++) { ssc[sscnum[n]].push_back(n); sol[n] = false; }

    for (uint32_t i = 0; i < counter; i++) {
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
    uint32_t x,y;
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
    vector<bool> sol;
    bool res = t.twoSatXOR(orterms,m,sol);
    cout << (res ? "YES" : "NO") << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("776C.in1","r",stdin);
    solve();
    return 0;
}
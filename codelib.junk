#include <bits/stdc++.h>
using namespace std;


struct twoSatStructMap {
    uint32_t offset;
    map<uint32_t,set<uint32_t>> adj;
    map<uint32_t,set<uint32_t>> adjInv;
    set<uint32_t> visited;
    vector<uint32_t> nodevec;
    map<uint32_t,uint32_t> sscnum;
    vector<uint32_t> s;
    uint32_t counter;
    bool errflag;

    bool twoSat(vector<pair<uint32_t,uint32_t>> &orterms,
                uint32_t offsetin,
                map<uint32_t,bool> &sol);

    bool twoSatXOR(vector<pair<uint32_t,uint32_t>> &orterms,
                   uint32_t offsetin,
                   map<uint32_t,bool> &sol);



    private: 
    void prework(vector<pair<uint32_t,uint32_t>> &orterms);
    void kosaraju();
    bool greedyAssignment(map<uint32_t,bool> &sol);
    void makeInv();
    void dfs1(uint32_t n);
    void dfs2(uint32_t n);
    void dfs3(uint32_t n, map<uint32_t,bool> &sol);
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

bool twoSatStruct::twoSatXOR(vector<pair<uint32_t,uint32_t>> &orterms,
                             uint32_t offsetin,
                             map<uint32_t,bool> &sol) {
    offset = offsetin;
    prework(orterms);
    return greedyAssignment(sol);
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

bool twoSatStruct::greedyAssignment(map<uint32_t,bool> &sol) {
    visited.clear();
    errflag = false;
    for (auto n : nodevec) {sol[n] = false; } 
    for (auto n : nodevec) { 
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

void twoSatStruct::dfs3(uint32_t n, map<uint32_t,bool> &sol) {
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

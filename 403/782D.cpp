#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

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
    sscnum.clear();
    sscnum.resize(2*offset,0);
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
    sol.resize(2*offset,false);
    vector<vector<uint32_t>> ssc(counter);
    // This checks for the failure of the twosat
    for (uint32_t n = 0; n < 2*offset; n++) {
        if (n < offset  && sscnum[n] == sscnum[n+offset]) return false;
        if (n >= offset && sscnum[n] == sscnum[n-offset]) return false;
    }

    // Now we know we are satisfyable, so we initialize everything to false and then
    // only set loops to true as we must 
    for (uint32_t n = 0; n < 2*offset; n++) { ssc[sscnum[n]].push_back(n); sol[n] = false; }

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
    int n;  cin >> n;
    vector<string> optiona(n);
    vector<string> optionb(n);
    string a,b;
    for (uint32_t i = 0; i < n; i++) {
        cin >> a;
        cin >> b;
        optiona[i] = a.substr(0,3);
        optionb[i] = a.substr(0,2) + b.substr(0,1);
    }

    map<string,vector<uint32_t>> firstVals;
    map<string,vector<uint32_t>> secondVals;
    for (uint32_t i = 0; i < n; i++) {
        firstVals[optiona[i]].push_back(i);
        secondVals[optionb[i]].push_back(i);
    }

    // Just do raw 2sat first -- special case 2 sat is probably faster, but this is good enough
    // Rule 1a: If I choose my first value, then anyone with a matching first value must choose their second value.
    // Rule 1b: If I choose my second value, then anyone with a matching second value must choose their first value.
    // Rule 1c: If I choose my first value, then anyone with a matching second value must choose their first value.
    // Rule 1d: If I choose my second value, then anyone with a matching first value must choose their second value.
    // Rule 2:  If I choose my second value, then any club whose first value matches my first value must also choose its

    vector<pair<uint32_t,uint32_t>> constraints;
    for (uint32_t i = 0; i < n; i++) {
        if (firstVals[optiona[i]].size() > 1) { constraints.push_back({n+i,n+i}); }                  // Rule 1a + Rule2 implies clubs with matching first values must both choose their second value.
        //for (auto j : firstVals[optiona[i]])  { if (j != i) { constraints.push_back({i+n,j+n}); } }  // Rule 1a: i --> !j which is equiv to "!i or !j"
        for (auto j : secondVals[optionb[i]]) { if (j != i) { constraints.push_back({i,j}); }   }    // Rule 1b: !i --> j which is equiv to "i or j"
        if (secondVals.find(optiona[i]) != secondVals.end()) {
            for (auto j : secondVals[optiona[i]]) { constraints.push_back({i+n,j}); }                // Rule 1c: i --> j which is equivk to "!i or j"
        }
        if (firstVals.find(optionb[i]) != firstVals.end()) {
            for (auto j : firstVals[optionb[i]]) { constraints.push_back({i,j+n}); }                 // Rule 1d: !i --> !j which is equivk to "i or !j"
        }
    }

    twoSatStruct t;
    vector<bool> sol;
    auto res = t.twoSat(constraints,(uint32_t)n, sol);
    if (res) {
        cout << "YES" << endl;
        for (int i = 0; i < n; i++) { cout << (sol[i] ? optiona[i] : optionb[i]) << endl; } 
    } else {
        cout << "NO" << endl;
    }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("782D.in2","r",stdin);
  solve();
  return 0;
}
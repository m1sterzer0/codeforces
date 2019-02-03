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

string genRandomTempname(set<string> &examples, set<string> &regular) {
    string tf = "deadbe";
    mt19937 rng;
    uniform_int_distribution<ll>    pos(0,5);
    uniform_int_distribution<char>  val('a','z');
    rng.seed(1234567);
    while (examples.count(tf) > 0 || regular.count(tf) > 0) {
        ll idx = pos(rng);
        char c = val(rng);
        tf[idx] = c;
    }
    return tf;
}

void solve() {
    ll n; cin >> n;
    set<string> examples; 
    set<string> regular;
    REP(i,n) {
        string c; ll type; cin >> c >> type;
        if (type == 1) { examples.insert(c); }
        else           { regular.insert(c);  }
    }
    ll e = (ll) examples.size();
    set<string> efns;
    set<string> rfns;
    FORE(i,1,e)   { efns.insert(to_string(i)); }
    FORE(i,e+1,n) { rfns.insert(to_string(i)); }

    vector<string> ex2reg;
    vector<string> reg2ex;

    // Iterate through the files and look for the ones that should stay put and keep them
    vector<string> keep;
    vector<string> swap;
    for (auto &c : examples) { 
        if (efns.count(c) > 0) keep.push_back(c);
        if (rfns.count(c) > 0) swap.push_back(c);
    }
    for (auto &c : keep) { examples.erase(c); efns.erase(c); }
    for (auto &c : swap) { examples.erase(c); rfns.erase(c); reg2ex.push_back(c); }

    keep.clear();
    swap.clear();
    for (auto &c : regular) { 
        if (rfns.count(c) > 0) keep.push_back(c);
        if (efns.count(c) > 0) swap.push_back(c);
    }
    for (auto &c : keep) { regular.erase(c); rfns.erase(c); }
    for (auto &c : swap) { regular.erase(c); efns.erase(c); ex2reg.push_back(c); }

    vector<pair<string,string>> moves;

    // TODO: deal with case where we need a temp file
    string tf = "";
    if (!reg2ex.empty() && !ex2reg.empty() && efns.empty() && rfns.empty()) {
        tf = genRandomTempname(examples,regular);
        moves.push_back({ex2reg.back(),tf});
        efns.insert(ex2reg.back());
        ex2reg.pop_back();
    }

    while (!reg2ex.empty() && !ex2reg.empty()) {
        if (efns.size() > 0) {
            string efn  =  *efns.begin();
            moves.push_back({reg2ex.back(), efn});
            moves.push_back({ex2reg.back(), reg2ex.back()});
            efns.erase(efn);
            efns.insert(ex2reg.back());
        }

        else {
            string rfn  =  *rfns.begin();
            moves.push_back({ex2reg.back(), rfn});
            moves.push_back({reg2ex.back(), ex2reg.back()});
            rfns.erase(rfn);
            rfns.insert(reg2ex.back());
        }
        reg2ex.pop_back();
        ex2reg.pop_back();
    }

    while (!reg2ex.empty()) {
        string efn  =  *efns.begin();
        moves.push_back({reg2ex.back(), efn});
        rfns.insert(reg2ex.back());
        efns.erase(efn);
        reg2ex.pop_back();
    }

    while (!ex2reg.empty()) {
        string rfn  =  *rfns.begin();
        moves.push_back({ex2reg.back(), rfn});
        efns.insert(ex2reg.back());
        rfns.erase(rfn);
        ex2reg.pop_back();
    }

    if (tf != "") {
        string rfn  =  *rfns.begin();
        moves.push_back({tf, rfn});
        rfns.erase(rfn);
    }

    for (auto &c : examples) {
        string efn  =  *efns.begin();
        moves.push_back({c, efn});
        efns.erase(efn);
    }

    for (auto &c : regular) {
        string rfn  =  *rfns.begin();
        moves.push_back({c, rfn});
        rfns.erase(rfn);
    }

    printf("%lld\n", (ll) moves.size());
    for (auto &pi : moves) { printf("move %s %s\n", pi.first.c_str(), pi.second.c_str()); }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("861E.in2","r",stdin);
    solve();
    return 0;
}

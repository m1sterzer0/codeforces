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

struct sb {
    string firstTen;
    string lastTen;
    array<set<string>,10> track; 

    ll eval() { 
        ll ans  = 0;
        ll targsize = 2;
        REP(i,10) {
            if ((ll) track[i].size() < targsize) return ans;
            ans++;
            targsize *= 2;
        }
        return ans;
    }

    void fromStr(string &a) {
        FORE(i,1,10) {
            for (ll j = 0; j <= (ll) a.size() - i; j++) { track[i-1].insert(a.substr(j,i)); }
        }
        if (a.size() <= 10) { firstTen = a; lastTen = a; }
        else { firstTen = a.substr(0,10); lastTen = a.substr(a.size()-10,10); }
    }

    void fromPair(sb &a, sb &b) {
        REP(i,10) {
            for (auto s : a.track[i]) { track[i].insert(s); }
            for (auto s : b.track[i]) { track[i].insert(s); }
        }
        string middle = a.lastTen + b.firstTen;
        this->fromStr(middle);

        firstTen = a.firstTen;
        if (firstTen.size() < 10) {
            firstTen += b.firstTen;
            if (firstTen.size() > 10) { firstTen = firstTen.substr(0,10); }
        }

        lastTen = b.lastTen;
        if (lastTen.size() < 10) { 
            lastTen = a.lastTen + b.lastTen;
            if (lastTen.size() > 10) { lastTen = lastTen.substr(lastTen.size()-10,10); }
        }
    }
};

void solve() {
    ll n; cin >> n;
    vector<sb> a(n+1);
    FORE(i,1,n) { string s; cin >> s; a[i].fromStr(s); }
    ll m; cin >> m;
    a.resize(n+1+m);
    FORE(i,n+1,n+m) {
        ll ai, bi;
        cin >> ai >> bi;
        a[i].fromPair(a[ai],a[bi]);
        cout << a[i].eval() << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("868D.in1","r",stdin);
    solve();
    return 0;
}

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

struct event {
    ll t; ll type;
};
bool operator<(const event &a, const event &b) { return a.t < b.t || (a.t == b.t && a.type < b.type); }

void solve() {
    ll n, k; cin >> n >> k;
    string s; cin >> s;
    array<ll,26> start;
    array<ll,26> end;
    for (ll i = 0; i < 26; i++) { start[i] = -1; end[i] = -1; }
    ll ii = 0;
    for (auto c : s) {
        ll idx = c - 'A';
        if (start[idx] < 0) start[idx] = ii;
        end[idx] = ii;
        ii++;
    }
    vector<event> qq;
    REP(i,26) {
        if (start[i] >= 0) { qq.PB({start[i],0}); }
        if (end[i] >= 0)   { qq.PB({end[i],1}); }
    }
    sort(qq.begin(),qq.end());
    ll open = 0;
    ll maxopen = 0;
    for (auto e : qq) {
        if (e.type == 0) { open++; maxopen = max(maxopen,open); }
        else             { open--; }
    }
    cout << (maxopen > k ? "YES" : "NO") << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("834B.in2","r",stdin);
    solve();
    return 0;
}

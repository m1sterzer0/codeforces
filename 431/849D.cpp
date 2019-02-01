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

struct dancer {
    ll i;
    ll g;
    ll p;
    ll t;
};

bool sort1(const dancer &a, const dancer &b) {
    if (a.p - a.t < b.p - b.t) return true;
    if (a.p - a.t > b.p - b.t) return false;
    if (a.g > b.g) return true;
    if (a.g < b.g) return false;
    if (a.g == 2 && a.p > b.p) return true;
    if (a.g == 1 && a.p < b.p) return true;
    return false;
}

bool sort2(const dancer &a, const dancer &b) {
    if (a.p - a.t < b.p - b.t) return true;
    if (a.p - a.t > b.p - b.t) return false;
    if (a.g < b.g) return true;
    if (a.g > b.g) return false;
    if (a.g == 2 && a.p > b.p) return true;
    if (a.g == 1 && a.p < b.p) return true;
    return false;
}

void solve() {
    ll n, w, h; cin >> n >> w >> h;
    vector<dancer> aa(n);
    vector<dancer> bb(n);
    REP(i,n) { aa[i].i = i; cin >> aa[i].g >> aa[i].p >> aa[i].t; }
    REP(i,n) { bb[i] = aa[i]; }
    sort(aa.begin(),aa.end(),sort1);
    sort(bb.begin(),bb.end(),sort2);
    vector<ll> x(n);
    vector<ll> y(n);
    REP(i,n) {
        ll xx = (bb[i].g == 2 ? w : bb[i].p);
        ll yy = (bb[i].g == 1 ? h : bb[i].p);
        x[aa[i].i] = xx;
        y[aa[i].i] = yy;
    }
    REP(i,n) { cout << x[i] << " " << y[i] << '\n'; }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

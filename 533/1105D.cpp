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

struct node { ll x; ll y; ll d;};

void solve() {
    ll n, m, p;
    cin >> n >> m >> p;
    array<array<ll,1000>,1000> score;
    vector<string> grid(n);
    vector<deque<node>> qq(p+1);
    vector<ll> lim(p+1,0);
    vector<ll> s(p+1);
    FORE(i,1,p) cin >> s[i];
    REP(i,n) cin >> grid[i];

    REP(i,n) {
        REP(j,m) {
            score[i][j] = -1;
            if (grid[i][j] >= '1' && grid[i][j] <= '9') {
                ll pp = (ll) (grid[i][j] - '0');
                score[i][j] = pp;
                qq[pp].push_back({i,j,0});
            }
        }
    }

    bool done = false;
    while (!done) {
        done = true;
        FORE(pp,1,p) {
            lim[pp] += s[pp];
            while(!qq[pp].empty() && qq[pp].front().d <= lim[pp]) {
                ll i = qq[pp].front().x;
                ll j = qq[pp].front().y;
                ll d = qq[pp].front().d;
                qq[pp].pop_front();
                if (score[i][j] > 0 && d > 0) continue;
                score[i][j] = pp; done = false;
                if (i > 0 && grid[i-1][j] == '.' && score[i-1][j] < 0)   { qq[pp].push_back({i-1,j,d+1}); }
                if (j > 0 && grid[i][j-1] == '.' && score[i][j-1] < 0)   { qq[pp].push_back({i,j-1,d+1}); }
                if (i+1 < n && grid[i+1][j] == '.' && score[i+1][j] < 0) { qq[pp].push_back({i+1,j,d+1}); }
                if (j+1 < m && grid[i][j+1] == '.' && score[i][j+1] < 0) { qq[pp].push_back({i,j+1,d+1}); }
            }
        }
    }
    vector<ll> total(p+1,0);
    REP(i,n) {
        REP(j,m) {
            if (score[i][j] > 0) { total[score[i][j]]++; }
        }
    }
    FORE(i,1,p) { cout << total[i] << " "; }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

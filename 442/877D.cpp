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

void solve() {
    array<array<bool, 1000>,1000> maze;
    array<array<int, 1000>,1000> moves;
    ll n, m, k; cin >> n >> m >> k;
    REP(j,n) {
        string s; cin >> s;
        REP(i,m) maze[i][j] = (s[i] == '.');
    }
    ll x1,y1,x2,y2;
    cin >> y1 >> x1 >> y2 >> x2;  // Transposing becaue of a poor problem convenction
    x1--; y1--; x2--; y2--;

    deque<pair<ll,ll>> bfs;
    REP(i,1000) moves[i].fill(INT_MAX);
    bfs.push_back({x1,y1});
    moves[x1][y1] = 0;
    array<pair<ll,ll>,4> dir;
    dir[0] = {1,0};  dir[1] = {-1,0}; dir[2] = {0,1}; dir[3] = {0,-1};
    
    while (moves[x2][y2] == INT_MAX && !bfs.empty()) {
        ll x = bfs.front().first;
        ll y = bfs.front().second;
        bfs.pop_front();
        int mm = moves[x][y]+1;
        for (auto d : dir) {
            FORE(i,1,k) {
                ll xx = x + i * d.first; ll yy = y + i * d.second; 
                if (xx < 0 || xx >= m || yy < 0 || yy >= n || !maze[xx][yy] || moves[xx][yy] < mm) break;
                if (moves[xx][yy] == INT_MAX) {
                    moves[xx][yy] = mm;
                    bfs.push_back({xx,yy});
                }
            }
        }
    }

    printf("%d\n",moves[x2][y2] == INT_MAX ? -1 : moves[x2][y2]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("877D.in1","r",stdin);
    solve();
    return 0;
}

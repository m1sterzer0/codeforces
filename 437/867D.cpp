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

bool tryEV(double ev, ll R, ll N, vector<ll> f, vector<ll> s, vector<double> p) {
    vector<vector<double>> dp(N);
    REP(i,N) dp[i].assign(R+1,0.0);
    for (ll i = N-1; i >= 0; i--) {
        double ff = (double) f[i];
        double ss = (double) s[i];
        for (ll t = R; t >= 0; t--) {
            double evplay;
            double goodtime = (i==N-1) ? ff : ff + dp[i+1][t];
            double badtime  = (t - s[i] + f[i] < 0) ? ss+ev : (i==N-1) ? ss : ss+dp[i+1][t-s[i]+f[i]];
            evplay = p[i] * goodtime + (1.0-p[i]) * badtime; 
            dp[i][t] = min(evplay,ev);
        }
    }
    return dp[0][R] < ev; // True means that the ev is too high
}

// Iterate on the expected time of the whole game
// If our guess at expected time is too high, we will calculate an expected time of the game lower than ev of the game
// If our guess at expected time is too low, we will calculate an expected time of the game higher than ev of the game
void solve() {
    ll N, R; cin >> N >> R;
    vector<double> P(N);
    vector<ll> f(N);
    vector<ll> s(N);
    REP(i,N) {
        ll pp;
        cin >> f[i] >> s[i] >> pp;
        P[i] = 0.01 * (double) pp;
        R -= f[i];
    }
    double mintime = 0;
    REP(i,N) { mintime += (double) f[i]; }
    double maxtime = 10.0 * mintime;
    while (!tryEV(maxtime,R,N,f,s,P)) { mintime = maxtime; maxtime *= 10; }
    while (0.5 * (maxtime - mintime) / max(1.0, mintime) > 1e-10) {
        double mid = 0.5 * (maxtime + mintime);
        if (tryEV(mid,R,N,f,s,P)) maxtime = mid;
        else                      mintime = mid;
    }
    cout << 0.5 * (maxtime + mintime) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("867D.in1","r",stdin);
    solve();
    return 0;
}

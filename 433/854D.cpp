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

struct flight {
    ll city;
    ll day;
    ll cost;
};
bool sort1 (const flight &a, const flight &b) { return a.day < b.day || (a.day==b.day && a.cost < b.cost); }
bool sort2 (const flight &a, const flight &b) { return a.day > b.day || (a.day==b.day && a.cost < b.cost); }

void solve() {
    ll n, m, k; cin >> n >> m >> k;
    vector<flight> toConf;
    vector<flight> backHome;
    REP(i,m) {
        ll d,f,t,c;
        cin >> d >> f >> t >> c;
        if (t == 0) toConf.push_back({f,d,c});
        else        backHome.push_back({t,d,c});
    }
    sort(toConf.begin(),toConf.end(), sort1);
    sort(backHome.begin(),backHome.end(), sort2);
    vector<ll> cheapestPerCity(n+1,infll);
    vector<ll> costToConf(1000001,infll);
    vector<ll> costFromConf(1000001,infll);

    ll numto = 0;
    ll j = 0;
    ll mincost = 0;
    FORE(i,1,1000000) {
        while(j < (ll) toConf.size() && toConf[j].day == i) {
            ll city = toConf[j].city;
            ll cost = toConf[j].cost;
            if (cheapestPerCity[city] == infll) {
                numto++;
                mincost += cost;
                cheapestPerCity[city] = cost;
            }
            else if (cost < cheapestPerCity[city]) {
                mincost = mincost - cheapestPerCity[city] + cost;
                cheapestPerCity[city] = cost;
            }
            j++;
        }
        costToConf[i] = numto < n ? infll : mincost;
    }

    cheapestPerCity.assign(1000001,infll);
    ll numfrom = 0;
    j = 0;
    mincost = 0;
    for (ll i = 1000000; i >= 1; i--) {
        while(j < (ll) backHome.size() && backHome[j].day == i) {
            ll city = backHome[j].city;
            ll cost = backHome[j].cost;
            if (cheapestPerCity[city] == infll) {
                numfrom++;
                mincost += cost;
                cheapestPerCity[city] = cost;
            }
            else if (cost < cheapestPerCity[city]) {
                mincost = mincost - cheapestPerCity[city] + cost;
                cheapestPerCity[city] = cost;
            }
            j++;
        }
        costFromConf[i] = numfrom < n ? infll : mincost;
    }

    ll best = infll;
    for (ll i = 1; i + k + 1 <= 1000000; i++) {
        if (costToConf[i] == infll) continue;
        if (costFromConf[i+k+1] == infll) continue;
        best = min(best, costToConf[i]+costFromConf[i+k+1]);
    }
    if (best == infll) cout << "-1\n";
    else cout << best << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("854D.in1","r",stdin);
    solve();
    return 0;
}

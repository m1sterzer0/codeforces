#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

struct vacation {
    ll start;
    ll end;
    ll cost;
};

bool operator<(const vacation &a, const vacation &b) { return a.start > b.start || (a.start == b.start && a.cost < b.cost); }

void solve() {
    vector<vector<vacation>> byDuration(200001);
    vector<vacation> vacations;
    ll n,x; cin >> n >> x;
    for (ll i = 0; i < n; i++) {
        ll l,r,cost;
        cin >> l >> r >> cost;
        vacations.push_back({l,r,cost});
    }
    sort(vacations.begin(),vacations.end());
    for (auto v : vacations) {
        ll duration = v.end-v.start+1;
        if (byDuration[duration].empty()) { byDuration[duration].push_back(v); }
        else {
            auto lv = byDuration[duration].back();
            if (v.start < lv.start && v.cost < lv.cost) { byDuration[duration].push_back(v); }
        }
    }

    function<ll(ll,ll)> mySearch = [&](ll duration, ll earliest) {
        if (byDuration[duration].empty()) { return -1LL; }
        if (earliest > byDuration[duration].front().start) { return -1LL; }
        if (earliest <= byDuration[duration].back().start) { return byDuration[duration].back().cost; }
        ll l = 0; ll r = byDuration[duration].size()-1;
        while (r-l > 1) {
            ll m = (r+l)/2;
            if (earliest <= byDuration[duration][m].start) { l = m; }
            else                                           { r = m; }
        }
        return byDuration[duration][l].cost;
    };

    ll bestCost = infll;
    for (auto v : vacations) {
        ll d1 = v.end - v.start+1;
        ll d2 = x - d1;
        if (d2 < 0) continue;
        ll c1 = mySearch(d2,v.end+1);
        if (c1 < 0) continue;
        ll mycost = c1 + v.cost;
        bestCost = min(bestCost,mycost);
    }
    if (bestCost == infll) { cout << -1 << endl; }
    else                   { cout << bestCost << endl; }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("822C.in2","r",stdin);
    solve();
    return 0;
}

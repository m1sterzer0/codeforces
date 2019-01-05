#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n,m;  cin >> n >> m;
    array<array<ll, 100>, 100> g;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }

    ll best = infll; ll bestidx = -1;
    for (ll val = 0; val <= 500; val++) {
        vector<ll> r(n,0);
        vector<ll> c(m,0);
        c[0] = val;
        bool goodFlag = true;
        for (ll i = 0; i < n; i++) {
            r[i] = g[i][0] - c[0];
            if (r[i] < 0) { goodFlag = false; break; }
        }
        if (!goodFlag) continue;
        for (ll j = 1; j < m; j++) {
            c[j] = g[0][j] - r[0];
            if (c[j] < 0) { goodFlag = false; break; }
        }
        if (!goodFlag) continue;

        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < m; j++) {
                if (g[i][j] != r[i] + c[j]) { goodFlag = false; break; }
            }
            if (!goodFlag) break; 
        }
        if (!goodFlag) continue;

        ll score = 0;
        for (ll i = 0; i < n; i++) { score += r[i]; }
        for (ll j = 0; j < m; j++) { score += c[j]; }
        if (score < best) { best = score; bestidx = val; }
    }

    if (best == infll) { cout << -1 << endl; }
    else {
        cout << best << endl;
        vector<ll> r(n,0);
        vector<ll> c(m,0);
        c[0] = bestidx;
        for (ll i = 0; i < n; i++) { r[i] = g[i][0] - c[0]; }
        for (ll j = 1; j < m; j++) { c[j] = g[0][j] - r[0]; }
        for (ll i = 0; i < n; i++) {
            for (ll v = 0; v < r[i]; v++) {
                cout << "row " << i+1 << endl;
            }
        }
        for (ll j = 0; j < m; j++) {
            for (ll v = 0; v < c[j]; v++) {
                cout << "col " << j+1 << endl;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

bool check(double t, int n, vector<int> &a, vector<int> &b, int p) {
    double pp = 0;
    for (int i = 0; i < n; i++) {
        double energyRequired = t * a[i] - b[i];
        if (energyRequired > 0) {
            double powerRequired = energyRequired / t;
            pp += powerRequired;
        }
    }
    if (pp > p) { return false; }
    return true;
}

void solve() {
    int n;
    int p;
    cin >> n >> p;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++) { cin >> a[i]  >> b[i]; }
    ull powerRequired = 0;
    for (int i = 0; i < n; i++) { powerRequired += a[i]; }
    if (powerRequired <= (ull) p) { cout << -1 << endl; return; }
    ull energyAvailable = 0;
    for (int i = 0; i < n; i++) { energyAvailable += b[i]; }
    
    double l = 0.000;
    double r = 1.5 * (double) energyAvailable / (double) (powerRequired - p); // Just to be safe
    while ((r-l) / (0.5*(r+l)) >= 1e-5) {
        double m = 0.5*(r+l);
        if (check(m,n,a,b,p)) l = m;
        else                  r = m;
    }

    cout << 0.5 * (l+r) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("782E.in3","r",stdin);
    solve();
    return 0;
}

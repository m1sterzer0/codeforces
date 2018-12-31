#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    int n; cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) { cin >> a[i]; }
    vector<vector<int>> adj(n+1);
    int x,y;
    for (int i = 0; i < n-1; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    } 
    // First, get the maximum value
    // Get the count of the maximum values
    // Get the count of the maxmimum values minus 1
    int mymax  = *max_element(next(a.begin()),a.end());
    int cmax   = count(next(a.begin()),a.end(),mymax);
    int cmaxm1 = count(next(a.begin()),a.end(),mymax-1);

    int current = mymax + 2;
    for (int i = 1; i <= n; i++) {
        int local = mymax;
        int lcmax = 0;
        int lcmaxm1 = 0;
        if (a[i] == mymax)   { lcmax += 1; }
        if (a[i] == mymax-1) { lcmaxm1 += 1; }
        if (lcmax < cmax) { local = mymax+1; }
        for (auto nn : adj[i]) {
            if      (a[nn] == mymax)   { lcmax += 1;   }
            else if (a[nn] == mymax-1) { lcmaxm1 += 1; }
        }
        if (lcmax < cmax)          { local = mymax+2; }
        else if (lcmaxm1 < cmaxm1) { local = mymax+1; }
        if (local < current) current = local;
    }

    cout << current << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("796C.in92","r",stdin);
    solve();
    return 0;
}

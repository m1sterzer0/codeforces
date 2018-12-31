#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    m--; // Easier w/ zero indexing
    vector<int> a(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    for (int i = 1; i < n; i++) {
        if (m-i >= 0 && a[m-i] > 0 && a[m-i] <= k) { cout << 10*i << endl; return;}
        if (m+i <= n && a[m+i] > 0 && a[m+i] <= k) { cout << 10*i << endl; return;}
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("796A.in1","r",stdin);
    solve();
    return 0;
}

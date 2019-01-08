#include <bits/stdc++.h>
using namespace std;

void solve() {
    unsigned int n,m;
    cin >> n >> m;
    vector<int> a(n*m,0);
    vector<int> dp(n*m,0);
    vector<int> dp2(n,0);
    int elems = n*m;
    for (int i = 0; i < elems; i++) { cin >> a[i]; }
    int idx = n*m - 1;
    for (unsigned int i = 0; i < m; i++) { dp[idx--] = n-1; }
    for (int j = n-2; j >= 0; j--) {
        for (unsigned int i = 0; i < m; i++) {
            if (a[idx] <= a[idx+m]) { dp[idx] = dp[idx+m];  }
            else                    { dp[idx] = j;          }
            idx--;
        }
    }
    idx = n*m - 1;
    for (int j = n-1; j >= 0; j--) {
        dp2[j] = j;
        for (unsigned int i = 0; i < m; i++) {
            if (dp[idx] > dp2[j]) { dp2[j] = dp[idx]; }
            idx--;
        }
    }

    int k; cin >> k;
    int l,r;
    for (int i = 0; i < k; i++) {
        cin >> l >> r;
        if (dp2[l-1] >= r-1) { cout << "Yes" << endl; }
        else                 { cout << "No"  << endl; }
    }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();
  return 0;
}
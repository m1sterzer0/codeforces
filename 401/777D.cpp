#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;  cin >> n;
    vector<string> a(n);
    char c;
    for (int i = 0; i <n; i++) {
        cin >> c >> a[i];
    }
    for (int i = n-2; i >=0; i--) {
        if (a[i].compare(a[i+1]) <= 0) { continue; }
        int k = min( (int) a[i].size(), (int) a[i+1].size());
        a[i].resize(k);
        for (int j = 0; j <k; j++) {
            if (a[i][j] > a[i+1][j]) { a[i].resize(j); break; }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << '#' << a[i] << endl;
    }

}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();
  return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    int n;  cin >> n;
    vector<int> a(6,0);
    vector<int> b(6,0);
    int x;
    for (int i = 0; i < n; i++) { cin >> x; a[x]++; }
    for (int i = 0; i < n; i++) { cin >> x; b[x]++; }
    int exchanges = 0;
    for (int i = 1; i <= 5; i++) {
        int avg = (a[i]+b[i]) / 2;
        if (2*avg != a[i] + b[i]) { cout << -1 << endl; return; }
        if (a[i] > avg) { exchanges += (a[i]-avg); }
    }
    cout << exchanges << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("777E.in3","r",stdin);
  solve();
  return 0;
}
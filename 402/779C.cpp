#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    for (int i = 0; i < n; i++) { cin >> b[i]; }
    vector<int> cheapest(n), discount(n);
    for (int i = 0; i < n; i++) {
        cheapest[i] = min(a[i],b[i]);
        discount[i] = a[i] <= b[i] ? 0 : a[i] - b[i];
    }
    int ans = 0;
    for (auto x : cheapest) { ans += x; }
    sort(discount.begin(),discount.end());
    for (int i = 0; i < k; i++) {ans += discount[i]; }
    cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("779C.in1","r",stdin);
  solve();
  return 0;
}
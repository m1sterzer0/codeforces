#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    int n,m;
    cin >> n;
    vector<int> l1(n), r1(n);
    for (int i = 0; i < n; i++) { cin >> l1[i] >> r1[i]; }
    cin >> m;
    vector<int> l2(m), r2(m);
    for (int i = 0; i < m; i++) { cin >> l2[i] >> r2[i]; }
    int minr1 = *min_element(r1.begin(),r1.end());
    int minr2 = *min_element(r2.begin(),r2.end());
    int maxl1 = *max_element(l1.begin(),l1.end());
    int maxl2 = *max_element(l2.begin(),l2.end());
    int ans = max(maxl2-minr1,maxl1-minr2);
    if (ans < 0) ans = 0;
    cout << ans << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("782E.in3","r",stdin);
  solve();
  return 0;
}
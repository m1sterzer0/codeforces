#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

// Just brute force it.  Solution should exist in 0 <= i,j <= 200
void solve() {
    int n,k;
    cin >> n >> k;
    int ans = 0; int x;
    for (int i = 0; i < n; i++) {
        cin >> x;
        if (x % k == 0) { ans += x / k; }
        else            { ans += x / k + 1; }
    }
    if (ans % 2 == 0) cout << (ans/2) << endl;
    else              cout << (ans/2+1) << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("782E.in3","r",stdin);
  solve();
  return 0;
}
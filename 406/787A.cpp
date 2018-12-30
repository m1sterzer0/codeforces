#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

// Just brute force it.  Solution should exist in 0 <= i,j <= 200
void solve() {
    int a,b,c,d;
    cin >> a >> b;
    cin >> c >> d;
    int val = d;
    for (int i = 0; i < 200; i++) {
        int target = b + i * a;
        while (val < target) { val += c; }
        if (val == target) { cout << val << endl; return; }
    }
    cout << -1 << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("782E.in3","r",stdin);
  solve();
  return 0;
}
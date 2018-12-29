#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    ull a,b;
    cin >> a >> b;
    int years = 0;
    while (true) {
        years += 1;
        a *= 3;
        b *= 2;
        if (a > b) break;
    }
    cout << years;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("782E.in3","r",stdin);
  solve();
  return 0;
}
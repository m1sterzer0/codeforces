#include <bits/stdc++.h>
using namespace std;

uint64_t solveit(uint64_t rot, uint64_t x) {
    // 0 1 2 --> 1 0 2 --> 1 2 0 --> 2 1 0 --> 2 0 1 --> 0 2 1 --> 0 1 2
    if (x == 0) {
        if (rot == 0 || rot == 5) { return 0; }
        if (rot == 1 || rot == 2) { return 1; }
        return 2;
    } else if (x == 1) {
        if (rot == 1 || rot == 4) { return 0; }
        if (rot == 0 || rot == 3) { return 1; }
        return 2;
    } else if (x == 2) {
        if (rot == 2 || rot == 3) { return 0; }
        if (rot == 4 || rot == 5) { return 1; }
        return 2;
    }
    return 0; // Shouldn't get here.
}

void solve() {
  uint64_t x,n;
  cin >> n >> x;
  uint64_t rot = n % 6;
  cout << solveit(rot,x) << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();
  return 0;
}
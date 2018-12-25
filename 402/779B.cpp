#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    string n;
    int k;
    cin >> n >> k;
    int deleted = 0;
    for (auto it = n.rbegin(); it != n.rend(); it++) {
        if (*it == '0') { k--; if (k==0) { cout << deleted << endl; return; } }
        else            { deleted += 1; }
    }
    cout << n.size()-1 << endl; //Problem guarantees there is at least one zero
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("779B.in1","r",stdin);
  solve();
  return 0;
}
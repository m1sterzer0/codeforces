#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    int n;  cin >> n;
    vector<bool> found(n+1,false);
    int numsocks = 0;
    int maxsocks = 0;
    int x;
    for (int i = 0; i < 2 * n ; i++) {
        cin >> x;
        if (!found[x]) {
            numsocks += 1;
            if (numsocks > maxsocks) { maxsocks = numsocks; }
            found[x] = true;
        } else {
            numsocks -= 1;
        }        
    }
    cout << maxsocks << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("777E.in3","r",stdin);
  solve();
  return 0;
}
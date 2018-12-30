#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

// Just brute force it.  Solution should exist in 0 <= i,j <= 200
void solve() {
    int n,m; cin >> n >> m;
    set<int> currentGroup;
    for (int i = 0; i < m; i++) {
        currentGroup.clear();
        int k; cin >> k;
        int x;
        bool goodGroup = false;
        for (int j = 0; j < k; j++) {
            cin >> x;
            currentGroup.insert(x);
            if (currentGroup.find(-x) != currentGroup.end()) { goodGroup = true; }
        }
        if (!goodGroup) { cout << "YES" << endl; return; }
    }
    cout << "NO" << endl; 
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("782E.in3","r",stdin);
  solve();
  return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

// Just brute force it.  Solution should exist in 0 <= i,j <= 200
void solve() {
    ll b1,q,l,m;
    cin >> b1 >> q >> l >> m;
    set<int> bad;
    int x;
    for (int i = 0; i < m; i++) { cin >> x; bad.insert(x); }

    // Special cases are q = 0, q = 1, q = -1
    if (b1 > l || b1 < -l) { cout << 0 << endl; return; }

    if (b1 == 0) {
        if (bad.count(0) == 0) { cout << "inf" << endl; return; }
        else                   { cout << 0 << endl; return;     }
    }

    if (q == 0) {
        if (bad.count(0) == 0) { cout << "inf" << endl; return; }
        else { cout << (bad.count((int) b1) == 0 ? 1 : 0) << endl; return; } 
    } 
    
    if (q == 1) {
        if (bad.count((int) b1) == 0) { cout << "inf" << endl; return; }
        else                    { cout << 0 << endl;     return; }
    }
    
    if (q == -1) {
        if ((bad.count((int) b1) > 0) && (bad.count((int) -b1) > 0)) { cout << 0 << endl; return; }
        else                                             { cout << "inf" << endl; return; }
    }
   
    ll tt = b1;
    int ans = 0;
    while ((tt <= l) && (tt >= -l)) {
        if (bad.count((int) tt) == 0) { ans += 1; }
        tt *= q;
    }
    cout << ans << endl;
}
        
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("789B.in56","r",stdin);
  solve();
  return 0;
}
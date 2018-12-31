#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    vector<bool> holes(n+1,false);
    int xx;
    for (int i = 0; i < m; i++) {
        cin >> xx;
        holes[xx] = true;
    }
    if (holes[1]) { cout << 1 << endl; return; }
    int bone = 1;
    int x,y;
    for (int i = 0; i < k; i++) {
        cin >> x >> y;
        if      (x == bone) bone = y;
        else if (y == bone) bone = x;
        if (holes[bone]) { cout << bone << endl; return; }
    } 
    cout << bone << endl; return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("782E.in3","r",stdin);
    solve();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    string x,y;
    cin >> x;
    cin >> y;
    int ss = x.size();
    for (int i = 0; i < ss; i++) {
        if (x[i] < y[i]) { cout << -1 << endl; return; }
    }
    cout << y << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("782E.in3","r",stdin);
    solve();
    return 0;
}

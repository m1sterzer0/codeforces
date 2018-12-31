#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    string s;
    for (int i = 0; i < 50000; i++) { s += "aabb"; }
    ll n; cin >> n;
    cout << s.substr(0,n) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("782E.in3","r",stdin);
    solve();
    return 0;
}

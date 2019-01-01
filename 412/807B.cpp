#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

bool isGood(int p, int s) {
    int i = (s / 50) % 475;
    for (int ii = 0; ii < 25; ii++) {
        i = (i * 96 + 42 ) % 475;
        if (p == i + 26) { return true; }
    }
    return false;
}

void solve() {
    int p,x,y;  cin >> p >> x >> y;
    int ans = 0;
    if (x > y) {
        // Have to check several unsuccessful hacks from starting value as special case
        int uhacktotal = 50;
        while (x - uhacktotal >= y) {
            if (isGood(p,x-uhacktotal)) { cout << 0 << endl; return; }
            uhacktotal += 50;
        }
    }
    while (x < y) { x += 100; ans += 1; }
    while (true) {
        if (isGood(p,x)) { cout << ans << endl; return; }
        if (x - 50 > y && isGood(p,x-50)) { cout << ans << endl; return; }
        x += 100;
        ans += 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("807B.in1","r",stdin);
    solve();
    return 0;
}

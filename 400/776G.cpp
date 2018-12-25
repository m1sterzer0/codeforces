#include <bits/stdc++.h>
using namespace std;

void solve() {
    uint64_t n,k;
    cin >> n >> k;
    totientCalc t;
    t.sieve(1000000);
    uint64_t res = t.totient(n);
    for (uint64_t kk = 3; kk <= k; kk += 2) {
        res = t.totient(res);
        if (res == 1) { break; }
    }
    cout << (res % 1000000007ULL) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("776C.in1","r",stdin);
    solve();
    return 0;
}
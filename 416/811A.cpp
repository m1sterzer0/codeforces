#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll a, b; cin >> a >> b;
    ll gift = 1;
    while (true) {
        a -= gift; gift++; 
        if (a < 0) { cout << "Vladik" << endl; return; }
        b -= gift; gift++;
        if (b < 0) { cout << "Valera" << endl; return; }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

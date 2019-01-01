#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

void solve() {
    ll n,h;
    cin >> n >> h;
    for (ll i = 1; i < n; i++) {
        double res = sqrt((double) i / (double) n) * (double) h;
        printf("%.10e ", res);
    }
    printf("\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}
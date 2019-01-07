#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll A,B; cin >> A >> B;
    vector<ll> fact(13);
    fact[1] = 1;
    for (ll i = 2; i <= 12; i++) { fact[i] = i * fact[i-1]; }
    A = min(A,B);
    cout << fact[A] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

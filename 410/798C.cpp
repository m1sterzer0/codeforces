#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

bool checkForZero(vector<ll> &a, ll n) {
    ll g = a[0];
    ll idx = 1;
    while (idx < n && g > 1) { g = __gcd(g,a[idx]); idx++; }
    if (g > 1) return true;
    return false;
}

void solve() {
     ll n; cin >> n;
     vector<ll> a(n);
     for (ll i = 0; i < n; i++) { cin >> a[i]; }
     cout << "YES" << endl;
     if (checkForZero(a,n)) { cout << 0 << endl; return; }
     ll ops = 0;
     for (ll i = 0; i < n-1; i++) {
         if ((a[i] & 1) && (a[i+1] & 1)) { a[i] = 2; a[i+1] = 2; ops++; }
     }

     for (ll i = 0; i < n; i++) {
         if (a[i] & 1) { a[i] = 2; ops += 2; }
     }
     cout << ops << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("782E.in3","r",stdin);
    solve();
    return 0;
}

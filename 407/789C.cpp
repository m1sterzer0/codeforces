#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

// Just brute force it.  Solution should exist in 0 <= i,j <= 200
void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) { cin >> a[i]; }
    vector<ll> b(n-1);


    // We first solve the problem for an even l, then we solve the problem for odd l
    for (int i = 0; i < n-1; i++) {
        b[i] = a[i] - a[i+1];
        if (b[i] < 0)   { b[i] = -b[i]; }
        if (i % 2 == 1) { b[i] = -b[i]; }
    }
    ll mincum = 0;
    ll maxcum = 0;
    ll cum = 0;
    ll best = 0;
    for (int i = 0; i < n-1; i++) {
        cum += b[i];
        if (i % 2 == 1 && cum < mincum) { mincum = cum; maxcum = cum; }
        else if (cum > maxcum)          { maxcum = cum; }
        if (maxcum - mincum > best) { best = maxcum - mincum; }
    }

    // Now we invert all the signs in the b array and run it again, forcing ourselves to start on an odd 
    for (int i = 0; i < n-1; i++) { b[i] = -b[i]; }
    mincum = b[0];
    maxcum = 0;
    cum = b[0];
    for (int i = 1; i < n-1; i++) {
        cum += b[i];
        if (i % 2 == 0 && cum < mincum) { mincum = cum; maxcum = cum; }
        else if (cum > maxcum) { maxcum = cum; }
        if (maxcum - mincum > best) { best = maxcum - mincum; }
    }

    cout << best << endl;

}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("789B.in56","r",stdin);
  solve();
  return 0;
}
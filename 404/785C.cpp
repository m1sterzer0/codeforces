#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

bool test(uint64_t n, uint64_t m, uint64_t k) {
    if (2*(n-m) / (k-m)     >  (k-m+1)) return false;
    if (2*(n-m) / (k-m) + 1 <= (k-m+1)) return true;
    if ((2 * (n-m)) % (k-m) == 0) return true;         // No rouding
    return false;
}

    // For the first m days, we will end the day at n-1, n-2, n-3, n-4, ... , n-m
    // Need to find day k such that we end up with <= 0 grain
    // * We start day m+1 with n-m grain
    // * We will refill m * (k-m) = k*m - m*m grain
    // * We will depelete (m+1) + (m+2) + ... + k grain = (k-m)(k+m+1) / 2
    // Thus, we need to find the minimum k such that 
    //  n-m + m *(k-m) <= (k-m)(k+m+1) / 2
    //  2(n-m) / (k-m) + 2m <= k + m + 1
    //  2(n-m) / (k-m) <= k - m + 1


void solve() {
    uint64_t n,m;
    cin >> n >> m;
    if (m >= n) { cout << n << endl; return; }
    uint64_t l = m;
    uint64_t r = n;
    while (r-l > 1) {
        uint64_t mid = (l+r)/2;
        if (test(n,m,mid)) { r = mid; }
        else               { l = mid; }
    }
    cout << r << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("782E.in3","r",stdin);
  solve();
  return 0;
}
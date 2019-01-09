#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

// Modular Combinatorics
const ull mod = 1000000007;
inline ull madd(ull x, ull y) { ull r = x + y; if (r >= mod) { r -= mod; } return r; }
inline ull msub(ull x, ull y) { return x >= y ? x - y : x + mod - y; }
inline ull mmul(ull x, ull y) { return x * y % mod; }
inline ull mpow(ull x, ull p) { ull r=1; while (p) { if (p & 1) r = mmul(r,x); x = mmul(x,x); p = p >> 1; } return r; } 
inline ull minv(ull x) { return mpow(x,mod-2); }

struct modularCombinatorics {
    vector<ull> fact;
    vector<ull> ifact;
    void init(ull lim) {
        fact.clear(); fact.resize(lim+1,1);
        ifact.clear(); ifact.resize(lim+1,1);
        for (ull i = 2; i <= lim; i++) {
            fact[i] = mmul(fact[i-1],i);
            ifact[i] = minv(fact[i]);
        }
    }
    ull comb(ull n, ull k) {
        if (k > n) { return 0; }
        return mmul(mmul(fact[n],ifact[k]),ifact[n-k]);
    }
};

// We are going to count based on the ith position beeing the inner-most left parenthesis
// For a string of x '('s followed by y ')'s, we have that we can get comb(x+y,x) - 1 substrings.
// For a string of x '('s followed by y ')'s, we want to count how many substrings include the rightmost (.
//     This is (comb(x+y,x) -1 ) - (comb(x+y-1,x-1) - 1) = comb(x+y,x) - comb(x+y-1,x-1)
//                                                       = (comb(x+y-1,x-1)+comb(x+y-1,x)) - comb(x+y-1,x-1)
//                                                       = comb(x+y-1,x)


void solve() {
    modularCombinatorics engine;
    engine.init(200000);
    string s;
    cin >> s;
    int n = (int) s.size();
    vector<int> left(n,0), right(n,0);
    int l = 0;
    for (int i = 0; i < n; i++) { if (s[i] == '(') l++;  left[i] = l;  }
    int r = 0;
    for (int i = n-1; i >= 0; i--) { if (s[i] == ')') r++;  right[i] = r;  }
    ull sol = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(') { sol = madd(sol,engine.comb(left[i]+right[i]-1,left[i])); }
    }
    cout << sol << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("785D.in1","r",stdin);
  solve();
  return 0;
}
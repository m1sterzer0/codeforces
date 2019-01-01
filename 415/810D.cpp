#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

bool doQuery(ll x, ll y) {
    cout << 1 << " " << x << " " << y << endl;
    fflush(stdout);
    string s;
    cin >> s;
    return (s == "TAK");
}

ll doBinSearch(ll l, ll r) {
    while (r != l) {
        ll m = (l+r)/2;
        if (doQuery(m,m+1)) { r = m; }
        else                { l = m+1; } 
    }
    return r;
}

void solve() {
    ll n,k; cin >> n >> k;
    ll dish1, dish2, dish2a, dish2b;
    // Step 1 -- binsearch from 1 to n
    dish1 = doBinSearch(1,n);
    if (dish1 == 1)      { dish2 = doBinSearch(2,n);   }
    else if (dish1 == n) { dish2 = doBinSearch(1,n-1); }
    else {
        dish2a = doBinSearch(1,dish1-1);
        dish2b = doBinSearch(dish1+1,n);
        dish2 = doQuery(dish2a,dish2b) ? dish2a : dish2b;
    }

    cout << 2 << " " << dish1 << " " << dish2 << endl;
    fflush(stdout);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

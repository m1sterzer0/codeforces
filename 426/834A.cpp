#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    char s0; cin >> s0;
    char s1; cin >> s1;
    ll n; cin >> n;
    if      ((s0 == '^' && s1 == '>') || (s0 == '>' && s1 == 'v') || (s0 == 'v' && s1 == '<') || (s0 == '<' && s1 == '^')) { cout << (n % 4 == 1 ? "cw" : "ccw") << endl; }
    else if ((s0 == '^' && s1 == '<') || (s0 == '>' && s1 == '^') || (s0 == 'v' && s1 == '>') || (s0 == '<' && s1 == 'v')) { cout << (n % 4 == 3 ? "cw" : "ccw") << endl; }
    else    cout << "undefined" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("834A.in1","r",stdin);
    solve();
    return 0;
}

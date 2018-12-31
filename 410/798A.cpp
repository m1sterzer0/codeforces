#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    string s;
    cin >> s;
    int i1 = 0;
    int i2 = s.size() - 1;
    int mismatches = 0;
    while (i2 > i1) {
        if (s[i1] != s[i2]) mismatches += 1;
        i1++; i2--;
    }
    if ((mismatches == 1) || (mismatches == 0) && (s.size() % 2 == 1)) cout << "YES" << endl;
    else                                                               cout << "NO"  << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("782E.in3","r",stdin);
    solve();
    return 0;
}

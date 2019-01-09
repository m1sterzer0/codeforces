#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    string s1; cin >> s1;
    string s2; cin >> s2;
    map<char,char> t;
    for (ll i = 0; i < 26; i++) { t[s1[i]] = s2[i]; }
    string s3; cin >> s3;
    #pragma GCC diagnostic ignored "-Wconversion"
    for (auto c : s3) {
        if (c >= 'a' && c <= 'z') { cout << t[c]; }
        else if (c >= 'A' && c <= 'Z') { c += 32; c = t[c]; c -= 32; cout << c; }
        else { cout << c; }
    }
    #pragma GCC diagnostic pop
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

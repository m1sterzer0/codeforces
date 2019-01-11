#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    map<char,bool> good;
    for (char c = 'a'; c <= 'z'; c++) { good[c] = false; }
    string goodlet; cin >> goodlet;
    for (auto c : goodlet) { good[c] = true; }
    string pat; cin >> pat;
    bool starInPat = false;
    for (auto c : pat) { if (c == '*') starInPat = true; }
    
    ll n; cin >> n;
    for (ll i = 0; i < n; i++) {
        string test; cin >> test;
        bool match = true;
        if (!starInPat && test.size() != pat.size()) match = false;
        else if (starInPat && (int) test.size() - (int) pat.size() < -1) match = false;
        else {
            ll slen = starInPat ? (int) test.size() - (int) pat.size() + 1 : 0;
            ll it = 0;
            for (ll ip = 0; ip < (ll) pat.size(); ip++) {
                if (pat[ip] == '*') {
                    for (ll j = 0; j < slen; j++) {
                        if (it >= (ll) test.size() || good[test[it]]) { match = false; break; }
                        it++;
                    }
                } 
                else if (pat[ip] == '?') {
                    if (!good[test[it]]) { match = false; }
                    it++;
                }
                else {
                    if (test[it] != pat[ip]) { match = false; }
                    it++;
                }
                if (!match) break;
            }
        }
        if (!match) { cout << "NO"  << endl; }
        else        { cout << "YES" << endl; }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("832B.in2","r",stdin);
    solve();
    return 0;
}

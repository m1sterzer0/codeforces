#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n;
    cin >> n;
    vector<ll> mystack;
    ll numCommands = 2 * n;
    ll target = 1;
    ll res = 0;
    for (ll i = 0; i < numCommands; i++) {
        string s; ll b; cin >> s;
        if (s == "add") { cin >> b; mystack.push_back(b); }
        else {
            if      (!mystack.empty() && mystack.back() == target) { mystack.pop_back(); }
            else if (!mystack.empty() && mystack.back() != target) { res++; mystack.clear(); }
            target++;
        }
    }
    cout << res << endl; 
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

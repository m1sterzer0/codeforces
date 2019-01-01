#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    int n; cin >> n;
    int last = 9999;
    bool maybe = true;
    for (int i = 0; i < n; i++) {
        int before, after;
        cin >> before >> after;
        if (before != after) { cout << "rated\n"; return; }
        if (before > last)     maybe = false; 
        last = before;
    }
    cout << (maybe ? "maybe\n" : "unrated\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("782E.in3","r",stdin);
    solve();
    return 0;
}
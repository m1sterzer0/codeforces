#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    string s;
    cin >> s;
    // Count the VKs in the string
    int ss = (int) s.size();
    int count = 0;
    for (int i = 0; i < ss-1; i++) {
        if (s[i] == 'V' && s[i+1] == 'K') { count++; }
    }

    bool vvv = false;
    for (int i = 0; i < ss-2; i++) {
        if (s[i] == 'V' && s[i+1] == 'V' && s[i+2] == 'V') { vvv = true; }
        if (s[i] == 'K' && s[i+1] == 'K' && s[i+2] == 'K') { vvv = true; }
    }
    bool vvend = false;
    if (ss >= 2 && s[ss-1] == 'V' && s[ss-2] == 'V') { vvend = true; }
    if (ss >= 2 && s[0]    == 'K' && s[1]    == 'K') { vvend = true; }
    if (vvv || vvend) count++;
    cout << count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("782E.in3","r",stdin);
    solve();
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    // Do a simple sieve
    vector<uint8_t> sieve;
    sieve.resize(100002);
    for(int i = 2; i < 100002; i++) { sieve[i] = 1; }
    for(int i = 4; i < 100002; i+=2) { sieve[i] = 2; } // Do the Evens
    for(int i = 3; i < 1001; i+=2) {
        if (sieve[i] == 2) continue;
        int jinc = 2*i;
        for (int j = i*i; j <= 100002; j += jinc) { sieve[j] = 2; }
    }

    if (n <= 2) cout << 1 << endl;
    else        cout << 2 << endl;
    cout << 1;
    for (int i = 3; i < n+2; i++) cout << " " << (int) sieve[i];
    cout << endl;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}
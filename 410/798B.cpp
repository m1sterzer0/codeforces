#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    int n; cin >> n;
    vector<string> ss(n);
    vector<int>    ii(n);
    for (int i = 0; i < n; i++) { cin >> ss[i]; ss[i] = ss[i] + ss[i]; }
    int slen = (int) ss[0].size() / 2;
    int best = 1000000000;
    for (int i = 0; i < slen; i++) {
        int current = i;
        for (int j = 1; j < n; j++) {
            bool foundMatch = false;
            for (int k = 0; k < slen; k++) {
                if (ss[0].substr(i,slen) == ss[j].substr(k,slen)) {
                    foundMatch = true;
                    break;
                }
                else { current++; }
            }
            if (!foundMatch) { cout << -1 << endl; return; }
        }
        if (current < best) best = current;
    }
    cout << best << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("798B.in1","r",stdin);
    solve();
    return 0;
}

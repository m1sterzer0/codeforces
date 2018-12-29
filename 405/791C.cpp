#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;


void solve() {
    vector<string> names{ "Aa", "Ab", "Ac", "Ad", "Ae", "Af", "Ag", "Ah", "Ai", "Aj",
                          "Ba", "Bb", "Bc", "Bd", "Be", "Bf", "Bg", "Bh", "Bi", "Bj",
                          "Ca", "Cb", "Cc", "Cd", "Ce", "Cf", "Cg", "Ch", "Ci", "Cj",
                          "Da", "Db", "Dc", "Dd", "De", "Df", "Dg", "Dh", "Di", "Dj",
                          "Ea", "Eb", "Ec", "Ed", "Ee", "Ef", "Eg", "Eh", "Ei", "Ej" };
        
    int n,k;
    cin >> n >> k;
    vector<bool> observations(n-k+1);
    vector<string> ans(n);
    string x;
    bool allfalse = true;
    for (int i = 0; i < n-k+1; i++) {
        cin >> x;
        observations[i] = (x == "YES" ? true : false);
        if (observations[i]) { allfalse = false; }
    }

    // If all of the observations are false, then we just return 10 copies of the first guy.
    // Otherwise
    // * We use the first name for as many NOs as we initially have.
    // * We use k subsequent names for the first yes
    // * For each subsequent NO, we use the value "k-1" ago.
    // * For each subsequent YES, we use the next name on the list

    if (allfalse) {
        cout << "A";
        for (int i = 1; i < n; i++) { cout << " A"; }
        cout << endl;
        return; 
    }

    int nidx(0), sidx(0);
    bool firstyes = false;
    for (int i = 0; i < n-k+1; i++) {
        if (!firstyes) {
            if (observations[i]) {
                for (int j=0; j < k; j++) { ans[sidx] = names[nidx]; sidx++; nidx++; }
                firstyes = true;
            } else {               ans[sidx] = names[nidx]; sidx++; }
        } else {
            if (observations[i]) { ans[sidx] = names[nidx]; sidx++; nidx++; }
            else                 { ans[sidx] = ans[sidx-k+1]; sidx++; }
        }
    }

    cout << ans[0];
    for (int i = 1; i < n; i++) { cout << " " << ans[i]; }
    cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("782E.in3","r",stdin);
  solve();
  return 0;
}
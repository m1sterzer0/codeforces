#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

bool eval(string a, string b, vector<int> &perm, int n) {
    vector<bool> crossed(a.size(),false);
    for (int i = 0; i < n; i++) { crossed[perm[i]] = true; }
    int matched = 0;
    int target = (int) b.size();
    int alen = (int) a.size();
    for (int i = 0; i < alen; i++) {
        if (crossed[i]) continue;
        if (a[i] != b[matched]) continue;
        matched++;
        if (matched == target) return true;
    }
    return false;
}

void solve() {
    string a,b;
    cin >> a;
    cin >> b;
    int alen = (int) a.size();
    vector<int> perm(alen);
    for (int i = 0; i < alen; i++) { cin >> perm[i]; perm[i]--; }  //to get us back to zero indexing
    int l = 0;
    int r = alen;
    if (eval(a,b,perm,alen)) { cout << alen << endl; return; }
    while (r-l > 1) {
        int t = (l+r)/2;
        if (eval(a,b,perm,t)) { l = t; }
        else                  { r = t; }
    }
    cout << l << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("779C.in1","r",stdin);
  solve();
  return 0;
}
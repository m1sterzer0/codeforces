#include <bits/stdc++.h>
using namespace std;

int minimizeblosses(vector<int> &a, vector<int> &b, int n) {
    int i = 0;
    int blosses = 0;
    for (int j = 0; j < n; j++) {
        if (b[j] >= a[i]) { i += 1; }
        else              { blosses += 1; }
    }
    return blosses;
}

int maximizebwins(vector<int> &a, vector<int> &b, int n) {
    int i = 0;
    int bwins = 0;
    for (int j = 0; j < n; j++) {
        if (b[j] > a[i]) { i += 1; bwins += 1; }
    }
    return bwins;
}

void solve() {
    int n;
    string sa,sb;
    cin >> n;
    cin >> sa;
    cin >> sb;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        a[i] = sa[i] - '0';
        b[i] = sb[i] - '0';
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int s1 = minimizeblosses(a,b,n);
    int s2 = maximizebwins(a,b,n);
    cout << s1 << endl << s2 << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  solve();
  return 0;
}
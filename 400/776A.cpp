#include <bits/stdc++.h>
using namespace std;

void solve() {
  string a,b;
  int n;
  cin >> a >> b;
  cin >> n;
  cout << a << " " << b << endl;
  for (int i=0; i < n; i++) {
    string murdered;
    string newvictim;
    cin >> murdered >> newvictim;
    if (a == murdered) a = newvictim;
    else               b = newvictim;
    cout << a << " " << b << endl;
  }
}


int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("776A.in1","r",stdin);
  solve();
  return 0;
}
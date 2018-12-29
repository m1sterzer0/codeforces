#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    int n;
    cin >> n;
    string s;
    int faces = 0;
    for (int i = 0; i < n; i++) {
        cin >> s;
        if (s == "Tetrahedron")       faces += 4;
        else if (s == "Cube")         faces += 6;
        else if (s == "Octahedron")   faces += 8;
        else if (s == "Dodecahedron") faces += 12;
        else if (s == "Icosahedron")  faces += 20;
    }
    cout << faces << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("782E.in3","r",stdin);
  solve();
  return 0;
}
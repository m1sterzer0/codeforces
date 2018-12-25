#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    int n;  cin >> n;
    vector<vector<int>> g(n+1);
    int x,y;
    for (int i = 0; i < n-1; i++) { cin >> x >> y; g[x].push_back(y); g[y].push_back(x); }
    vector<int> colors(n+1,0);
    vector<int> st; st.push_back(1);
    colors[1] = 1;
    while (!st.empty()) {
        int node = st.back();
        st.pop_back();
        int currentcolor = colors[node];
        int parentcolor  = 0;
        for (auto n : g[node]) { if (colors[n] != 0) parentcolor = colors[n]; } //Could do better here, but no need.
        int mycolor = 1;
        while (mycolor == currentcolor || mycolor == parentcolor) { mycolor++; }
        for (auto n : g[node]) { 
            if (colors[n] == 0) {
                colors[n] = mycolor++;
                while (mycolor == currentcolor || mycolor == parentcolor) { mycolor++; }
                st.push_back(n);
            }
        }
    }
    int maxcolors = *max_element(colors.begin(),colors.end());
    cout << maxcolors << endl;
    cout << colors[1];
    for (int i = 2; i <= n; i++) { cout << " " << colors[i]; }
    cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("782B.in1","r",stdin);
  solve();
  return 0;
}
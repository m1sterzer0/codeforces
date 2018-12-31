#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;



void solve() {
    ll n,m; cin >> n >> m;
    vector<vector<int>> ic(n+1);
    for (int i = 1; i <= n; i++) {
        int s; cin >> s;
        for (int j = 0; j < s; j++) {
            int ss; cin >> ss; ic[i].push_back(ss);
        }
    }
    vector<vector<int>> adj(n+1);
    for (int i = 0; i < n-1; i++) {
        int x,y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> res(m+1,-1);
    int maxcolor = 1;

    function<void(int,int)> dfs = [&](int n, int p) {
        priority_queue<int, vector<int>, greater<int>> pq;
        vector<int> needAssign;
        int nextColor = 1;
        for (auto flavor : ic[n]) {
            if (res[flavor] == -1) { needAssign.push_back(flavor); }
            else                   { pq.push(res[flavor]); }
        }
        for (auto flavor : needAssign) {
            while (!pq.empty() && nextColor == pq.top()) { pq.pop(); nextColor++; }
            res[flavor] = nextColor;
            maxcolor = max(maxcolor,nextColor);
            nextColor++;
        }
        
        for (auto nn : adj[n]) { if (nn != p) dfs(nn,n); }
    };
    dfs(1,-1);
    for (int i = 1; i <= m; i++) { if (res[i] == -1) res[i] = 1; }

    cout << maxcolor << endl;
    cout << res[1];
    for (int i = 2; i <= m; i++) { cout << " " << res[i]; }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("805E.in1","r",stdin);
    solve();
    return 0;
}

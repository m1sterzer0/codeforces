#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

struct tarjanSCC {
    vector<int> index;
    vector<int> lowlink;
    vector<bool> onstack;
    vector<int> stack;
    int currentidx;
    int startnode,endnode;
    vector<vector<int>> *padj;
    vector<vector<int>> *pssc;

    void dfs(int n) {
        index[n] = currentidx++;
        lowlink[n] = index[n];
        onstack[n] = true;
        stack.push_back(n);
        for (auto nn : (*padj)[n]) {
            if (index[nn] < 0) { dfs(nn); lowlink[n] = min(lowlink[n], lowlink[nn]); }
            else if (onstack[nn]) { lowlink[n] = min(lowlink[n], lowlink[nn]); }
        }
        if (lowlink[n] == index[n]) { // Root of an SSC
            pssc->resize(pssc->size()+1);
            vector<int> *pcurssc = &(pssc->back());
            do {
                pcurssc->push_back(stack.back());
                stack.pop_back();
            } while (pcurssc->back() != n);
        }
    }

    void ssc(vector<vector<int>> &adj, vector<vector<int>> &sscout, int start, int end) {
        currentidx = 0;
        index.clear();   index.resize(end+1,-1);
        lowlink.clear(); lowlink.resize(end+1,-1);
        onstack.clear(); onstack.resize(end+1,false);
        stack.clear();
        sscout.clear();
        padj = &adj;
        pssc = &sscout;
        for (int i = start; i <= end; i++) { if (index[i] < 0) dfs(i); }
    }
};

void solve() {
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n+1);
    int x,y;
    for (int i = 0; i < m; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<vector<int>> sscout;
    tarjanSCC t;
    t.ssc(adj,sscout,1,n);
    int neededEdges = 0;
    for (int i = 0; i < sscout.size(); i++) {
        int s = sscout[i].size();
        if (s > 1000) { neededEdges = 1000000; }
        else { neededEdges += s * (s-1) / 2; }
        if (neededEdges > m) break;
    }
    cout << (neededEdges > m ? "NO" : "YES") << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("782E.in3","r",stdin);
  solve();
  return 0;
}
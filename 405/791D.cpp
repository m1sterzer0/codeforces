#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

// Easier problem:
// To sum the distance between all pairs of vertices in a tree, for each edge, we should count the number of paths through that edge.
// For each node (other than the root), we can associate the edge going to the root.  The number of paths that use that edge are 
//     (num nodes in the node's subtree) * (num nodes not in the node's subtree)
// Thus, with a simple postfix dfs, we can calculate the size of each node and perform the requisite calculation.
//
// Our problem:
// Our answer is "around" S/k (where S is the answer of the easier problem), but there is the problem of remainders.
// We need caluclate the length of paths from a root down to the children modulo k.  Since k is small, this is a manageable problem, and we can do
// this in the same DFS as the first part.

struct mydfs {
    int k;
    vector<vector<int>> *padj;
    array<array<int,5>,5> precomputedAdder;
    vector<int> subtreeSize;
    vector<vector<int>> subtreeRemainders;
    ull ktimesans;
    int maxnode;

    void init(vector<vector<int>> &adj, int maxnodein, int kin) {
        maxnode = maxnodein;
        k = kin;
        ktimesans = 0;
        padj = &adj;
        subtreeSize.clear(); subtreeSize.resize(maxnode+1,0);
        subtreeRemainders.clear(); subtreeRemainders.resize(maxnode+1);
        for (int i = 0; i <= maxnode; i++) { subtreeRemainders[i].resize(5,0); }
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                precomputedAdder[i][j] = ((i+j+1) % k == 0) ? 0 : k - ((i+j+1) % k);
            }
        }
    }

    ull dfs(int n, int p) {
        for (auto nn : (*padj)[n]) {
            if (nn == p) continue;
            dfs(nn,n);
            // 1) Deal with the bridging paths through the parent -- these go straight to the answer
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < k; j++) {
                    ktimesans += (ull) precomputedAdder[i][j] * (ull) subtreeRemainders[n][i] * (ull) subtreeRemainders[nn][j];
                }
            }

            // 2) Deal with paths that terminate on the current node
            for (int j = 0; j < k; j++) {
                    ktimesans += (ull) precomputedAdder[0][j] * (ull) subtreeRemainders[nn][j];
            }

            // 3) Add the remainders that go from the subtrees through the current node to somewhere else
            for (int j = 0; j < k; j++) {
                if (j+1 == k) { subtreeRemainders[n][0]   += subtreeRemainders[nn][j]; }
                else          { subtreeRemainders[n][j+1] += subtreeRemainders[nn][j]; }
            }

            // 4) Deal with my subtree size
            subtreeSize[n] += subtreeSize[nn];
        }
        subtreeSize[n] += 1;
        subtreeRemainders[n][0] += 1;  // For nodes that end on me
        ktimesans += (ull) subtreeSize[n] * (ull) (maxnode - subtreeSize[n]);
        return ktimesans;
    }
};


void solve() {
    int n,k; cin >> n >> k;
    vector<vector<int>> adj(n+1);
    int x,y;
    for (int i = 0; i < n-1; i++) {
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    mydfs d;
    d.init(adj,n,k);
    ull ans = d.dfs(1,-1);
    assert(ans % k == 0);
    cout << ans / k << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("791D.in3","r",stdin);
  solve();
  return 0;
}
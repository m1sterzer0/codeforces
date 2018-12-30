#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

// Just brute force it.  Solution should exist in 0 <= i,j <= 200

struct myMiniMax {
    int n;
    vector<int> nodes;
    vector<int> moves;
    vector<int> s1;
    vector<int> s2;

    void processLosingMove(int nn) {
        nodes[nn] = 1;
        int idx = nn % n;
        // Look for winning moves for Morty
        if (nn < n) {
            // Look for winning moves for Morty
            for (auto a : s2) {
                int space = (n + idx - a) % n;
                if (nodes[n+space] == 0) { processWinningMove(n+space); }
            }
        } else {
            // Look for winning moves for Rick
            for (auto a : s1) {
                int space = (n + idx - a) % n;
                if (nodes[space] == 0) { processWinningMove(space); }
            }
        }
    }

    void processWinningMove(int nn) {
        if (nn % n == 0) return; // These are losing moves.
        nodes[nn] = 2;
        int idx = nn % n;
        if (nn < n) {
            // Delete all the moves for morty that lead to this move
            for (auto a : s2) {
                int space = (n + idx - a) % n;
                moves[n+space]--;
                if ((moves[n+space] == 0) && (nodes[n+space] == 0)) { processLosingMove(n+space); }
            }
        } else {
            // Delete all the moves for Rick that lead to this move
            for (auto a : s1) {
                int space = (n + idx - a) % n;
                moves[space]--;
                if ((moves[space] == 0) && (nodes[space] == 0)) { processLosingMove(space); }
            }
        }
    }
};



void solve() {
    myMiniMax mm;
    int n; cin >> n; mm.n = n;
    int k1; cin >> k1;
    mm.s1.resize(k1);  for (int i = 0; i < k1; i++) { cin >> mm.s1[i]; }
    int k2; cin >> k2;
    mm.s2.resize(k2);  for (int i = 0; i < k2; i++) { cin >> mm.s2[i]; }
    mm.nodes.resize(2*n,0);
    mm.moves.resize(2*n,0);
    for (int i = 0; i < n; i++)   mm.moves[i] = k1;
    for (int i = n; i < 2*n; i++) mm.moves[i] = k2;
    mm.processLosingMove(0);
    mm.processLosingMove(n);

    for (int i = 1; i < n; i++) {
        if (i > 1) cout << " ";
        cout << ((mm.nodes[i] == 0) ? "Loop" : (mm.nodes[i] == 1) ? "Lose" : "Win");
    }
    cout << endl;

    for (int i = n+1; i < 2*n; i++) {
        if (i > n+1) cout << " ";
        cout << ((mm.nodes[i] == 0) ? "Loop" : (mm.nodes[i] == 1) ? "Lose" : "Win");
    }
    cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("787C.in1","r",stdin);
  solve();
  return 0;
}
#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n, m; cin >> n >> m;
//    array<array<char, 102>, 15> bldg;
    vector<ll> leftmost(n,-1);
    vector<ll> rightmost(n,-1);
    ll topFloor = n;
    for (int i = 0; i < n; i++) {
        string s;  cin >> s;
        for (int j = 0; j < m+2; j++) {
            if (s[j] == '1') {
                topFloor = min(topFloor,(ll) i);
                rightmost[i] = j;
                if (leftmost[i] == -1) leftmost[i] = j;
            }
        }
    }

    function<ll(int,int,int)> solveFloor = [&](int f, int start, int end) {
        if (end >= 0 && start != end) { return m+1; }
        if (start == 0) {
            ll left = (rightmost[f] == -1) ? 0 : 2 * rightmost[f];
            return end < 0 ? left / 2 : left;
        } else {
            ll right = (leftmost[f] == -1) ? 0  : 2 * ((m+1) - leftmost[f]);
            return end < 0 ? right / 2 : right;
        }
    };
    if (topFloor == n) { cout << 0 << endl; return; } 

    array<array<ll, 2>, 15> dp;
    dp[topFloor][0] = solveFloor(topFloor,0,-1);
    dp[topFloor][1] = solveFloor(topFloor,1,-1);
    for (int i = topFloor+1; i < n; i++) {
        dp[i][0] = min(1 + solveFloor(i,0,0) + dp[i-1][0], 1 + solveFloor(i,0,1) + dp[i-1][1]);
        dp[i][1] = min(1 + solveFloor(i,1,0) + dp[i-1][0], 1 + solveFloor(i,1,1) + dp[i-1][1]);
    }
    cout << dp[n-1][0] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("812B.in4","r",stdin);
    solve();
    return 0;
}

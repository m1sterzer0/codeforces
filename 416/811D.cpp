#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;


void solve() {
    ll n, m; cin >> n >> m;
    array<array<char,100>,100> board;

    vector<ll> parent(4*n*m,-2);
    for (ll j = 0; j < n; j++) {
        for (ll i = 0; i < m; i++) {
            cin >> board[j][i];
        }
    }

    function<ll(int,int,bool,bool)> encode = [&](int i, int j, bool lr, bool ud) {
        ll offset = lr ? (ud ? 0 : m*n) : (ud ? 2*m*n : 3*m*n);
        return offset + j * m + i;
    };

    function<void(int&,int&,bool&,bool&,ll)> decode = [&](int &i, int &j, bool &lr, bool &ud, ll nodenum) {
        ll bs = m*n;
        ll base = nodenum % bs;
        j = base / m;
        i = base % m;
        if (nodenum < bs)        { lr = true;  ud = true;  }
        else if (nodenum < 2*bs) { lr = true;  ud = false; }
        else if (nodenum < 3*bs) { lr = false; ud = true;  }
        else                     { lr = false; ud = false; }
    };


    // Quick BFS to find shortest path
    queue<pair<ll,ll>> q;
    ll start = encode(0,0,false,false);
    q.push({start,-1});
    ll lastNode = -1;
    while (!q.empty()) {
        ll n = q.front().first;
        ll p = q.front().second;
        q.pop();
        if (parent[n] > -2) continue; // been here before
        parent[n] = p;
        lastNode = n;
        int i,j;
        bool lr,ud;
        decode(i,j,lr,ud,n);
        if (board[j][i] == 'F') break;

        if (j > 0   && board[j-1][i] != '*' && (ud || j == n-1 || board[j+1][i] != '*')) { q.push({encode(i,j-1,lr,true), n}); } //up
        if (j < n-1 && board[j+1][i] != '*' && (ud || j == 0   || board[j-1][i] != '*')) { q.push({encode(i,j+1,lr,true), n}); } //down
        if (i > 0   && board[j][i-1] != '*' && (lr || i == m-1 || board[j][i+1] != '*')) { q.push({encode(i-1,j,true,ud), n}); } //left
        if (i < m-1 && board[j][i+1] != '*' && (lr || i == 0   || board[j][i-1] != '*')) { q.push({encode(i+1,j,true,ud), n}); } //right
    }

    // Generate list of moves
    vector<ll> moves;
    moves.push_back(lastNode);
    ll prevNode = lastNode;
    while (prevNode != start) {
        prevNode = parent[prevNode]; 
        moves.push_back(prevNode);
    }
    reverse(moves.begin(), moves.end());



    // Execute the moves
    ll idx = 0;
    bool lrflipped = false;
    bool udflipped = false;
    while (idx < moves.size()-1) {
        int lasti, lastj, curi, curj;
        bool zz1, zz2;
        decode(lasti,lastj,zz1,zz2,moves[idx]);
        decode(curi,curj,zz1,zz2,moves[idx+1]);
        char  move      = curj < lastj ? 'U' : curj > lastj ? 'D' : curi < lasti ? 'L' : 'R';
        char  oppmove   = curj < lastj ? 'D' : curj > lastj ? 'U' : curi < lasti ? 'R' : 'L';
        bool *pflipflag = curj != lastj ? &udflipped : &lrflipped;

        int ri, rj;
        cout << (*pflipflag ? oppmove : move) << endl; fflush(stdout);
        cin >> rj >> ri;
        while (ri != curi+1 || rj != curj+1) { 
            *pflipflag = true; 
            cout << oppmove << endl; 
            fflush(stdout); 
            cin >> rj >> ri;
        }
        idx++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("811D.in1","r",stdin);
    solve();
    return 0;
}

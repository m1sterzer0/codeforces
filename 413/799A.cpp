#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    ll n,t,k,d;
    cin >> n >> t >> k >> d;

    //without the oven
    priority_queue<int, vector<int>, greater<int>> mh;
    priority_queue<int, vector<int>, greater<int>> mh2;
    mh.push(t);
    ll cakes = 0;
    ll tt = 0;
    while (cakes < n) {
        tt = mh.top(); mh.pop(); cakes += k; mh.push(tt+t);
    } 

    mh2.push(t);
    mh2.push(d+t);
    cakes = 0;
    ll tt2 = 0;
    while (cakes < n) {
        tt2 = mh2.top(); mh2.pop(); cakes += k; mh2.push(tt2+t);
    } 
    if (tt2 < tt) cout << "YES" << endl;
    else          cout << "NO"  << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("799A.in1","r",stdin);
    solve();
    return 0;
}
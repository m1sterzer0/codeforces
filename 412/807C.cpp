#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    ll x,y,p,q;
    cin >> x >> y >> p >> q;
    // Special Cases
    if (x*q == y*p) { cout << 0 << endl; return; }
    if (p == 0 && x > 0) { cout << -1 << endl; return; }
    if (p == 1 && q == 1 && x < y) { cout << -1 << endl; return; }

    ll a;
    if (q*x < y*p) {
        // Step 1: Want minimum a such that (x+a)/(y+a) >= p/q <--> qx + qa >= py + pa <==> (q-p)a >= p*y-q*x
        a = (y*p-q*x) / (q-p); // should get us within 1
        if ((x+a)*q < (y+a)*p) a++;
    }    

    else {
        // Here we want a such that x / (y+a) <= p/q <==> qx <= py + pa <==> a >= (qx-pq)/p
        a = (q*x-p*y) / p; // should get us within 1
        if (x*q > (y+a)*p) a++;
    }
    // Step 2: increase y+a to the nearest multiple of q
    if ((y+a) % q > 0) { a += q - ((y+a) % q); }
    cout << a << endl; return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("782E.in3","r",stdin);
    int t; cin >> t;
    while (t--) { solve(); }
    return 0;
}

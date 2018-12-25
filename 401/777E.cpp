#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

struct ring {
    ull a;
    ull b;
    ull h;
    friend bool operator<(ring a, ring b) {
        return a.b < b.b || ((a.b == b.b) && (a.a < b.a));
    }
};

// Do it the slow way first, and then speed up with binary searches if needed
struct dp {
    vector<ull> radius;
    vector<ull> height;
    ull find(ull a) {
        auto nn = radius.size();
        if (nn == 0) return 0;
        if (a >= radius[nn-1]) { return 0; }
        for (int i = 0; i < nn; i++) {                   // Can be bin searched
            if (a < radius[i]) { return height[i]; }
        }
        return 0; // SHOULDN'T GET HERE
    }
    void update(ull b, ull htot) {
        auto nn = radius.size();
        if (nn != 0) {
            int i;
            for (i = 0; i < nn; i++) {                   // Can be bin searched
                if (htot >= height[i]) { break; }
            }
            if (i < nn) { radius.resize(i); height.resize(i); }
        }      
        radius.push_back(b);
        height.push_back(htot);
    }
};

void solve() {
    int n;  cin >> n;
    vector<ring> r(n);
    for (int i = 0; i < n; i++) { cin >> r[i].a >> r[i].b >> r[i].h; }
    sort(r.begin(),r.end());
    dp d;
    for (auto rr : r) {
        ull hAbove = d.find(rr.a);
        d.update(rr.b,hAbove+rr.h);
    }
    auto htot = d.find(0);
    cout << htot << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  //freopen("777E.in3","r",stdin);
  solve();
  return 0;
}
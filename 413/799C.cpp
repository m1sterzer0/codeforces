#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

struct fountain {
    ll b;
    ll p;
};

bool byPrice(const fountain &a, const fountain &b) { return a.p < b.p; }

ll findBestTwo(vector<fountain> &v, ll c) {
    ll res = 0;
    ll midx = 0;
    if (v.size() < 2) return 0;    
    // Sort the fountains by price
    sort(v.begin(),v.end(),byPrice);

    vector<fountain> myStack;
    myStack.push_back(v[0]);
    for (ll i = 1; i < v.size(); i++) {
        if (c >= v[i].p + myStack[0].p) {
            while (c < v[i].p + myStack[midx].p) { midx--; }
            ll trial = v[i].b + myStack[midx].b;
            res = max(res,trial);
        }

        if (v[i].b > myStack.back().b && midx == myStack.size()-1) {
            while (!myStack.empty() && myStack.back().p == v[i].p) { myStack.pop_back(); midx--; }
            myStack.push_back(v[i]); midx++;
        }

    }
    return res;
}


void solve() {
    vector<fountain> cFountains;
    vector<fountain> dFountains;
    ll n, c, d;
    cin >> n >> c >> d;
    ll bestc = -1;
    ll bestd = -1;
    for (int i = 0; i < n; i++) {
        ll b,p;
        char cc;
        cin >> b >> p >> cc;
        if (cc == 'C' && p <= c)      { cFountains.push_back({b,p}); bestc = max(b,bestc); }
        else if (cc == 'D' && p <= d) { dFountains.push_back({b,p}); bestd = max(b,bestd); }
    }

    ll best = 0;
    if (bestc > 0 && bestd > 0) { best = bestc + bestd; }
    ll best2 = findBestTwo(cFountains,c);
    best = max(best,best2);
    ll best3 = findBestTwo(dFountains,d);
    best = max(best,best3);
    cout << best << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("tc1","r",stdin);
    solve();
    return 0;
}

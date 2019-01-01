#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    ll n; cin >> n;
    priority_queue<int, vector<int>, greater<int>> mh11;
    priority_queue<int, vector<int>, greater<int>> mh12;
    priority_queue<int, vector<int>, greater<int>> mh13;
    priority_queue<int, vector<int>, greater<int>> mh22;
    priority_queue<int, vector<int>, greater<int>> mh23;
    priority_queue<int, vector<int>, greater<int>> mh33;
    vector<int> p(n), a(n), b(n);
    for (ll i = 0; i < n; i++) { cin >> p[i]; }
    for (ll i = 0; i < n; i++) { cin >> a[i]; }
    for (ll i = 0; i < n; i++) { cin >> b[i]; }
    for (ll i = 0; i < n; i++) {
        if      ( a[i] == 1 && b[i] == 1) { mh11.push(p[i]); }
        else if ( a[i] == 1 && b[i] == 2) { mh12.push(p[i]); }
        else if ( a[i] == 1 && b[i] == 3) { mh13.push(p[i]); }
        else if ( a[i] == 2 && b[i] == 1) { mh12.push(p[i]); }
        else if ( a[i] == 2 && b[i] == 2) { mh22.push(p[i]); }
        else if ( a[i] == 2 && b[i] == 3) { mh23.push(p[i]); }
        else if ( a[i] == 3 && b[i] == 1) { mh13.push(p[i]); }
        else if ( a[i] == 3 && b[i] == 2) { mh23.push(p[i]); }
        else if ( a[i] == 3 && b[i] == 3) { mh33.push(p[i]); }
    }
    ll m; cin >> m;
    for (ll i = 0; i < m; i++) {
        ll c; cin >> c;
        ll price = 1000000001;
        if (c == 1) {
            if (!mh11.empty() && mh11.top() < price) price = mh11.top();
            if (!mh12.empty() && mh12.top() < price) price = mh12.top();
            if (!mh13.empty() && mh13.top() < price) price = mh13.top();
        }
        else if (c == 2) {
            if (!mh12.empty() && mh12.top() < price) price = mh12.top();
            if (!mh22.empty() && mh22.top() < price) price = mh22.top();
            if (!mh23.empty() && mh23.top() < price) price = mh23.top();
        }
        else {
            if (!mh13.empty() && mh13.top() < price) price = mh13.top();
            if (!mh23.empty() && mh23.top() < price) price = mh23.top();
            if (!mh33.empty() && mh33.top() < price) price = mh33.top();
        }
        if (price == 1000000001) { cout << -1 << " "; }
        else {
            cout << price << " ";
            if (!mh11.empty() && mh11.top() == price) mh11.pop();
            if (!mh12.empty() && mh12.top() == price) mh12.pop();
            if (!mh13.empty() && mh13.top() == price) mh13.pop();
            if (!mh22.empty() && mh22.top() == price) mh22.pop();
            if (!mh23.empty() && mh23.top() == price) mh23.pop();
            if (!mh33.empty() && mh33.top() == price) mh33.pop();
        }
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("782E.in3","r",stdin);
    solve();
    return 0;
}

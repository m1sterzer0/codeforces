#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    ll n; cin >> n;
    vector<array<int,5>> scores(n);

    vector<int> correct(5,0);
    for (ll i=0; i < n; i++) {
        for (ll j = 0; j < 5; j++) {
            cin >> scores[i][j];
            if (scores[i][j] >= 0) { correct[j]++; }
        }
    }

    // Vasya can't submit "correct" solutions for problems which he hasn't solved
    // Thus, Vasya can only submit "correct" solutions when he has solved a problem slower than Petya.
    vector<int> fakeSubmissions(5,0);
    for (ll i = 0; i < 5; i++) {
        if (scores[0][i] >= 0 && scores[1][i] >= 0 && scores[1][i] < scores[0][i]) { fakeSubmissions[i] = 1; }
    }

    // Find the interesting points
    priority_queue<int, vector<int>, greater<int>> mh;
    mh.push(0);
    for (ll i = 0; i < 5; i++) {
        if ((scores[0][i] >= 0 && scores[1][i] < 0) || (scores[0][i] >= 0 && scores[1][i] >= 0 && scores[0][i] < scores[1][i])) {
            if (2  * correct[i] > n) mh.push(2*correct[i] - n);
            if (4  * correct[i] > n) mh.push(4*correct[i] - n);
            if (8  * correct[i] > n) mh.push(8*correct[i] - n);
            if (16 * correct[i] > n) mh.push(16*correct[i] - n);
            if (32 * correct[i] > n) mh.push(32*correct[i] - n);
        }
        else if (scores[0][i] >= 0 && scores[1][i] >= 0 && scores[0][i] < scores[1][i]) {
            if (32 * correct[i] <= n) { ll x = (n - 32 * correct[i]) / 31 + 1; mh.push(x); } 
            if (16 * correct[i] <= n) { ll x = (n - 16 * correct[i]) / 15 + 1; mh.push(x); } 
            if ( 8 * correct[i] <= n) { ll x = (n -  8 * correct[i]) /  7 + 1; mh.push(x); }  
            if ( 4 * correct[i] <= n) { ll x = (n -  4 * correct[i]) /  3 + 1; mh.push(x); } 
            if ( 2 * correct[i] <= n) { ll x = (n -  2 * correct[i]) /  1 + 1; mh.push(x); } 
        }
    }

    // test to see if we work
    function<bool(ll)> test = [&](ll t) {
        ll diff = 0;
        ll total = t + n; 
        for (ll i = 0; i < 5; i++) {
            ll cc = correct[i] + fakeSubmissions[i] * t;
            ll mult = (2 * cc > total)  ? 1 :
                      (4 * cc > total)  ? 2 :
                      (8 * cc > total)  ? 3 :
                      (16 * cc > total) ? 4 :
                      (32 * cc > total) ? 5 : 6;
            if (scores[0][i] >= 0) { diff +=  mult * (500 - 2 * scores[0][i]); }
            if (scores[1][i] >= 0) { diff -=  mult * (500 - 2 * scores[1][i]); }
        }
        return (diff > 0);
    };

    while (!mh.empty()) {
        ll x = mh.top(); mh.pop();
        if (test(x)) { cout << x << endl; return; }
    }
    cout << -1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("807D.in33","r",stdin);
    solve();
    return 0;
}

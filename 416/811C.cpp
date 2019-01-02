#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

void solve() {
    
    ll n; cin >> n;
    vector<ll> a(n);
    vector<ll> lastPerCity(5001,-1);
    vector<ll> firstPerCity(5001,-1);
    for (ll i = 0; i < n; i++) { 
        cin >> a[i];
        if (firstPerCity[a[i]] == -1) firstPerCity[a[i]] = i;
        lastPerCity[a[i]] = i;
    }

    vector<ll> minTrainEnd(n,-1);
    vector<ll> minTrainValue(n,0);

    for (ll i = 0; i < n; i++) {
        if (i != firstPerCity[a[i]]) continue;
        ll value = a[i];
        bool goodTrain = true;
        ll maxj = lastPerCity[a[i]];
        for (ll j = i+1; j <= maxj; j++) {
            if      (firstPerCity[a[j]] < i)  { goodTrain = false; break; }
            else if (firstPerCity[a[j]] == j) { maxj = max(maxj,lastPerCity[a[j]]); value = value ^ a[j]; }
        }
        if (goodTrain) {
            minTrainEnd[i]  =  maxj;
            minTrainValue[i] = value; 
        }
    }

    vector<ll> dp(n+1,0);
    dp[n-1] = minTrainValue[n-1];
    for (ll i = n-2; i >= 0; i--) {
        dp[i] = dp[i+1];
        ll value = 0;
        ll s = i;
        while (s < n && minTrainEnd[s] >= 0) {
            value = value ^ minTrainValue[s];
            s = minTrainEnd[s] + 1;
            dp[i] = max(dp[i], value + dp[s]);
        }
    }

    cout << dp[0] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

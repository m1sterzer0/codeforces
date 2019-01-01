#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

void solve() {
    string oleg; cin >> oleg;
    string igor; cin >> igor;
    ll n = oleg.size();
    sort(oleg.begin(),oleg.end());
    sort(igor.begin(),igor.end());
    reverse(igor.begin(),igor.end());
    string ans(n,'?');
    ll olegFidx(0), olegBidx((n-1)/2), igorFidx(0), igorBidx(n/2-1), ansFidx(0), ansBidx(n-1);
    for (int i = 0; i < n; i += 2) {
        // Oleg's turn
        if (oleg[olegFidx] < igor[igorFidx]) { ans[ansFidx] = oleg[olegFidx]; ansFidx++; olegFidx++; } // My lowest is better than his biggest, so I need to place it now
        else                                 { ans[ansBidx] = oleg[olegBidx]; ansBidx--; olegBidx--; } // All of igors are better than mine, so I place mine in the end in reverse order.

        if ((i+1) < n) {
            if (oleg[olegFidx] < igor[igorFidx]) { ans[ansFidx] = igor[igorFidx]; ansFidx++; igorFidx++; } 
            else                                 { ans[ansBidx] = igor[igorBidx]; ansBidx--; igorBidx--; } 
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("794C.in1","r",stdin);
    solve();
    return 0;
}


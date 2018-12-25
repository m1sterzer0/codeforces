#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n,k;
    cin >> n >> k;
    vector<int64_t> affectionValues(n,0);
    for (int i = 0; i < n; i++) { cin >> affectionValues[i]; }

    // Partial sums
    vector<int64_t> partialSums(n,0);
    partialSums[0] = affectionValues[0];
    for (int i = 1; i < n; i++) { partialSums[i] = partialSums[i-1] + affectionValues[i]; }

    // Deal with the values for k
    // If k == 1, then all of the powers of k are 1, so we only have one case
    // If k == -1, then we have 2 cases
    // Else, we load up until we exceed 10^14/-10^14
    vector<int64_t> targetValues;
    if (k == 1) { targetValues.push_back(1); }
    else if (k == -1) { targetValues.push_back(1); targetValues.push_back(-1); }
    else {
        int64_t t = 1;
        while (t <= 100000000000000L && t >= -100000000000000L) {
            targetValues.push_back(t);
            t *= k;
        }
    }

    // FAST ATTEMPT
    map<int64_t,int64_t> p;
    int64_t combos = 0;
    for (auto s : partialSums) {
        for (auto t : targetValues) {
            if (s == t) {
                combos += 1;
                if (p.find(0) != p.end()) combos += p[0];
            }
            else {
                int64_t lt = s - t;
                if (p.find(lt) != p.end()) combos += p[lt];
            }
        }
        p[s] += 1;
    }
    cout << combos << endl;    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    freopen("776C.in1","r",stdin);
    solve();
    return 0;
}
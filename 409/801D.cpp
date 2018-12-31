#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;

void solve() {
    int n; cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) { cin >> x[i] >> y[i]; }
    // I think the answer is either the 0.5 * the minimum side length, or 
    // 0.5 * the distance to the line formed by the adjacent vertices.
    double best = 1e99;
    for (int i = 0; i < n; i++) {
        double x1 = (i == 0) ? x[n-1] : x[i-1];
        double y1 = (i == 0) ? y[n-1] : y[i-1];
        double x2 = x[i];
        double y2 = y[i];
        double x3 = (i == n-1) ? x[0] : x[i+1];
        double y3 = (i == n-1) ? y[0] : y[i+1];

        double d1 = sqrt( (x2-x1) * (x2-x1) + (y2-y1) * (y2-y1) );
        double d2 = sqrt( (x2-x3) * (x2-x3) + (y2-y3) * (y2-y3) );
        
        // Do the projection of 12 onto 13
        double d13     = sqrt( (x3-x1) * (x3-x1) + (y3-y1) * (y3-y1) );
        double dotprod = (x2-x1) * (x3-x1) + (y2-y1) * (y3-y1);
        double uvx     = (x3-x1) / d13;
        double uvy     = (y3-y1) / d13;
        double projPointx = x1 + uvx * (dotprod / d13);
        double projPointy = y1 + uvy * (dotprod / d13);
        double d3 = sqrt( (x2 - projPointx) * (x2 - projPointx) + (y2 - projPointy) * (y2 - projPointy) );
        if (best > 0.5 * d1) best = 0.5 * d1;
        if (best > 0.5 * d2) best = 0.5 * d2;
        if (best > 0.5 * d3) best = 0.5 * d3;
    }
    printf("%.10e\n", best); 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("801D.in1","r",stdin);
    solve();
    return 0;
}

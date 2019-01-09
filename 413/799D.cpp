#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;

void solve() {
    ll a,b,h,w,n;
    cin >> a >> b >> h >> w >> n;
    vector<ll> sizes(n);
    for (ll i = 0; i < n; i++) { cin >> sizes[i]; }
    std::sort(sizes.begin(), sizes.end());
    std::reverse(sizes.begin(), sizes.end());
 
    ll targa, targb;
    ll best = infll;

    function<bool(ll,ll,ll,ll)> dfs = [&](ll a, ll b, ll i, ll imax) {
        //cout << "DEBUG: "  << a << " " << b << " " << i << " " << best << endl;
        if (a >= targa && b >= targb) { return true; }
        if (i >  imax) { return false; }

        if (sizes[i] == 2) { 
            while (i <= imax && a < targa) { a *= 2; i++; }
            while (i <= imax && b < targb) { b *= 2; i++; }
            return (a >= targa && b >= targb);
        }

        return ((a < targa) && dfs(a*sizes[i],b,i+1,imax)) || ((b < targb) &&  dfs(a, b*sizes[i],i+1,imax));
    };

    for (ll ii = 0; ii < 2; ii++) {
        targa = (a + (h-1)) / h;
        targb = (b + (w-1)) / w;
        ll targprod = targa * targb;
        ll prod = 1;
        if (targprod == 1) { cout << 0 << endl; return; }
        for (ll i = 0; i < n; i++) {
            if (sizes[i] == 1) break;
            if (prod < targprod) prod *= sizes[i];
            if ((prod >= targprod) && dfs(1,1,0,i)) { best = min(best,i+1); break;}
        }
        ll temp;
        temp = h; h = w; w = temp;
    }
        
    if (best == infll) { cout << -1 << endl; }
    else               { cout << best << endl; }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("799D.in3","r",stdin);
    solve();
    return 0;
}

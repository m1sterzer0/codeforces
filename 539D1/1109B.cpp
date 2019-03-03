#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ull;
typedef int64_t  ll;
const ll infll = 9223372036854775807LL;
#define PB push_back  
#define MP make_pair  
#define SZ(v) ((ll)(v).size())  
#define FOR(i,a,b) for(ll i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(ll i=(a);i<=(b);++i)  
#define REPE(i,n) FORE(i,0,n)  
#define FORSZ(i,a,v) FOR(i,a,SZ(v))  
#define REPSZ(i,v) REP(i,SZ(v)) 

bool checkFor1(string s) {
    // We are good if s is not a palendrome
    // If s is a palindrome and is odd length, we are bad
    // If s is a palindrome and is even length, we recurse
    bool ispal = true;
    ll n = (ll) s.size();
    REP(i,n) {
        if (s[i] != s[n-1-i]) { ispal = false; break; } 
    }
    if (!ispal) return true;
    if (n & 1) return false;
    return checkFor1(s.substr(0,n/2));
}


void solve() {
    string s; cin >> s;
    ll n = (ll) s.size();
    // A size 1 or size 2 or size 3 string can't be made to work
    if (n <= 3) { printf("Impossible\n"); }
    else {
        bool same = true;
        FOR(i,1,n/2) {
            if (s[i] != s[i-1]) { same=false; break; }
        }
        if (same) { printf("Impossible\n"); }
        else if (n & 1) { printf("2\n"); }
        else if (checkFor1(s.substr(0,n/2))) { printf("1\n"); }
        else { printf("2\n"); }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    solve();
    return 0;
}

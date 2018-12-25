#include <bits/stdc++.h>
using namespace std;

struct totientCalc {
    vector<uint64_t> primes;
    void sieve(uint64_t maxPrime);
    uint64_t totient(uint64_t x);
};

void totientCalc::sieve(uint64_t maxPrime) {
    // We can optimize this later for storage.
    vector<bool> sieve(maxPrime+1,true);
    primes.clear();
    if (maxPrime < 2) return; primes.push_back(2);
    if (maxPrime < 3) return;
    for (uint64_t i = 4; i <= maxPrime; i+=2)   { sieve[i] = false; }
    for (uint64_t i = 9; i <= maxPrime; i+=2*3) { sieve[i] = false; }
    for (uint64_t j = 5; j * j <= maxPrime; j += 6) {
        uint64_t j1 = j;
        uint64_t j2 = j+2;
        if (sieve[j1]) {
            for (uint64_t i = j1*j1; i*i <= maxPrime; i += 2*j1) { sieve[i] = false; } 
        }
        if (sieve[j2]) {
            for (uint64_t i = j2*j2; i*i <= maxPrime; i += 2*j2) { sieve[i] = false; } 
        }
    }
    for (uint64_t i = 3; i <= maxPrime; i += 2) { 
        if (sieve[i]) { primes.push_back(i); }
    }
}

uint64_t totientCalc::totient(uint64_t x) {
    if (x == 1) { return 1; }
    uint64_t res = x;
    uint64_t residual = x;
    for (auto p : primes) {
        //cout << "DEBUG: " << p << endl;
        if ((residual / p) * p == residual) {
            while  ((residual / p) * p == residual) { residual /= p; }
            res /= p; res *= (p-1);
        }
        //cout << "DEBUG: " << p << " RESIDUAL: " << res << endl;
        if (p*p > residual) break;
    }
    if (residual > 1) { res /= residual; res *= (residual-1); }
    return res; 
}

void solve() {
    uint64_t n,k;
    cin >> n >> k;
    totientCalc t;
    t.sieve(1000000);
    uint64_t res = t.totient(n);
    for (uint64_t kk = 3; kk <= k; kk += 2) {
        res = t.totient(res);
        if (res == 1) { break; }
    }
    cout << (res % 1000000007ULL) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("776C.in1","r",stdin);
    solve();
    return 0;
}
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

//////////////////////////////////////////////////
//
// SECTION A: FUNDAMENTALS
//
//////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// SUBSECTION A1: BINARY EXPONENTIATION
// https://cp-algorithms.com/algebra/binary-exp.html
////////////////////////////////////////////////////////////

// Basic idea is to calculate a^n by calculating a^1, a^2, a^4, a^8, ... by squaring and multiplying the relevant
// terms into the result based on the binary representation of n.  O(log n).

ll binPow(ll a, ll b) { ll res = 1; while (b > 0) { if (b & 1) res *= a; a *= a; b >>= 1; } return res; }

// We can use the same algorithm to raise a^b % m.
ll binPowMod(ll a, ll b, ll m) { a %= m; ll res = 1; while (b > 0) { if (b & 1) res = (res * a) % m; a = (a * a) % m; b >>= 1; } return res; }

// Note if m is prime, we have that a^b % m == a ^ (b % (m-1)) % m by Fermat's little theorem.  This can help in corner cases.

// Other uses:
// * Applying a permutation multiple times.
// * Applying a rigid motion n times.
// * Matrix exponentiation and/or applying a linear transformation n times.
// * Calculating fibonacci numbers (application of matrix exponentiation)
// * Finding the number of paths of length k.
// * Multiplying two numbers modulo m, where a % m and b % m fit in the data type but (a % m) * (b % m) does NOT.
//   Here we use addition/multiplication instead of multiplication/exponentiation, but the idea is the same.


////////////////////////////////////////////////////////////
// SUBSECTION A2: EUCLIDEAN ALGORITHM
// https://cp-algorithms.com/algebra/euclid-algorithm.html
////////////////////////////////////////////////////////////

// Basics
ll gcd (ll a, ll b) { return (b == 0) ? a : gcd(b, a%b); }
ll lcm (ll a, ll b) { return (a*b) / gcd(a,b); }


////////////////////////////////////////////////////////////
// SUBSECTION A3: EXTENDED EUCLIDEAN ALGORITHM
// https://cp-algorithms.com/algebra/extended-euclid-algorithm.html
////////////////////////////////////////////////////////////

// Here, we also find coefficients x and y such that x*a + y*b = gcd(a,b)
ll gcdExtended(ll a, ll b, ll &x, ll &y) {
    if (a == 0) { x = 0; y = 1; return b; }
    ll x1,y1;
    ll d = gcdExtended(b%a, a, x1, y1);
    x = y1 - (b / a) * x1; y = x1; return d;
}


////////////////////////////////////////////////////////////
// SUBSECTION A4: LINEAR DIOPHANTANE EQUATIONS
// https://cp-algorithms.com/algebra/linear-diophantine-equation.html
////////////////////////////////////////////////////////////

bool diophantineFindAnySol(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = gcdExtended(abs(a),abs(b),x0,y0);
    if (c % g) return false;
    x0 = (a<0) ? -(x0 * (c/g)) : x0 * (c/g);
    y0 = (b<0) ? -(y0 * (c/g)) : y0 * (c/g);
    return true;
}

// This finds the number of solutions with x in [minx,maxx] and y in [miny,maxy]
void diophantineShiftSol(ll &x, ll &y, ll a, ll b, ll cnt) { x += cnt * b; y -= cnt * a; }
ll diophantineFindNumSol(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy) {
    ll x, y, g;
    if (!diophantineFindAnySol(a,b,c,x,y,g)) return 0;
    a /= g; b /= g;

    ll sign_a = a > 0 ? 1 : -1;
    ll sign_b = b > 0 ? 1 : -1;
    diophantineShiftSol(x,y,a,b,(minx-x)/b);
    if (x < minx) diophantineShiftSol(x,y,a,b,sign_b);
    if (x > maxx) return 0;
    ll lx1 = x;
    diophantineShiftSol(x,y,a,b,(maxx-x)/b);
    if (x > maxx) diophantineShiftSol(x,y,a,b,-sign_b);
    ll rx1 = x;
    diophantineShiftSol(x,y,a,b,-(miny-y)/a);
    if (y < miny) diophantineShiftSol(x,y,a,b,-sign_a);
    if (y > maxy) return 0;
    ll lx2 = x;
    diophantineShiftSol(x,y,a,b,-(maxy-y)/a);
    if (y > maxy) diophantineShiftSol(x,y,a,b,sign_a);
    ll rx2 = x;
    if (rx1 > lx1) swap(rx1,lx1);
    if (rx2 > lx2) swap(rx2,lx2);
    ll lx = max(lx1,lx2);
    ll rx = max(rx1,rx2);
    return (lx > rx) ? 0LL : 1LL + (rx - lx) / abs(b);
} 

// If you want to find the solution with the minimum x+y on a range, we just modify
// the solution above and look at which endpoint gives the better solution.  x+y should
// be monotonic.


////////////////////////////////////////////////////////////
// SUBSECTION A5: FIBONACCI NUMBERS
// https://cp-algorithms.com/algebra/fibonacci-numbers.html
////////////////////////////////////////////////////////////

// F[0] = 0, F[1] = 1, F[n] = F[n-1] + F[n-2] for n >= 2
//
// Interesting Properties:
// * Cassini's Identity:   F[n-1]*F[n+1] - F[n]*F[n] = (-1)^n
// * The "addition" rule:  F[n+k] = F[k]F[n+1] + F[k-1]F[n]
// * The "doubling" rule:  F[2n] = F[n] * (F[n+1] + F[n-1])   (can be derived from above)
// * Divisibility :        F[n] | F[nk]
// * GCD identity :        gcd(F[m],F[n]) = F[gcd(m,n)]
// * Lame's theorem:       Fibonacci numbers are the worst possible inputs for the runtime of Euclidean algorithm

// Fibonacci Coding
// Zeckendorf's Theorem -- Every natural number can be uniquely represented as a sum of Fibonacci numbers.
// See https://cp-algorithms.com/algebra/fibonacci-numbers.html for more details on a coding algorithm.

// nth Fibonacci number (math -- not super useful)
// Let phi = (1 + sqrt(5)) / 2
// Let zeta = (1 - sqrt(5)) / 2
// Then F[n] = (1/sqrt(5)) * (phi^n - zeta^n) = round( (1/sqrt(5)) * phi^n )
// This needs lots of accuracy, so not very useful for cp.

// Matrix math
// [ F[n+1] ]  = [ 1 1 ] * [ F[n]   ]
// [ F[n]   ]    [ 1 0 ]   [ F[n-1] ]
// Can use fast matrix exponentiation to calculate a matrix that will advance the pair an arbitrary amount

// Doubling method for calculating the nth fibonaci number
// Use F[2n]   = F[n] * (F[n+1] + F[n-1]) = F[n] * (F[n+1] + F[n+1] - F[n]) = F[n] * (2 * F[n+1] - F[n])
// Use F[2n+1] = F[n+(n+1)] = F[n+1]*F[n+1] + F[n]*F[n]

pair<ll,ll> fibonacci(ll n) {
    if (n == 0) return {0LL, 1LL};
    auto p = fibonacci(n >> 1);
    ll c = p.first * (2 * p.second - p.first);
    ll d = p.first+p.first + p.second*p.second;
    if (n & 1) return {d, c+d};
    return {c,d};
}



////////////////////////////////////////////////////////////
//
// SECTION B: PRIME NUMBERS
//
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// SUBSECTION B1: SIEVE OF ERATOSTHENES
// https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html
////////////////////////////////////////////////////////////

void sieve(vector<ll> &primes, vector<bool> &isPrime, ll n) {
    primes.clear();
    isPrime.assign(n+1,true);
    isPrime[0] = false; isPrime[1] = false;
    for (ll j = 4; j <= n; j += 2) { isPrime[j] = false; }
    for (ll i = 3; i * i < n; i += 2) {
        if (!isPrime[i]) continue;
        ll inc = i+i;
        for (ll j = i * i; j <= n; j += inc) isPrime[j] = false;
    }
    primes.push_back(2);
    for (ll i = 3; i <= n; i += 2) { if (isPrime[i]) primes.push_back(i); }
}

// Memory efficient block sieve for counting primes (see page for more details)


////////////////////////////////////////////////////////////
// SUBSECTION B2: SIEVE OF ERATOSTHENES
// https://cp-algorithms.com/algebra/prime-sieve-linear.html
////////////////////////////////////////////////////////////

// Linear time factor sieve
void factorSieve(vector<ll> &primes, vector<ll> lp, ll n) {
    primes.clear();
    lp.assign(n+1,0LL);
    FORE(i,2,n) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes.push_back(i);
        }

        ll lpi = lp[i];
        for (auto &p : primes) {
            if (p > lpi) break;
            ll ip = i *p;
            if (ip > n) break;
            lp[ip] = p;
        }
    }
}



////////////////////////////////////////////////////////////
//
// SECTION C: NUMBER-THEORETIC FUNCTIONS
//
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// SUBSECTION C1: EULER'S TOTIENT FUNCTION
// https://cp-algorithms.com/algebra/phi-function.html
////////////////////////////////////////////////////////////

// phi(n) = number of integers x in [1,n] with gcd(n,x) = 1.
//
// Properties:
// * phi(p) = p - 1    (all integers in [1,p-1] are relatively prime to p)
// * phi(p^k) = p^k - p^(k-1)
// * phi(a*b) = phi(a) * phi(b) * gcd(a,b) / phi(gcd(a,b))
// * For n = p_1 ^ a_1 * p_2 ^ a_2 * ... * p_k ^ a_k (where p_i are distinct primes), we have
//   phi(n) = n * (1 - 1/p_1) * (1 - 1/p_2) * ... * (1 - 1/p_k)

ll totient(ll n) {
    ll res = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            res -= res / i;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

// Other more complex properties are explained on the web page.


////////////////////////////////////////////////////////////
// SUBSECTION C2: NUMBER OF DIVISORS / SUM OF DIVISORS
// https://cp-algorithms.com/algebra/divisors.html
////////////////////////////////////////////////////////////

// Let n = p_1 ^ a_1 * p_2 ^ a_2 * ... * p_k ^ a_k.
// The number of divisors d(n) = (1 + a_1) * (1 + a_2) * ... * (1 + a_k)
// The sum of the divisors  sigma(n) = [ (p_1 ^ a_1 - 1) / (p_1 - 1) ] * [ (p_2 ^ a_2 - 1) / (p_2 - 1) ] * ... * [ (p_k ^ a_k - 1) / (p_k - 1) ]
// Both d(n) and sigma(n) are multiplicative functions f(ab) = f(a) * f(b), which have interesting properties (e.g. Dirichlet convolution)
//    (See: https://en.wikipedia.org/wiki/Multiplicative_function)



////////////////////////////////////////////////////////////
//
// SECTION D: MODULAR ARITHMETIC
//
////////////////////////////////////////////////////////////

// Modular Combinatorics
const  ll mod = 1000000007;
inline ll madd(ll x, ll y) { ll r = x + y; if (r >= mod) { r -= mod; } return r; }
inline ll msub(ll x, ll y) { return x >= y ? x - y : x + mod - y; }
inline ll mmul(ll x, ll y) { return x * y % mod; }
inline ll mpow(ll x, ll p) { ll r=1; while (p) { if (p & 1) r = mmul(r,x); x = mmul(x,x); p = p >> 1; } return r; } 
inline ll minv(ll x)       { return mpow(x,mod-2); }
inline bool minv2(ll a, ll &ans) { ll x,y; ll g = gcdExtended(a, mod, x, y); if (g != 1) return false; ans = (x % mod + mod) % mod; return true; }

struct modularCombinatorics {
    vector<ll> fact, ifact;
    void init(ll lim) {
        fact.assign(lim+1,1LL); ifact.assign(lim+1,1LL);
        for (ll i = 2; i <= lim; i++) {
            fact[i] = mmul(fact[i-1],i);
            ifact[i] = minv(fact[i]);
        }
    }
    ll comb(ll n, ll k) {
        if (k > n) { return 0; }
        return mmul(mmul(fact[n],ifact[k]),ifact[n-k]);
    }
};


////////////////////////////////////////////////////////////
// SUBSECTION D1: MODULAR MULTIPLICATIVE INVERSE
// https://cp-algorithms.com/algebra/module-inverse.html
////////////////////////////////////////////////////////////

// * You can use extended euclidean algorithm to find x,y w/ a*x + m*y = 1.
//   Taking both sides modulo m, we get a*x = 1, so x is the multiplicative modular inverse.
// * Note that if m is prime, (a) * (a^(m-2)) = a^(m-1) = 1, so we can use binary exponentiation to get the inverse.
// * If we want to generate an array of multiplicative inverses with a prime modulus, we can get down to linear time using this function:

void mInvArr(vector<ll> &invArr, ll n, ll m) {
    invArr.assign(n+1,1LL);
    FORE(i,2,n) { invArr[i] = (m - (m/i) * invArr[m%i] % m) % m; }
}


////////////////////////////////////////////////////////////
// SUBSECTION D2: LINEAR CONGRUENCE EQUATION
// https://cp-algorithms.com/algebra/linear_congruence_equation.html
////////////////////////////////////////////////////////////

// * Trying to solve a * x = b (mod m)
// * Use inverses:
//   * If gcd(a,m) = 1, then we can find the unique solution x = b * a^-1 (mod m).
//   * If gcd(a,m) = g > 1, then we only have solutions if g | b.
//     In this case, let (a',b',m') = (a/g,b/g,m/g) and now consider a' * x = b' (mod m').
//     We can solve this one with inverses for the "base" solution.  Call this base solution x'.
//     All solutions are of form x_i = (x' + i * n') (mod n) for i in [0,g-1].  (i.e. there are g solutions).
// * You can also turn the equation to a*x - b = -y*n --> a*x + y*n = b and we can use
//   techniques for solving Linear Diophantane equations.


////////////////////////////////////////////////////////////
// SUBSECTION D3: CHINESE REMAINDER THEOREM (AND BIGINT)
// https://cp-algorithms.com/algebra/chinese-remainder-theorem.html
////////////////////////////////////////////////////////////

// Let p = p_1 * p_2 * ... * p_k where all (p_i,p_j) are relatively prime.
// Also assume we have the set of equivalence relations:
// a = a_1 (mod p_1), a = a_2 (mod p_2), ... , a = a_k (mod p_k)
// CRT says that this system of equations only has one solution mod p.

// Garner's algorithm
// A number in [0,p-1] can be uniquely represented as an array (a_1,a_2,...,a_k)
// We look for a solution of the form a = x_1 + x_2*p_1 + x_3*p_1*p_2 + ... + x_k*p_1*p_2*...*p_(k-1)
//     Step 0: Calculate r_ij = (p_i)^-1 (mod p_j)
//     Step 1: Looking at the first equation, we get                                    x1 = a_1 (mod p_1)
//     Step 2: Looking at the second equation, we get x_1 + x_2*p_1 = a_2 (mod p_2) --> x2 = (a_2 - x_1) * r_12
//     Step 3: Looking at the third equation,  we get                               --> x3 = ((a_3 - x_1) * r_13 - x_2) * r_23

// DUMMY BIGINT STRUCTURE
struct bigInt {
    const int base = 1000000000;
    const int baseDigits = 9;
    vector<int> a;
    int sign;
    bigInt()     {return;} //DUMMY CODE
    bigInt(ll v) {return;} //DUMMY CODE
    friend bigInt operator+ (const bigInt &a, const bigInt &b) { return bigInt(1); } //DUMMY CODE
    friend bigInt operator+ (const bigInt &a, ll b)            { return bigInt(1); } //DUMMY CODE
    friend bigInt operator+ (ll b, const bigInt &a)            { return bigInt(1); } //DUMMY CODE
    friend bigInt operator* (const bigInt &a, const bigInt &b) { return bigInt(1); } //DUMMY CODE
    friend bigInt operator* (const bigInt &a, ll b)            { return bigInt(1); } //DUMMY CODE
    friend bigInt operator* (ll b, const bigInt &a)            { return bigInt(1); } //DUMMY CODE
    void operator +=(const bigInt &a) {return;} //DUMMY CODE
    void operator +=(ll &a) {return;}           //DUMMY CODE
    void operator *=(const bigInt &a) {return;} //DUMMY CODE
    void operator *=(ll &a) {return;}           //DUMMY CODE
};

inline ll mpow2(ll x, ll p, ll m) { ll r=1; while (p) { if (p & 1) r = (r*x) % m; x = (x*x) % m; p = p >> 1; } return r; } 

bigInt gardner(vector<ll> &a, vector<ll> &p) {
    bigInt ans(0);
    bigInt mult(1);
    ll n = a.size();
    vector<vector<ll>> r(n);
    vector<ll> x(n);
    REP(i,n) {
        r[i].assign(n,0);
        REP(j,n) {
            if (i == j) continue;
            r[i][j] = mpow2(p[i],p[j]-2,p[j]);
        }
    }
    REP(i,n) {
        x[i] = a[i];
        REP(j,i) { x[i] = ((p[i] + x[i] - x[j]) % p[i]) * r[j][i] % p[i]; }
        ans += mult * x[i];
        mult *= p[i];
    }
    return ans;
}


////////////////////////////////////////////////////////////
// SUBSECTION D4: Factorial Modulo p in O(plogn)
// https://cp-algorithms.com/algebra/factorial-modulo.html
////////////////////////////////////////////////////////////

// * For some prime p, let n! = p^a * k s.t. p doesn't divide k.  We want to find k % p.
// * Example: n! = 1 * 2 * 3 * ... * (p-1) * p * (p+1) * (p+2) * ... * 2p * ... 
//   Then     k  = 1 * 2 * 3 * ... * (p-1) * 1 * 1 * 2 * 3 * ... * (p-1) * 2
// * We can use Wilsons theorem to simplify 1 * 2 * ... * (p-1) to (p-1)
// * Whats left (the powers of p) form a sequence similar to the original, so we can recurse.

ll factmod(ll n, ll p) {
    ll res = 1;
    while (n > 1) {
        res = res * ((n/p) & 1 ? p-1 : 0) % p;
        for (ll i = 2; i <= n % p; i++) res = (res * i) % p;
        n /= p;
    }
    return res;
}


////////////////////////////////////////////////////////////
// SUBSECTION D5: Primitive Root
// https://cp-algorithms.com/algebra/primitive-root.html
////////////////////////////////////////////////////////////

// BACKGROUND:
// * A primitive root modulo n is a generator of the multiplicative group modulo n (when it exists)
// * This means g is a primitive root if, for all a s.t. gcd(a,n) = 1, there is a k with g^k = a (mod n).
// * Gauss showed that primitive roots exist if an only if n in { 1, 2, 4, p^k, 2*p^k} wher p is some ODD prime.
// * A number g is a primitive root iff the smallest k s.t. g^k = 1 (mod n) is phi(n).
// * If n has primitive roots, then there are phi(phi(n)) of them, where phi is the Euler totient function.

// ALGORITHM:
// * Use lagrange theorem in that the order of the subgroup generated by g must divide g.
// * If g^ (phi(n)/p_i) is not 1 for all of the prime divisors p_i of phi(n), then we know that g is a generator.

ll findMultGenerator(ll n) {
    // Handle a few small cases
    if (n < 1)  return -1LL;
    if (n == 1) return 1LL;
    if (n == 2) return 1LL;
    if (n == 3) return 2LL;
    if (n == 4) return 3LL;

    ll phi = totient(n);

    // Factorize phi
    vector<ll> pi;
    ll nn = phi;
    if ((nn & 1) == 0) { pi.push_back(2); while((nn & 1) == 0) nn /= 2; }
    for (ll i = 3; i*i <= nn; i++) {
        if (nn == 1) break;
        if ((nn % i) == 0) { pi.push_back(nn); while((nn & 1) == 0) nn /= i; }
    }
    if (nn > 1) pi.push_back(nn);

    // Test each possible residue
    for (ll res = 2; res <= n-1 ; res++) {
        if (gcd(res,n) > 1) continue;
        bool ok = true;
        for (auto p : pi) {
            if (mpow2(res,phi/p,n) == 1) {ok = false; break; }
        }
        if (ok) return res;
    }
    return -1LL;
}



////////////////////////////////////////////////////////////
// SUBSECTION D6: Discrete Logarithm
// https://cp-algorithms.com/algebra/discrete-log.html
////////////////////////////////////////////////////////////

// * Now consider trying to solve the equations a^x = b (mod m) where gcd(a,m) == 1;
// * The relatively prime assumption isn't strictly necessary, but it simplifies the algorithm below.
// * This can be solved by Shanks Baby step - giant step algorithm

// ALGORITHM DETAILS (a "meet in the middle" sqrt(n) approach)
// * Pick n, and let x = np - q.  Then (because of relatively prime assumption), we have a^(np) = b*a^q (mod m)
// * Step 1: Calculate a^(np) (mod m) for all possible values of p.
// * Step 2: Calculate ba^q for each possible value of q, and see if there is a match

ll discreteLog(ll a, ll b, ll m) {
    if (b == 1) return 0LL;
    ll n = (ll) sqrt((double) m + 0.0) + 1;
    ll an = 1; REP(i,n) an = (an * a) % m;
    unordered_map<ll,ll> vals;
    ll cur = 1;
    FORE(p,1,n) {
        cur = (cur * an) % m;
        if (vals.count(cur) == 0) vals[cur] = p;
    }
    cur = b;
    FORE(q,0,n) {
        if (vals.count(cur) == 0) { return vals[cur] * n - q; }
        cur = (cur * a) % m;
    }
    return -1LL;   
}


////////////////////////////////////////////////////////////
// SUBSECTION D7: Discrete Root
// https://cp-algorithms.com/algebra/discrete-root.html
////////////////////////////////////////////////////////////

// * In this problem, we're given a prime modulus n and two integers: a & k.  We want to find all x such that x^k == a (mod n).
// * Assuming n is an odd prime, it has a primitive root (meaning multiplicative group is cyclic). Thus, we can find g so that g generates the multiplcative group.
// * If we have a primitive root, we can solve discrete log problem to find first root. (i.e. (g^k)^y = a (mod n) )
// * If we have one solution y_0, then note we have x^k = g^(y_0*k) = g^(y_0*k + l * phi(n)).
// * To find all solutions, we have x = g^(y_0 + i * phi(n) / gcd(phi(n),k))

bool discreteRoots(ll a, ll k, ll n, vector<ll> &ans) {
    // Assume n is an odd prime
    assert(n & 1);
    ll g = findMultGenerator(n);
    ll gk = mpow2(g,k,n);
    ll y0 = discreteLog(gk,a,n);
    if (y0 < 0) return false;
    ll baseSol = mpow2(g,y0,n);
    ll delta = (n-1) / gcd(k,n-1);
    ll firstSol = baseSol % delta;
    for (ll lans = firstSol; lans < n; lans += delta) ans.push_back(lans);
    return true;
}



////////////////////////////////////////////////////////////
//
// SECTION E: NUMBER SYSTEMS
//
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// SUBSECTION E1: Balanced Ternary
// https://cp-algorithms.com/algebra/balanced-ternary.html
////////////////////////////////////////////////////////////

// * Can represent a number in a ternary system with digits {-1,0,1}
// * Easy to switch from normal ternary --> balanced ternary by working from right to left
//   * 0 & 1 stay
//   * 2 changes to -1 with a carry to the next bit
//   * 3 changes to  0 with a carry to the next bit (3 happens by a previous carry + 2)
//  * See webpage for more details


////////////////////////////////////////////////////////////
// SUBSECTION E2: Gray Code
// https://cp-algorithms.com/algebra/gray-code.html
////////////////////////////////////////////////////////////

// * Gray codes change one bit at a time.
// * Conversion routines below (based on clever tricks)

ll toGray(ll n)  { return n ^ (n >> 1); }
ll fromGray(ll g) { ll n = 0; for(;g;g>>=1) n ^= g; return g; }

// Applications:
// * Gray code forms a hamiltonian cycle on a hypercube.
// * Gray code are used to facilitate asynchronous crossings in hardware design.
// * Towers of Hanoi


////////////////////////////////////////////////////////////
//
// SECTION F: MISCELLANEOUS
//
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// SUBSECTION F1: Submask Enumeration
// https://cp-algorithms.com/algebra/all-submasks.html
////////////////////////////////////////////////////////////

// * We can use a bit-mask parlor trick to help iterate through all of the bitmasks
void bitMaskIterate(ll m) {
    for (ll s = m; ; s = (s-1) & m) {
        // DO SOMETHING HERE...
        if (s == 0) break;
    }
}

// * Iterating through all (mask,submask) pairs is O(3^n)


////////////////////////////////////////////////////////////
// SUBSECTION F2: Arbitrary-Precision Arithmetic
// https://cp-algorithms.com/algebra/big-integer.html
////////////////////////////////////////////////////////////

// I didn't find anything here I didn't know.
// I've already implemented a bigInt class which seems to encompass many of the ideas here. 



////////////////////////////////////////////////////////////
// SUBSECTION F3: Fast Fourier Transform
// https://cp-algorithms.com/algebra/fft.html
////////////////////////////////////////////////////////////

// DISCRETE FOURIER TRANSFORM
// * Consider the polynomial A(x) = a_0 x^0 + a_1 x^1 + ... + a_(n-1) x^(n-1)
// * WLOG, assume that n is a power of 2 (can be made by padding 0's on the right)
// * DFT of the polynomial is the set of values of the polynomial evaluated at the n complex roots of unity.
// * Also have an inverse DFT to go from the values at the roots of unity back to the coefficients.

// Application: Fast multiplication of polynomials
// * Assume A and B are polynomials each with order n-1.  Then A*B has order 2n-1.  THe coefficients naively take O(n^2) to calculate.
// * However, we can do the following to get an O(nlogn) solution
//   * Pad each polynomial out to 2n coefficients O(n)
//   * Compute the DFT of each polynomial O(nlogn) w/ FFT
//   * Multiply the corresponding evaluation values at the complex roots of unity O(n)
//   * Get back to coefficients with IDFT O(nlogn) w/ IFFT.

// Key idea behind the FFT
// * Start with A(x) = a_0 x^0 + a_1 x^1 + ... + a_(n-1) x^(n-1) with n a power of 2.
// * Create two polynomials each half as long as A
//   A_0(x) = a_0 x^0 + a_2 x^1 + ... + a_(n-2) x^(n/2+1)
//   A_1(x) = a_1 x^0 + a_3 x^1 + ... + a_(n-1) x^(n/2+1)
// * We see that A(x) = A_0(x^2) + x*A_1(x^2)
// * We can do the same thing on the children, so if we can combine the FFTs of the children to make the FFT of the parent in O(n) time, we have an O(nlogn) algo by master theorem.
// * Website shows math of how to combine the FFTs of the children (math is too much of a pain to write out)
// * IFFT is very sim

typedef complex<double>  cd;
const double PI = acos(-1);

// First version of the fft
// Call with invert = true for IFFT.
// Assumes the length of a is a power of 2
// Coefficients are given in a
// Result comes back in a (i.e. a is destroyed)
void fft1(vector<cd> &a, bool invert) {
    ll n = (ll) a.size();
    if (n == 1) return;
    ll childSize = n >> 1;
    vector<cd> a0(childSize), a1(childSize);
    REP(i,childSize) { a0[i] = a[i+i]; a1[i] = a[i+i+1]; }
    fft1(a0,invert); fft1(a1,invert);

    // Stitching code
    double ang = 2 * PI / (double) n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    REP(i,childSize) {
        a[i]           = a0[i] + w * a1[i]; // Butterfly
        a[i+childSize] = a0[i] - w * a1[i]; 
        if (invert) { a[i] /= 2; a[i + childSize] /= 2; }
        w *= wn;
    }
}

// We can optimize by doing this iteratively instead of recursively by dealing with the butterfly tranformations in place.
// We use a little bitmask math ot make this efficient
void fft(vector<cd> &a, bool invert) {
    ll n = (ll) a.size();
    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i],a[j]);
    }

    for (ll len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / (double) len * (invert ? -1 : 1);
        cd wlen(cos(ang),sin(ang));
        for (ll i = 0; i < n; i += len) {
            cd w(1);
            for (ll j = 0; j < len/2; j++) {
                cd u = a[i+j];
                cd v = a[i+j+len/2] * w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }

    // Do the scaling for the ifft
    if (invert) { for (auto &x : a) x /= (double) n; }
}
// Example Application, multiplying two polynomials
vector<ll> multiplyPolyWithFFT(vector<ll> const &a, vector<ll> const &b) {
    vector<cd> fa(a.begin(),a.end());
    vector<cd> fb(b.begin(),b.end());
    ll n = 1;
    while (n < (ll) a.size() + (ll) b.size()) n <<= 1;
    fa.resize(n,0);
    fb.resize(n,0);
    fft(fa,false);
    fft(fb,false);
    REP(i,n) fa[i] *= fb[i];
    fft(fa,true);
    vector<ll> result(n);
    for(ll i = 0; i < n; i++) { result[i] = (ll) round(fa[i].real()); }
    return result;
}

// One thing that is WAY COOL is that we can use the machinery of the FFT in certain purely integer contexts (NTT = Number Theoretic Transformation)
// If we have a large prime p, we can do "mod p" math.  If the prime p is of the form c*2^k + 1, then we can find large power of 2 roots in (mod p).

//1: 3 7 11 19 23 31 43 47 59 67
//2: 5 13 29 37 53 61 101 109 149 157
//3: 41 73 89 137 233 281 313 409 457 521
//4: 17 113 241 337 401 433 593 881 977 1009
//5: 97 353 673 929 1249 1697 1889 2017 2081 2273
//6: 193 449 577 1217 1601 2113 2753 3137 4289 4673
//7: 641 1153 1409 2689 3457 4481 4993 6529 7297 9601
//8: 257 769 3329 7937 9473 14081 14593 22273 23297 26881
//9: 7681 10753 11777 17921 23041 26113 32257 36353 45569 51713
//10: 13313 15361 19457 25601 37889 39937 50177 58369 64513 70657
//11: 18433 59393 79873 83969 120833 133121 202753 301057 329729 366593
//12: 12289 61441 86017 151553 176129 184321 249857 307201 331777 380929
//13: 40961 188417 270337 286721 319489 417793 778241 925697 974849 1073153
//14: 114689 147457 638977 737281 1032193 1097729 1130497 1196033 1589249 1720321
//15: 163841 557057 1146881 2654209 4423681 4620289 4816897 4882433 5865473 6258689
//16: 65537 1376257 1769473 2424833 3604481 3735553 5308417 6750209 7667713 8716289
//17: 1179649 2752513 6684673 6946817 8257537 8519681 12451841 13238273 16121857 16384001
//18: 786433 8650753 10223617 11272193 14942209 16515073 22806529 27000833 33292289 35389441
//19: 5767169 14155777 21495809 29884417 36175873 37224449 40370177 68681729 77070337 83361793
//20: 7340033 13631489 26214401 28311553 70254593 101711873 120586241 141557761 147849217 158334977
//21: 23068673 69206017 81788929 111149057 132120577 136314881 169869313 186646529 199229441 211812353
//22: 104857601 113246209 138412033 155189249 163577857 230686721 415236097 666894337 683671553 918552577
//23: 377487361 595591169 645922817 880803841 897581057 998244353
//24: 754974721
//25: 167772161
//26: 469762049
//27:
//28:
//29:
//30:

// For the larger answers, I calculated a generator, a primitive root, and the inverse of said root

//k    p=c*2^k+1   generator  primroot    rootinv
//20:    7340033          3       2187    4665133
//20:   13631489         15   11799463    6244495
//20:   26214401          3   12954722   16048914
//20:   28311553          5    4493789   13207632
//20:   70254593          3   68840249   49980542
//20:  101711873          3   78093862   87893216
//20:  120586241          3    3687060   64376339
//20:  141557761         13  115404399   23421442
//20:  147849217          5  146588288   21743970
//20:  158334977          3   78827302  105047930
//21:   23068673          3     177147   17187657
//21:   69206017          5   13058274   10025011
//21:   81788929          7   22285958   75577748
//21:  111149057          3   60767546    5744330
//21:  132120577          5  102376994    8853984
//21:  136314881          3    2981173   80071223
//21:  169869313          5  143354861  160581751
//21:  186646529          3   88383805  152793079
//21:  199229441          3  174670364   84134940
//21:  211812353          3  113852926  148895411
//22:  104857601          3   39193363   96987805
//22:  113246209          7   58671006   62639419
//22:  138412033          5   99040867  115638535
//22:  155189249          6   14921912    1592618
//22:  163577857          5  133129875  162456208
//22:  230686721          3  230220481  178280006
//22:  415236097          5   73362476  247718523
//22:  666894337          5  147340140  583564973
//22:  683671553          3  236932120  136292362
//22:  918552577          5   86995699  324602258
//23:  377487361          7   48510621  225915792
//23:  595591169          3  361399025  325748783
//23:  645922817          3  224270701  454025871
//23:  880803841         13   98722167  809745052
//23:  897581057          3  872686320  354917575
//23:  998244353          3   15311432  469870224
//24:  754974721         11  739831874  337633511
//25:  167772161          3        243  114609789
//26:  469762049          3       2187  410692747

// Here a is assumed to be a power of 2 long
void ntt(vector<ll> &a, ll p, ll root, ll rootinv, ll rootpw, bool invert) {
    ll n = (ll) a.size();
    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i],a[j]);
    }

    for (ll len = 2; len <= n; len <<= 1) {
        ll wlen = invert ? rootinv : root;
        for (ll i = len; i < rootpw; i <<= 1) wlen = (wlen * wlen) % p;
        for (ll i = 0; i < n; i += len) {
            ll w = 1;
            for (ll j = 0; j < len/2; j++) {
                ll u = a[i+j];
                ll v = (a[i+j+len/2] * w) % p;
                a[i+j] = u+v < p ? u+v : u+v-p;
                a[i+j+len/2] = u-v >= 0 ? u-v : p+u-v; 
                w = (w * wlen) % p;
            }
        }
    }

    // Do the scaling for the ifft
    if (invert) {
        ll ninv = mpow2(n,p-2,p); 
        for (auto &x : a) x  = (x * ninv) % p;
    }
}

// Useful applications
// * Given 2 arrays a[i] and b[j] and finding all possible sums a[i] + b[j] with counts
// * Finding all possible scalar products of a[] with a cyclical shifted b[] (just convolution)
// * Matching 2 strips.
// * Counting substring matches.
// * Counting substring matches with wildcards.

// See the web page for more details, but these are cool.


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(15);
    //freopen("999A.in1","r",stdin);
    return 0;
}


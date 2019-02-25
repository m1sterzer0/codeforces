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


// bigInt library inspired from
// * https://github.com/ngthanhtrung23/ACM_Notebook_new/blob/master/Math/bigint.h
// * https://github.com/dmkz/competitive-programming/blob/master/e-olymp.com/0317.cpp
// * https://gist.github.com/ar-pa/957297fb3f88996ead11


struct bigInt {
    const int base = 1000000000;
    const int baseDigits = 9;
    vector<int> a;
    int sign;

    ///////////////////////   CONSTRUCTORS /////////////////////////////////

    bigInt() : sign(1) {return;}
    bigInt(ll v) { *this = v; }
    bigInt(const string &s) { read(s); }
  
    ///////////////////////   ASSIGNMET OPERATORS  /////////////////////////////////

    bigInt& operator=(const bigInt &v) { sign = v.sign; a = v.a; return *this; }
    bigInt& operator=(ll v) {
        sign = 1; a.clear();
        if (v < 0) { sign = -1; v = -v; }
        while (v > 0) { a.push_back((int) (v % base)); v /= base; }
        return *this;
    }
  
    ///////////////////////   INPUT/OUTPUT  /////////////////////////////////

    void read(const string& s) {
        sign = 1; a.clear(); int pos = 0;
        while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-') sign = -sign;
            ++pos;
        }
        for (int i = (int) s.size() - 1; i >= pos; i -= baseDigits) {
            int x = 0;
            for (int j = max(pos, i - baseDigits + 1); j <= i; j++) x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }
    friend istream& operator>>(istream &stream, bigInt &v) { string s; stream >> s; v.read(s); return stream; }
    friend ostream& operator<<(ostream &stream, const bigInt &v) {
        if (v.sign == -1 && !v.isZero()) stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        // TODO: FIX THE FORMATTING BETTER
        stream << setw(v.baseDigits) << setfill('0');
        for (int i = (int) v.a.size() - 2; i >= 0; i--) stream << setw(v.baseDigits) << setfill('0') << v.a[i];
        stream << setw(0) << setfill(' ');
        return stream;
    }

    ///////////////////////   COMPARISON  /////////////////////////////////

    friend int __compareAbs(const bigInt& x, const bigInt& y) {
        // Returns: 0 if |x| == |y|, -1 if |x| < |y|, 1 if |x| > |y|
        if (x.a.size() != y.a.size()) { return x.a.size() < y.a.size() ? -1 : 1; }
        for (int i = ((int) x.a.size()) - 1; i >= 0; i--) {
            if (x.a[i] != y.a[i]) return x.a[i] < y.a[i] ? -1 : 1;
        }
        return 0;
    }

    friend bool operator<(const bigInt &x, const bigInt &y) {
        if (x.sign != y.sign) return x.sign < y.sign;
        if (x.a.size() != y.a.size()) return x.a.size() * x.sign < y.a.size() * y.sign;
        for (int i = (int) x.a.size() - 1; i >= 0; i--) { if (x.a[i] != y.a[i]) return x.a[i] * x.sign < y.a[i] * y.sign; }
        return false;
    }

    friend bool operator==(const bigInt &x, const bigInt &y) {
        if (x.sign != y.sign) return false;
        if (x.a.size() != y.a.size()) return false;
        for (int i = (int) x.a.size() - 1; i >= 0; i--) { if (x.a[i] != y.a[i]) return false; }
        return true;
    }

    friend bool operator> (const bigInt &x, const bigInt &y) { return y < x; }
    friend bool operator<=(const bigInt &x, const bigInt &y) { return !(y < x); }
    friend bool operator>=(const bigInt &x, const bigInt &y) { return !(x < y); }
    friend bool operator!=(const bigInt &x, const bigInt &y) { return !(x == y); }

    ///////////////////////   UNARY OPERATORS  /////////////////////////////////

    bigInt operator-() const { 
        bigInt res = *this;
        if (isZero()) return res;
        res.sign = -sign;
        return res;
    }

    ///////////////////////   ADDITION AND SUBTRACTION  ///////////////////////

    // Assumes that the addend as the same sign as us
    void __rawAddToMe(const bigInt &v) {
        assert(sign == v.sign);
        if (v.a.size() > a.size()) a.resize(v.a.size(),0);
        for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; i++) {
            if (i == (int) a.size()) a.push_back(0);
            a[i] += carry + (i < (int) v.a.size() ? v.a[i] : 0);
            if (a[i] >= base) { carry = 1; a[i] -= base; }
            else              { carry = 0; }
        }
    }

    // Assumes that the subtrahend has the same sign as us and does NOT have a larger absolute value
    void __rawSubFromMe(const bigInt &v) {
        assert(sign == v.sign);
        for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; i++) {
            if (i == (int) a.size()) a.push_back(0);
            a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
            if (a[i] < base)  { carry = 1; a[i] += base; }
            else              { carry = 0; }
        }
        this->trim();
    }

    void operator += (const bigInt& v) {
        if (sign == v.sign)                    { __rawAddToMe(v);   }
        else if (__compareAbs(*this, v) >= 0)  { __rawSubFromMe(v); }
        else                                   { bigInt vv = v; swap(a,vv.a); __rawSubFromMe(vv); sign = -sign; }
    }

    void operator -= (const bigInt& v) {
        if (sign != v.sign)                    { __rawAddToMe(v);   }
        else if (__compareAbs(*this, v) >= 0)  { __rawSubFromMe(v); }
        else                                   { bigInt vv = v; swap(a,vv.a); __rawSubFromMe(vv); sign = -sign; }
    }

    friend bigInt operator+ (const bigInt &x, const bigInt &y) { bigInt res(x); res += y; return res; }
    friend bigInt operator- (const bigInt &x, const bigInt &y) { bigInt res(x); res -= y; return res; }

    ///////////////////////   MULTIPLICATION  ///////////////////////

    friend bigInt operator* (const bigInt &a, const bigInt &b) { 
        if (a.isZero() || b.isZero()) { bigInt res; return res; }
        if ((ll) a.a.size() * (ll) b.a.size() < 1000LL) return mulSimple(a,b);
        else                                        return mulKaratsuba(a,b);
    }

    void operator *= (const bigInt& v) { *this = *this * v; }

    static bigInt mulSimple(const bigInt &a, const bigInt &b) { 
        bigInt res;
        res.sign = a.sign * b.sign;
        res.a.assign(a.a.size()+b.a.size(),0);
        for (int i = 0; i < (int) a.a.size(); i++) {
            if(a.a[i]) {
                for (int j = 0; j < (int) b.a.size(); j++) {
                    int idx = i+j; int idxp1 = idx+1;
                    ll cur = (ll) res.a[idx] + (ll) a.a[i] * (ll) b.a[j];
                    res.a[idx]    = (int) (cur % a.base);
                    res.a[idxp1] += (int) (cur / a.base);
                }
            }
        }
        res.trim();
        return res;
    }

    static bigInt mulKaratsuba(bigInt x, bigInt y) {
        if (x.a.size() < y.a.size()) x.a.resize(y.a.size(),0);
        if (y.a.size() < x.a.size()) y.a.resize(x.a.size(),0);
        int m = ((int) x.a.size()) >> 1;
        bigInt x0, x1, y0, y1;
        x0.a.assign(x.a.begin(),x.a.begin()+m);
        x1.a.assign(x.a.begin()+m,x.a.end());
        y0.a.assign(y.a.begin(),y.a.begin()+m);
        y1.a.assign(y.a.begin()+m,y.a.end());
        x0.trim(); x1.trim(); y0.trim(); y1.trim();
        bigInt z2 = x1 * y1;
        bigInt z0 = x0 * y0;
        bigInt z1 = (x1 + x0) * (y1 + y0) - z2 - z0;
        bigInt res;
        res.sign = x.sign * y.sign;
        res.a.assign(2*x.a.size(),0);
        for (int i = 0; i < (int) z0.a.size(); i++) { res.a[i]      = z0.a[i]; }
        for (int i = 0; i < (int) z1.a.size(); i++) { res.a[i+m]   += z1.a[i]; }
        for (int i = 0; i < (int) z2.a.size(); i++) { res.a[i+m+m] += z2.a[i]; }
        for (int i = 0; i < (int) res.a.size()-1; i++) { while (res.a[i] > res.base) { res.a[i] -= res.base; res.a[i+1]++; } }
        res.trim();
        return res;
    }

    void operator *= (int v) {
        if (llabs(v) > base) { *this *= bigInt(v); return; }
        if (v < 0) { sign = -sign; v = -v; }
        a.push_back(0);
        for (int j = 0, carry = 0; j < (int) a.size(); j++) {
            ll cur = (ll) a[j] * (ll) v + (ll) carry;
            a[j] = (int) (cur % base);
            carry = (int) (cur / base);
        }
        trim();
    }

    friend bigInt operator* (const bigInt &a, int b) {
        if (llabs(b) > a.base) { return a * bigInt(b); }
        bigInt res(a);
        res *= b;
        return res;
    }

    friend bigInt operator* (int b, const bigInt &a) {
        if (llabs(b) > a.base) { return a * bigInt(b); }
        bigInt res(a);
        res *= b;
        return res;
    }

    ///////////////////////   DIVISION  ///////////////////////

    friend pair<bigInt, bigInt> divmod(const bigInt& a1, const bigInt& b1) {
        assert (!b1.isZero());
        assert (b1.sign == 1);
        int norm = a1.base / (b1.a.back() + 1);
        bigInt a = a1.abs() * norm;
        bigInt b = b1.abs() * norm;
        bigInt q = 0, r = 0;
        q.a.resize(a.a.size());
        for (int i = (int) a.a.size() - 1; i >= 0; i--) {
            r *= a.base;
            r += a.a[i];
            long long s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            long long s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            long long d = ((long long) a.base * s1 + s2) / b.a.back();
            r -= b * (int) d;
            while (r < 0) { r += b, d--; }
            q.a[i] = (int) d;
        }
        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        auto res = make_pair(q, r / norm);
        if (res.second < 0) res.second += b1;
        return res;
    }

    friend bigInt operator/(const bigInt &a, const bigInt &b) { return divmod(a,b).first; }
    friend bigInt operator%(const bigInt &a, const bigInt &b) { return divmod(a,b).second; }
    void operator/=(const bigInt &a) { *this = *this / a; }
    void operator%=(const bigInt &a) { *this = *this % a; }

    void operator /= (int v) {
        assert(v>0);
        if (llabs(v) >= base) { *this = *this / bigInt(v); return; }
        if (v < 0) { sign = -sign; v = -v; }
        for (int i = (int) a.size() - 1, rem = 0; i >= 0; i--) {
            ll cur = (ll) a[i] + (ll) rem * (ll) base;
            a[i] = (int) (cur / v);
            rem = (int) (cur % v);
        }
        trim();
    }

    friend bigInt operator/ (const bigInt &a, int b) {
        if (llabs(b) > a.base) { return a / bigInt(b); }
        bigInt res(a);
        res /= b;
        return res;
    }

    friend int operator%(const bigInt &a, int v) {
        assert(v > 0);
        assert(v < a.base);
        int m = 0;
        for (int i = (int) a.a.size() - 1; i >= 0; i--) {
            ll x = ((ll) m * (ll) a.base) % v;
            m = ((int) x + a.a[i]) % v;
        }
        return m * a.sign;
    }

    ///////////////////////   MISC  ///////////////////////
    bigInt abs() const { bigInt res = *this; res.sign = 1; return res; }
    bool isZero() const { return a.empty() || (a.size() == 1 && a[0] == 0); }
    void trim()  { while (!a.empty() && !a.back()) { a.pop_back(); } if (a.empty()) sign = 1; }
    friend bigInt gcd(const bigInt &a, const bigInt &b) { return b.isZero() ? a : gcd(b, a % b); }
    friend bigInt lcm(const bigInt &a, const bigInt &b) { return a / gcd(a,b) * b; }

};


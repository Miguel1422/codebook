//Importante el unsigned sino TLE (ull = unsigned long long)
// (a*b)%c
ull mulmod(ull a, ull b, ull c) {
    a %= c;
    b %= c;
    unsigned long long x = 0, y = a, t;
    while (b) {
        if (b & 1) {
            t = x + y;
            x = (t > c) ? t - c : t;
        }
        t = y << 1;
        y = (t > c) ? t - c : t;
        b >>= 1;
    }
    return x;
}
long long gcd(long long a, long long b) {
    return !b ? a : gcd(b, a % b);
}
// (x^n)%mod
long long powmod(long long x, long long n, long long mod) {
    long long ret = 1;
    while (n) {
        if (n & 1) ret = mulmod(ret, x, mod);
        x = mulmod(x, x, mod);
        n >>= 1;
    }
    return ret;
}
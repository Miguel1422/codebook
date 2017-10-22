long long pollard_rho(long long n) { // O(n^(1/4))
    int i = 0, k = 2;
    long long x = 3, y = 3;
    if (isPrime(n)) return n;
    while (1) {
        i++;
        x = (mulmod(x, x, n) + n - 1) % n;
        long long d = gcd(abs(y - x), n);
        if (d != 1 && d != n) return d;
        if (i == k) y = x, k *= 2;
    }
}
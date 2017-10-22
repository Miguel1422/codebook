int isPrime(long long p) { // implements by miller-babin
    if (p < 2 || !(p & 1)) return 0; // probof failure 1/4^it
    if (p == 2) return 1;
    long long q = p - 1, a, t;
    int k = 0, b = 0;
    while (!(q & 1)) q >>= 1, k++;
    for (int it = 0; it < 15; it++) { // Number of iterations
        a = rand() % (p - 4) + 2;
        t = powmod(a, q, p);
        b = (t == 1) || (t == p - 1);
        for (int i = 1; i < k && !b; i++) {
            t = mulmod(t, t, p);
            if (t == p - 1) b = 1;
        }
        if (b == 0)
            return 0;
    }
    return 1;
}
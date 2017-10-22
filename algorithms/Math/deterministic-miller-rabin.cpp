bool isPrime(long long n) { // Overall Time Complexity is (logN)^3
    if (n < 2) return false; // Will work < 3*10**18
    long long d = n - 1;
    int s = 0;
    while (d % 2 == 0)s++, d >>= 1;
    int a[9] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    for (int i = 0; i < 9; i++) if (n == a[i]) return true;
    for (int i = 0; i < 9; i++) {
        bool comp = powmod(a[i], d, n) != 1;
        if (comp)
            for (int j = 0; j < s; j++) {
                long long fp = powmod(a[i], (1LL << (long long) j) * d, n);
                if (fp == n - 1) {
                    comp = false;
                    break;
                }
            }
        if (comp) return false;
    }
    return true;
}
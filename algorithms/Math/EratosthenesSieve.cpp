// O(n)
vector<int> prime;
int lp[MAXN];
bool is_composite[MAXN];
void sieve(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!is_composite[i])
            prime.push_back(i), lp[i] = i;
        for (int j = 0; j < (int) prime.size() && i * prime[j] <= n 
          && prime[j] <= lp[i]; ++j) {
            is_composite[i * prime[j]] = true;
            lp[i * prime[j]] = prime[j];
            if (i % prime[j] == 0) break;
        }
    }
}
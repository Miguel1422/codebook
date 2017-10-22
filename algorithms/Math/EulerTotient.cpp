// O(nlogn)
int phi[n + 5];
for (int i = 1; i <= n; ++i) {
    phi[i] += i;
    for (int j = 2 * i; j <= n; j += i) {
        phi[j] -= phi[i];
    }
}

// O(sqrt(n))
int phi(int n) {
    int result = n;
    for (int p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// This code took less than 0.5s to calculate with MAX = 10^7
#define MAX 10000000

int phi[MAX];
bool pr[MAX];

void totient(){
  for(int i = 0; i < MAX; i++){
    phi[i] = i;
    pr[i] = true;
  }
  for(int i = 2; i < MAX; i++)
    if(pr[i]){
      for(int j = i; j < MAX; j+=i){
        pr[j] = false;
        phi[j] = phi[j] - (phi[j] / i);
      }
      pr[i] = true;
    }
}

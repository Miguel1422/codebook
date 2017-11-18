const int N = 1 << 21;
const int LOG = 22;

int sparse[N][LOG];
int arr[N], n;

inline int pow2(int p) {
    return 1 << p;
}

void preprocess(int *a, int n) {
    for (int i = 0; i < n; i++) {sparse[i][0] = i;}
    
    for (int j = 1; pow2(j) <= n; j++) {
        for (int i = 0; i + pow2(j) - 1 < n; i++) {
            if (arr[sparse[i][j - 1]] < arr[sparse[i + pow2(j - 1)][j - 1]]) { // Minumum from i to 2^j
                sparse[i][j] = sparse[i][j - 1];
            } else {
                sparse[i][j] = sparse[i + pow2(j - 1)][j - 1];
            }
        }
    }
}

int query(int a, int b) {
    int k = (int) (log2(b - a + 1));
    return min(arr[sparse[a][k]], arr[sparse[b - pow2(k) + 1][k]]);
}


int main() {
    n = 5000, a, b;
    for (int i = 0; i < n; i++)cin >>arr[i];
    preprocess(arr, n);
    int q; cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> a >> b;
        if (a > b) swap(a, b);
        cout << query(a, b) << endl;
    }
    return 0;
}
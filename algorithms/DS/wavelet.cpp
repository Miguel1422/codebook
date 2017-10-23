struct wavelet_tree {
    int lo, hi;
    wavelet_tree *l = nullptr;
    wavelet_tree *r = nullptr;
    vector<int> b;
    vector<int> c; // c holds the prefix sum of elements

    //numbers are in range [x,y]
    //array indices are [from, to)
    wavelet_tree(int *from, int *to, int x, int y) {
        lo = x, hi = y;
        if (from >= to) return;
        if (hi == lo) {
            b.reserve(to - from + 1);
            b.push_back(0);
            c.reserve(to - from + 1);
            c.push_back(0);
            for (auto it = from; it != to; it++) {
                b.push_back(b.back() + 1);
                c.push_back(c.back() + *it);
            }
            return;
        }
        int mid = (lo + hi) / 2;
        auto f = [mid](int x) {
            return x <= mid;
        };
        b.reserve(to - from + 1);
        b.push_back(0);
        c.reserve(to - from + 1);
        c.push_back(0);
        for (auto it = from; it != to; it++) {
            b.push_back(b.back() + f(*it));
            c.push_back(c.back() + *it);
        }
        //see how lambda function is used here
        auto pivot = stable_partition(from, to, f);
        l = new wavelet_tree(from, pivot, lo, mid);
        r = new wavelet_tree(pivot, to, mid + 1, hi);
    }

    //kth smallest element in [l, r] 1-indexed
    int kth(int l, int r, int k) {
        if (l > r) return 0;
        if (lo == hi) return lo;
        int inLeft = b[r] - b[l - 1];
        int lb = b[l - 1]; //amt of nos in first (l-1) nos that go in left
        int rb = b[r]; //amt of nos in first (r) nos that go in left
        if (k <= inLeft) return this->l->kth(lb + 1, rb, k);
        return this->r->kth(l - lb, r - rb, k - inLeft);
    }

    //count of nos in [l, r] Less than or equal to k
    int LTE(int l, int r, int k) {
        if (l > r or k < lo) return 0;
        if (hi <= k) return r - l + 1;
        int lb = b[l - 1], rb = b[r];
        return this->l->LTE(lb + 1, rb, k) + this->r->LTE(l - lb, r - rb, k);
    }

    //count of nos in [l, r] equal to k
    int count(int l, int r, int k) {
        if (l > r or k < lo or k > hi) return 0;
        if (lo == hi) return r - l + 1;
        int lb = b[l - 1], rb = b[r], mid = (lo + hi) / 2;
        if (k <= mid) return this->l->count(lb + 1, rb, k);
        return this->r->count(l - lb, r - rb, k);
    }

    //sum of nos in [l ,r] less than or equal to k
    int sumk(int l, int r, int k) {
        if (l > r or k < lo) return 0;
        if (hi <= k) return c[r] - c[l - 1];
        int lb = b[l - 1], rb = b[r];
        return this->l->sumk(lb + 1, rb, k) + this->r->sumk(l - lb, r - rb, k);
    }

    ~wavelet_tree() { // Destructor
        delete l;
        delete r;
    }
};
int a[N];
int main() {
    int n, k, j, q, l, r;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i + 1];
    wavelet_tree T(a + 1, a + n + 1, 1, MAX);
    //Kth Smallest
    cout << T.kth(l, r, k) << endl;
    //less than or equal to K
    cout << T.LTE(l, r, k) << endl;
    //count occurence of K in [l, r]
    cout << T.count(l, r, k) << endl;
    //sum of elements less than or equal to K in [l, r]
    cout << T.sumk(l, r, k) << endl;
    return 0;
}
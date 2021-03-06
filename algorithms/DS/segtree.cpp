#define LEFT(n) (n*2 + 1)
#define RIGHT(n) (n*2 + 2)
const int N = 1e5; // Max number
int n = 100; // Number of elements

typedef struct node {
    int mmax;
    int mmin;
    node() : mmax(-2e9), mmin(2e9) {}
    node(int mmax, int mmin) : mmax(mmax), mmin(mmin) {}
} Node;

node merge(const node &a, const node &b) {
    int mmax = max(a.mmax, b.mmax);
    int mmin = min(a.mmin, b.mmin);
    return node(mmax, mmin);
}

Node tree[N * 4];
int numbers[N];

void build(int index = 0, int f = 0, int t = n - 1) {
    if (f == t) {
        tree[index] = Node(numbers[f], numbers[f]);
        return;
    }
    int mid = (f + t) / 2;
    build(LEFT(index), f, mid);
    build(RIGHT(index), mid + 1, t);
    tree[index] = merge(tree[LEFT(index)], tree[RIGHT(index)]);
}

Node query(int l, int r, int index = 0, int f = 0, int t = n - 1) {
    if (l > t || r < f) return Node();
    if (f >= l && t <= r) {
        return tree[index];
    }
    int mid = (f + t) / 2;
    Node lef = query(l, r, LEFT(index), f, mid);
    Node ri = query(l, r, RIGHT(index), mid + 1, t);
    return merge(lef, ri);
}

void update(int ind, int val, int index = 0, int f = 0, int t = n - 1) {
    if(f > ind || t < ind) return;
    if (f == t) {
        tree[index] = Node(val, val);
        return;
    }
    int mid = (f + t) / 2;
    update(ind, val, LEFT(index), f, mid);
    update(ind, val, RIGHT(index), mid + 1, t);
    tree[index] = merge(tree[LEFT(index)], tree[RIGHT(index)]);
}
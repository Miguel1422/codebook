#include <bits/stdc++.h>
using namespace std;
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
int lazy[N * 4];
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


void push(int node, bool leaf) {
    if(lazy[node] != 0) {
        tree[node].mmin += lazy[node];
        tree[node].mmax += lazy[node];
        if(!leaf) {
            lazy[LEFT(node)]  += lazy[node];
            lazy[RIGHT(node)] += lazy[node];
        }
    }
    lazy[node] = 0;
}

Node query(int l, int r, int index = 0, int f = 0, int t = n - 1) {
    push(index, f == t);
    if (l > t || r < f) return Node();
    if (f >= l && t <= r) {
        return tree[index];
    }
    int mid = (f + t) / 2;
    Node lef = query(l, r, LEFT(index), f, mid);
    Node ri = query(l, r, RIGHT(index), mid + 1, t);
    return merge(lef, ri);
}

void updateRange(int l, int r, int val, int index = 0, int f = 0, int t = n - 1) {
    push(index, f == t);
    if (l > t || r < f) return;
    if (f >= l && t <= r) {
        lazy[index] = val;
        push(index, f == t);
        return;
    }
    int mid = (f + t) / 2;
    updateRange(l, r, val, LEFT(index), f, mid);
    updateRange(l, r, val, RIGHT(index), mid + 1, t);
    tree[index] = merge(tree[LEFT(index)], tree[RIGHT(index)]);
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

int main() {
    n = 10;
    for(int i = 0; i < n; i++) {
        numbers[i] = rand() % 10;
        cout << numbers[i] << " ";
    }
    build();
    cout << endl;
    int l, r, val;
    while(true) {
        char op;
        cin >> op;
        if(op == 'u') {
            cin >> l >> r >> val;
            updateRange(l, r, val);
        } else {
            cin >> l >> r;
            cout << query(l, r).mmax << " " << query(l, r).mmin << endl;
        }
    }
    return 0;
}
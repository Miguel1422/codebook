int R, C; // Rows Columns
int t[205][205];

void add(int r, int c, int value) {
    for (int i = r; i < R; i |= i + 1) {
        for (int j = c; j < C; j |= j + 1) {
            t[i][j] += value;
        }
    }
}
// sum[(0, 0), (r, c)]
int sum(int r, int c) {
    int res = 0;
    for (int i = r; i >= 0; i = (i & (i + 1)) - 1) {
        for (int j = c; j >= 0; j = (j & (j + 1)) - 1) {
            res += t[i][j];
        }
    }
    return res;
}

// sum[(r1, c1), (r2, c2)]
int sum(int r1, int c1, int r2, int c2) {
    return sum(r2, c2) - sum(r1 - 1, c2) - sum(r2, c1 - 1) + sum(r1 - 1, c1 - 1);
}

int get(int r, int c) {
    return sum(r, c, r, c);
}

void set(int r, int c, int value) {
    add(r, c, -get(r, c) + value);
}
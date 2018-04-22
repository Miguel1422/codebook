vector<int> tree[MAXN];
int depth[MAXN];
int parent[MAXN][level]; // level = log2(MAXN) + 1
int sparse[MAXN][level]; // store something else, example heaviest edge from n to 2^i parent

// pre-compute the depth for each node and their
// first parent(2^0th parent)
void dfs(int cur, int prev) {
    depth[cur] = depth[prev] + 1;
	sparse[cur][0] = cost[cur -> parent(same as prev)];
    parent[cur][0] = prev;
    for (int i = 0; i < tree[cur].size(); i++) {
        if (tree[cur][i] != prev) dfs(tree[cur][i], cur);
    }
}

// Dynamic Programming Sparse Matrix Approach
// populating 2^i parent for each node
void precomputeSparseMatrix(int n) {
    for (int i = 1; i < level; i++) {
        for (int node = 1; node <= n; node++) {
            if (parent[node][i - 1] != -1) {
				parent[node][i] = parent[parent[node][i - 1]][i - 1];
				int a = sparse[node][i - 1];
                int b = sparse[parent[node][i - 1]][i - 1];
                sparse[node][i] = max(a, b); // heaviest to 2^i parent
			}
        }
    }
}

// Returning the LCA of u and v
int lca(int u, int v) {
    if (depth[v] < depth[u])
        swap(u, v);
	int heaviest = 0;
    int diff = depth[v] - depth[u];
    for (int i = 0; i < level; i++)
        if ((diff >> i) & 1) {
            v = parent[v][i];
			heaviest = max(heaviest, sparse[v][i]);
		}

    // now depth[u] == depth[v]
    if (u == v) return u; // heaviest;
    for (int i = level - 1; i >= 0; i--)
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
			heaviest = max(heaviest, sparse[u][i]);
            heaviest = max(heaviest, sparse[v][i]);
        }
	// heaviest = max(heaviest, sparse[u][0], sparse[u][0]) if u or v != -1
    return parent[u][0];
}

void addEdge(int u, int v) {
    tree[u].push_back(v); tree[v].push_back(u);
}

int main() {
    memset(parent, -1, sizeof(parent));
    int n = Vertices;
    // addEdges
    depth[0] = 0; dfs(1, 0);
    precomputeSparseMatrix(n);
    cout << "LCA(4, 7) = " << lca(4, 7) << endl;
}
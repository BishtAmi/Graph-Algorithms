const int N = 100000;
int n;
int tree[2 * N];
void build(int arr[])
{
    for (int i = 0; i < n; i++)
        tree[n + i] = arr[i];
    for (int i = n - 1; i > 0; --i)
        tree[i] = tree[i << 1] + tree[i << 1 | 1];
}
void updateTreeNode(int p, int value)
{
    tree[p + n] = value;
    p = p + n;
    for (int i = p; i > 1; i >>= 1)
        tree[i >> 1] = tree[i] + tree[i ^ 1];
}
int query(int l, int r)
{
    int res = 0;
    // sum query
    for (l += n, r += n; l < r; l >>= 1, r >>= 1)
    {
        if (l & 1)
            res += tree[l++];
        if (r & 1)
            res += tree[--r];
    }
    return res;
}
// array update at position k by x
void update(int k, int x)
{
    k += n;
    tree[k] = x;
    for (int i = k / 2; i >= 1; i / 2)
    {
        tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
}
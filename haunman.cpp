// C++ Program to implement
// the above approach
#include <bits/stdc++.h>
using namespace std;

#define maxN 100001

// Adjacency List to store the graph
vector<int> adj[maxN];

// Stores the height of each node
int height[maxN];

// Stores the maximum distance of a
// node from its ancestors
int dist[maxN];

// Function to add edge between
// two vertices
void addEdge(int u, int v)
{
    // Insert edge from u to v
    adj[u].push_back(v);

    // Insert edge from v to u
    adj[v].push_back(u);
}

// Function to calculate height of
// each Node
void dfs1(int cur, int par)
{
    // Iterate in the adjacency
    // list of the current node
    for (auto u : adj[cur])
    {

        if (u != par)
        {

            // Dfs for child node
            dfs1(u, cur);

            // Calculate height of nodes
            height[cur] = max(height[cur], height[u]);
        }
    }

    // Increase height
    height[cur] += 1;
}

// Function to calculate the maximum
// distance of a node from its ancestor
void dfs2(int cur, int par)
{
    int max1 = 0;
    int max2 = 0;

    // Iterate in the adjacency
    // list of the current node
    for (auto u : adj[cur])
    {

        if (u != par)
        {

            // Find two children
            // with maximum heights
            if (height[u] >= max1)
            {
                max2 = max1;
                max1 = height[u];
            }
            else if (height[u] > max2)
            {
                max2 = height[u];
            }
        }
    }

    int sum = 0;

    for (auto u : adj[cur])
    {
        if (u != par)
        {

            // Calculate the maximum distance
            // with ancestor for every node
            sum = ((max1 == height[u]) ? max2 : max1);

            if (max1 == height[u])
                dist[u] = 1 + max(1 + max2, dist[cur]);
            else
                dist[u] = 1 + max(1 + max1, dist[cur]);

            // Calculating for children
            dfs2(u, cur);
        }
    }
}

// Driver Code
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        addEdge(u, v);
    }
    // addEdge(1, 2);
    // addEdge(1, 3);
    // addEdge(2, 4);
    // addEdge(2, 5);
    // addEdge(3, 6);

    // Calculate height of
    // nodes of the tree
    dfs1(1, 0);

    // Calculate the maximum
    // distance with ancestors
    dfs2(1, 0);

    // Print the maximum of the two
    // distances from each node
    vector<int> ecc(n + 1);
    for (int i = 1; i <= n; i++)
        ecc[i] = (max(dist[i], height[i]) - 1);
    sort(ecc.begin(), ecc.end());
    for (int i = 1; i <= n; i++)
    {
        // int curr = i;
        int pos = lower_bound(ecc.begin(), ecc.end(), i) - ecc.begin();
        // if(pos!=n)
        // pos++;
        if (pos > n)
            pos = n;
        cout << pos << " ";
    }

    return 0;
}

/*
 *   author: Momen Medhat 20221258
 */

#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

// Function to calculate GCD
long long gcd(long long a, long long b)
{
    return a == 0 ? b : gcd(b % a, a);
}

// Maximum number of nodes
const int N = 50005;
// Number of nodes and edges
int n, m;
// Gold and silver costs
int G, S;
long long Minimum_cost;

// Struct to represent an edge
struct Edge
{

    int from, to;
    long long goldAmount, SilverAmount;
};

int edgeCounter;
// Arrays for edges and temporary MST edges
Edge edges[N], temporaryEdges[N];
// Parent array for Union-Find
int parent[N];

// Function to find the root of a node in Union-Find
int findRoot(int x)
{
    if (x == parent[x])
    {
        return x;
    }
    return parent[x] = findRoot(parent[x]);
}

// Initialize Union-Find
void UnionFind()
{
    for (int i = 1; i <= n; ++i)
    {
        parent[i] = i;
    }
}

// Comparator for sorting edges
bool comparison_func(const Edge &a, const Edge &b)
{
    if (a.goldAmount != b.goldAmount)
    {
        // Sort by gold cost
        return a.goldAmount < b.goldAmount;
    }
    else
    {
        // If gold is equal, sort by silver cost
        return a.SilverAmount < b.SilverAmount;
    }
}

// Kruskal_algo's algorithm for Minimum Spanning Tree
void kruskal_algo()
{
    edgeCounter = 0;
    // Initialize Minimum_cost to large value
    Minimum_cost = LLONG_MAX;

    for (int i = 0; i < m; ++i)
    {
        // Initialize Union-Find for each iteration
        UnionFind();

        // Add current edge to temp array
        temporaryEdges[edgeCounter++] = edges[i];

        // Maximum silver cost in current MST
        long long maximumSilverAmount = -LLONG_MAX;

        // Sort temp edges by silver cost
        for (int j = edgeCounter - 1; j >= 1; --j)
        {
            if (temporaryEdges[j].SilverAmount < temporaryEdges[j - 1].SilverAmount)
            {
                swap(temporaryEdges[j], temporaryEdges[j - 1]);
            }
        }
        // Number of connected edges in MST
        int connected = 0;

        // Construct MST
        for (int j = 0; j < edgeCounter; ++j)
        {
            int u = findRoot(temporaryEdges[j].from);
            int v = findRoot(temporaryEdges[j].to);

            if (u != v)
            {
                // Update max silver cost
                maximumSilverAmount = max(maximumSilverAmount, temporaryEdges[j].SilverAmount);
                // Keep edge in MST
                temporaryEdges[connected++] = temporaryEdges[j];

                parent[u] = v;
            }
            // Stop if MST is complete
            if (connected == n - 1)
                break;
        }

        // Check if valid MST
        if (connected == n - 1)
        {
            Minimum_cost = min(Minimum_cost, edges[i].goldAmount * G + maximumSilverAmount * S); // Update minimum cost
        }
        // Update temp edge count
        edgeCounter = connected;
    }
}

int main()
{
    // Input number of nodes, edges, and costs
    cin >> n >> m;
    cin >> G >> S;

    // Input edges
    for (int i = 0; i < m; ++i)
    {
        cin >> edges[i].from >> edges[i].to >> edges[i].goldAmount >> edges[i].SilverAmount;
    }

    // Sort edges by gold cost
    sort(edges, edges + m, comparison_func);

    // Run Kruskal_algo's algorithm
    kruskal_algo();

    // Output result
    if (Minimum_cost == LLONG_MAX)
    {
        cout << "-1" << endl;
    }
    else
    {
        cout << Minimum_cost << endl;
    }

    return 0;
}

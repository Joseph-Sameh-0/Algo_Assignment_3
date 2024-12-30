#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

bool validPath(int n, vector<vector<int>>& edges, int source, int destination)
{
    // Create an adjacency list
    vector<vector<int>> graph(n);
    for (const auto& edge : edges)
    {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }

    // BFS initialization
    queue<int> q;
    vector<bool> visited(n, false);
    q.push(source);
    visited[source] = true;

    // BFS loop
    while (!q.empty())
    {
        int current = q.front();
        q.pop();

        // Check if we reached the destination
        if (current == destination)
        {
            return true;
        }

        // Visit all the neighbors
        for (int neighbor : graph[current])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return false; // No path found
}

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    // Remove '[' , ']' and ',' from the input string
    string r;
    for (char c : s)
    {
        if (c != '[' && c != ']' && c != ',')
        {
            r += c;
        }
    }

    // Build the edges from the processed string
    vector<vector<int>> edges;
    for (int i = 0; i < r.size(); i += 2)
    {
        int u = r[i] - '0';     // Convert char to int
        int v = r[i + 1] - '0'; // Convert char to int
        edges.push_back({u, v});
    }

    int source, destination;
    cin >> source >> destination;

    // Check if there is a valid path
    bool result = validPath(n, edges, source, destination);
    cout << (result ? "true" : "false") << endl;

    return 0;
}

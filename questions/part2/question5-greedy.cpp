/*
 * author: 	Joseph Sameh 20220099
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_CITIES = 100000;

vector<int> citySets[MAX_CITIES]; // List of sets
int cityParent[MAX_CITIES];       // Parent array for union-find

// Union-find function to merge sets
void unionCities(int cityA, int cityB)
{
    cityA = cityParent[cityA];
    cityB = cityParent[cityB];
    if (cityA != cityB)
    {
        if (citySets[cityA].size() < citySets[cityB].size())
        {
            swap(cityA, cityB);
        }
        while (!citySets[cityB].empty())
        {
            int city = citySets[cityB].back();
            citySets[cityB].pop_back();
            cityParent[city] = cityA;
            citySets[cityA].push_back(city);
        }
    }
}

vector<vector<pair<int, int>>> cityNeighbors;
vector<int> edgeCounts(200100, 0);
vector<int> visitedCities;
int totalCities, totalEdges;

// Depth-first search function
int dfs(int currentCity)
{
    visitedCities[currentCity] = 1;
    int subtreeSize = 1;
    for (auto neighbor : cityNeighbors[currentCity])
    {
        if (visitedCities[neighbor.first])
        {
            continue;
        }

        long long subtree = dfs(neighbor.first);
        subtreeSize += subtree;

        long long possibleWays = subtree * (totalCities - subtree);
        int currentEdge = neighbor.second;
        while (possibleWays > 0)
        {
            if (possibleWays % 2)
            {
                edgeCounts[currentEdge]++;
            }
            possibleWays /= 2;
            if (edgeCounts[currentEdge] == 2)
            {
                edgeCounts[currentEdge] = 0;
                possibleWays++;
            }
            currentEdge++;
        }
    }
    return subtreeSize;
}

string calculateRoads(int numCities, vector<vector<int>> roads)
{
    vector<pair<int, pair<int, int>>> edges;

    // Initialize number of cities and edges
    totalCities = numCities;
    totalEdges = roads.size();

    // Read edges
    for (int i = 0; i < totalEdges; i++)
    {
        int cityA = roads[i][0] - 1;
        int cityB = roads[i][1] - 1;
        int weight = roads[i][2];
        edges.push_back(make_pair(weight, make_pair(cityA, cityB)));
    }

    cityNeighbors.resize(totalCities);
    for (int i = 0; i < totalCities; i++)
    {
        citySets[i] = vector<int>(1, i);
        cityParent[i] = i;
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end());

    // Process edges using union-find
    for (auto edge : edges)
    {
        int cityA = edge.second.first;
        int cityB = edge.second.second;
        int rootA = cityParent[cityA];
        int rootB = cityParent[cityB];
        if (rootA == rootB)
        {
            continue;
        }
        int weight = edge.first;
        cityNeighbors[cityA].push_back(make_pair(cityB, weight));
        cityNeighbors[cityB].push_back(make_pair(cityA, weight));
        unionCities(cityA, cityB);
    }

    visitedCities = vector<int>(totalCities, 0);
    dfs(0);

    // Remove trailing zeros from the result
    while (edgeCounts.back() == 0)
    {
        edgeCounts.pop_back();
    }

    // Convert result to string
    string resultStr;
    for (auto it = edgeCounts.rbegin(); it != edgeCounts.rend(); it++)
    {
        resultStr += to_string(*it);
    }

    return resultStr;
}

int main()
{
    int numCities, numEdges;
    cin >> numCities >> numEdges;
    vector<vector<int>> roads(numEdges, vector<int>(3));

    for (int i = 0; i < numEdges; i++)
    {
        cin >> roads[i][0] >> roads[i][1] >> roads[i][2];
    }

    // Call the function and print the result
    string result = calculateRoads(numCities, roads);
    cout << result << endl;

    return 0;
}

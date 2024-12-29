#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;
typedef pair<long long, int> pli;

const long long Infinity = LLONG_MAX;

vector<vector<pli>> graph; // Adjacency list

vector<long long> dijkstra(int source, int N) {
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    vector<long long> dist(N + 1, Infinity);

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (auto &[v, weight] : graph[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int N, M;
    cin >> N >> M;

    // Initialize graph
    graph.assign(N + 1, vector<pli>());

    // Input edges
    for (int i = 0; i < M; ++i) {
        int A, B, C;
        cin >> A >> B >> C;
        long long weight = pow(2, C);
        graph[A].emplace_back(B, weight);
        graph[B].emplace_back(A, weight); // Bidirectional
    }

    // Compute sum of all-pairs shortest paths
    long long total_sum = 0;

    for (int i = 1; i <= N; ++i) {
        vector<long long> dist = dijkstra(i, N);
        for (int j = i + 1; j <= N; ++j) { // Avoid double-counting
            if (dist[j] != Infinity) {
                total_sum += dist[j];
            }
        }
    }

    // Convert total sum to binary representation
    string binaryResult = "";
    if (total_sum == 0) {
        binaryResult = "0";
    } else {
        while (total_sum > 0) {
            binaryResult = (total_sum % 2 == 0 ? "0" : "1") + binaryResult;
            total_sum /= 2;
        }
    }

    // Output the result
    cout << binaryResult << endl;

    return 0;
}

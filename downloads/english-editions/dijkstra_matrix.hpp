#pragma once
#include <limits>
#include <stdexcept>
#include <vector>

namespace matrix_paths {
using Distance = long long;
constexpr Distance INF = std::numeric_limits<Distance>::max() / 4;
using Matrix = std::vector<std::vector<Distance>>;

// INF means no edge. Finite weights and path costs must be below INF.
inline std::vector<Distance> dijkstra(const Matrix& cost, int source) {
    const int n = static_cast<int>(cost.size());
    if (source < 0 || source >= n)
        throw std::invalid_argument("invalid source");
    for (const auto& row : cost) {
        if (static_cast<int>(row.size()) != n)
            throw std::invalid_argument("matrix must be square");
        for (auto weight : row)
            if (weight < 0 || weight > INF)
                throw std::invalid_argument("invalid nonnegative edge weight");
    }
    std::vector<Distance> distance(n, INF);
    std::vector<bool> visited(n, false);
    distance[source] = 0;
    for (int step = 0; step < n; ++step) {
        int u = -1;
        for (int v = 0; v < n; ++v)
            if (!visited[v] && (u == -1 || distance[v] < distance[u])) u = v;
        if (u == -1 || distance[u] == INF) break;
        visited[u] = true;
        for (int v = 0; v < n; ++v) {
            if (visited[v] || cost[u][v] == INF) continue;
            if (distance[u] >= INF - cost[u][v])
                throw std::overflow_error("candidate distance reaches INF");
            const auto candidate = distance[u] + cost[u][v];
            if (candidate < distance[v]) distance[v] = candidate;
        }
    }
    return distance;
}
}  // namespace matrix_paths

#pragma once
#include <functional>
#include <limits>
#include <optional>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

namespace paths {
using Weight = long long;
using Distances = std::vector<std::optional<Weight>>;
struct Edge { int from, to; Weight weight; };

inline Weight add(Weight a, Weight b) {
    const auto lo = std::numeric_limits<Weight>::min();
    const auto hi = std::numeric_limits<Weight>::max();
    if ((b > 0 && a > hi - b) || (b < 0 && a < lo - b))
        throw std::overflow_error("distance exceeds signed 64-bit range");
    return a + b;
}

inline void validate(int n, const std::vector<Edge>& edges, int source) {
    if (n <= 0 || source < 0 || source >= n)
        throw std::invalid_argument("invalid graph size or source");
    for (const auto& edge : edges)
        if (edge.from < 0 || edge.from >= n || edge.to < 0 || edge.to >= n)
            throw std::invalid_argument("edge endpoint outside graph");
}

inline Distances dijkstra(int n, const std::vector<Edge>& edges, int source) {
    validate(n, edges, source);
    std::vector<std::vector<std::pair<int, Weight>>> graph(n);
    for (const auto& edge : edges) {
        if (edge.weight < 0)
            throw std::invalid_argument("Dijkstra requires nonnegative weights");
        graph[edge.from].push_back({edge.to, edge.weight});
    }
    Distances distance(n);
    using Item = std::pair<Weight, int>;
    std::priority_queue<Item, std::vector<Item>, std::greater<Item>> pending;
    distance[source] = 0;
    pending.push({0, source});
    while (!pending.empty()) {
        const auto [cost, u] = pending.top();
        pending.pop();
        if (cost != *distance[u]) continue;
        for (const auto& [v, weight] : graph[u]) {
            const auto candidate = add(cost, weight);
            if (!distance[v] || candidate < *distance[v]) {
                distance[v] = candidate;
                pending.push({candidate, v});
            }
        }
    }
    return distance;
}

struct BellmanFordResult {
    Distances distance;
    bool reachable_negative_cycle;
};

inline BellmanFordResult bellman_ford(
        int n, const std::vector<Edge>& edges, int source) {
    validate(n, edges, source);
    Distances distance(n);
    distance[source] = 0;
    for (int pass = 1; pass < n; ++pass) {
        bool changed = false;
        for (const auto& edge : edges) {
            if (!distance[edge.from]) continue;
            const auto candidate = add(*distance[edge.from], edge.weight);
            if (!distance[edge.to] || candidate < *distance[edge.to]) {
                distance[edge.to] = candidate;
                changed = true;
            }
        }
        if (!changed) return {distance, false};
    }
    for (const auto& edge : edges) {
        if (!distance[edge.from]) continue;
        const auto candidate = add(*distance[edge.from], edge.weight);
        if (!distance[edge.to] || candidate < *distance[edge.to])
            return {distance, true};
    }
    return {distance, false};
}
}  // namespace paths

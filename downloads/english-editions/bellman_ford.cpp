#include <iostream>
#include <limits>
#include <vector>
using namespace std;

struct Edge { int from, to; long long weight; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<Edge> edges(m);
    for (auto& edge : edges) cin >> edge.from >> edge.to >> edge.weight;
    const long long INF = numeric_limits<long long>::max() / 4;
    vector<long long> distance(n + 1, INF);
    distance[1] = 0;
    for (int pass = 1; pass < n; ++pass) {
        bool changed = false;
        for (const auto& edge : edges) {
            if (distance[edge.from] == INF) continue;
            const auto candidate = distance[edge.from] + edge.weight;
            if (candidate < distance[edge.to]) {
                distance[edge.to] = candidate;
                changed = true;
            }
        }
        if (!changed) break;
    }
    for (const auto& edge : edges) {
        if (distance[edge.from] != INF &&
            distance[edge.from] + edge.weight < distance[edge.to]) {
            cout << "NEGATIVE CYCLE\n";
            return 0;
        }
    }
    for (int vertex = 2; vertex <= n; ++vertex) {
        if (distance[vertex] == INF) cout << "UNREACHABLE\n";
        else cout << distance[vertex] << '\n';
    }
}

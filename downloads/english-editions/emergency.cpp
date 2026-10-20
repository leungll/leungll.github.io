#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, source, target;
    if (!(cin >> n >> m >> source >> target)) return 0;
    const long long INF = numeric_limits<long long>::max() / 4;
    vector<long long> teams(n), best_teams(n, 0), distance(n, INF);
    for (auto& count : teams) cin >> count;
    vector<vector<long long>> cost(n, vector<long long>(n, INF));
    for (int i = 0; i < n; ++i) cost[i][i] = 0;
    for (int i = 0; i < m; ++i) {
        int a, b;
        long long length;
        cin >> a >> b >> length;
        if (length <= 0 || length >= INF)
            throw invalid_argument("road lengths must be positive and below INF");
        cost[a][b] = cost[b][a] = min(cost[a][b], length);
    }
    vector<unsigned long long> ways(n, 0);
    vector<bool> visited(n, false);
    distance[source] = 0;
    best_teams[source] = teams[source];
    ways[source] = 1;
    for (int step = 0; step < n; ++step) {
        int u = -1;
        for (int v = 0; v < n; ++v)
            if (!visited[v] && (u == -1 || distance[v] < distance[u])) u = v;
        if (u == -1 || distance[u] == INF) break;
        visited[u] = true;
        for (int v = 0; v < n; ++v) {
            if (visited[v] || cost[u][v] == INF) continue;
            if (distance[u] >= INF - cost[u][v])
                throw overflow_error("candidate distance reaches INF");
            const auto candidate = distance[u] + cost[u][v];
            if (candidate < distance[v]) {
                distance[v] = candidate;
                ways[v] = ways[u];
                best_teams[v] = best_teams[u] + teams[v];
            } else if (candidate == distance[v]) {
                if (ways[v] > numeric_limits<unsigned long long>::max() - ways[u])
                    throw overflow_error("shortest-path count exceeds 64 bits");
                ways[v] += ways[u];
                best_teams[v] = max(best_teams[v], best_teams[u] + teams[v]);
            }
        }
    }
    cout << ways[target] << ' ' << best_teams[target] << '\n';
}

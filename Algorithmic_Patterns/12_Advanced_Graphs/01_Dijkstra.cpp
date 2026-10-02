/*
PROBLEM: Shortest Path in a Weighted Graph (Dijkstra's Algorithm)
DESCRIPTION: Given a weighted, directed graph with n nodes (0-indexed) and a list of edges
[from, to, weight] with non-negative weights, find the shortest distance from a given source
node to every other node in the graph. If a node is unreachable, its distance should be -1.
CONSTRAINTS: 1 <= n <= 10^5, 0 <= edges.length <= 2*10^5, 0 <= weight <= 10^4, all weights
are non-negative, graph may be disconnected.
EXAMPLE INPUT/OUTPUT:
  n = 5, edges = [[0,1,4],[0,2,1],[2,1,2],[1,3,1],[2,3,5],[3,4,3]], src = 0
  Output: dist = [0, 3, 1, 4, 7]
  (0->2->1 costs 1+2=3, which beats 0->1 direct cost 4; 0->2->1->3 costs 3+1=4; then ->4 costs 7)
*/

/*
APPROACH:
This is the canonical single-source shortest path algorithm for graphs with non-negative
weights. We maintain a dist[] array initialized to infinity and greedily expand the frontier
using a min-priority-queue keyed on current best-known distance, so the queue always hands us
the closest unvisited node next. We use
priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> as a min-heap
(the default C++ priority_queue is a max-heap, so `greater<>` inverts it). Each time we pop a
node, if the popped distance is stale (worse than the current best), we skip it — this lazy
deletion avoids the complexity of decrease-key operations. Every edge is relaxed at most once
per time it's the best-known route, giving O((V+E) log V) overall.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<long long> dijkstra(int n, vector<vector<int>>& edges, int src) {
        vector<vector<pair<int,int>>> adj(n); // adj[u] = {(v, weight), ...}
        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
        }

        vector<long long> dist(n, LLONG_MAX);
        dist[src] = 0;
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
        pq.push({0LL, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue; // stale entry, already found a better path
            for (auto& [v, w] : adj[u]) {
                long long nd = dist[u] + w;
                if (nd < dist[v]) {
                    dist[v] = nd;
                    pq.push({nd, v});
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (dist[i] == LLONG_MAX) dist[i] = -1;
        }
        return dist;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> edges = {{0,1,4},{0,2,1},{2,1,2},{1,3,1},{2,3,5},{3,4,3}};
    vector<long long> result = sol.dijkstra(5, edges, 0);
    cout << "Distances from node 0: ";
    for (long long d : result) cout << d << " ";
    cout << endl;
    cout << "Expected:               0 3 1 4 7" << endl;

    // Disconnected node test
    vector<vector<int>> edges2 = {{0,1,2}};
    vector<long long> result2 = sol.dijkstra(3, edges2, 0);
    cout << "Distances (disconnected): ";
    for (long long d : result2) cout << d << " ";
    cout << endl;
    cout << "Expected:                 0 2 -1" << endl;

    return 0;
}

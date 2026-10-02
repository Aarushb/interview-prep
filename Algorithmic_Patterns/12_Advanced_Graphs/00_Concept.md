# Advanced Graphs

## Pattern Overview
Advanced graph problems add edge weights, requiring shortest-path algorithms (Dijkstra for non-negative weights, Bellman-Ford for negative weights or hop-limited paths) and minimum-spanning-tree algorithms (Prim's, Kruskal's with Union-Find). The core idea is greedily/iteratively relaxing distances or edge choices until the graph is fully connected or the shortest paths are finalized.

## When to Use It
- The problem gives a **weighted** graph (edge costs, distances, times, probabilities) instead of an unweighted one.
- You're asked for the "shortest path," "minimum cost," "cheapest route," or "fastest time" between nodes.
- There's a constraint on the number of edges/stops/hops allowed (e.g., "at most K stops") — a signal that plain Dijkstra isn't enough and you need Bellman-Ford-style relaxation or a modified state (node, stops-used).
- You need to connect all nodes with minimum total edge weight ("minimum spanning tree," "connect all points," "minimum cost to make all connected").
- The problem can be reframed as "find the path that minimizes the maximum edge weight" (bottleneck shortest path) — classic for problems like Swim in Rising Water.
- Negative edge weights are present or possible — this rules out Dijkstra and points to Bellman-Ford.

## Core Idea
Dijkstra's algorithm finds the shortest path from a single source to all other nodes in a graph with **non-negative** edge weights. It works greedily: repeatedly pop the closest unvisited node from a min-priority-queue, and relax (try to improve) the distances of its neighbors. Because the queue always gives us the globally closest unprocessed node next, once a node is popped its shortest distance is finalized. In C++ this is implemented with `priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>>` acting as a min-heap on `(distance, node)`, and a `dist[]` array initialized to infinity except the source.

When edges can be negative, or when the problem constrains the *number of edges* used (like "cheapest flight within K stops"), Dijkstra's greedy finalization assumption breaks — a longer path with fewer stops might later become cheaper. Bellman-Ford solves this by relaxing **all edges** up to V-1 times (or up to K+1 times for a stop-bounded variant), allowing a node's distance to be updated multiple times as better, more-constrained paths are discovered. It's slower (O(V·E)) but handles negative weights and step-limited relaxation naturally.

Minimum Spanning Tree (MST) problems ask for the cheapest set of edges that connects every node with no cycles. **Prim's algorithm** grows a single tree greedily from an arbitrary start node, always adding the cheapest edge that connects a new node to the tree — implemented almost identically to Dijkstra but relaxing on "edge weight" instead of "cumulative distance." **Kruskal's algorithm** instead sorts all edges by weight and adds them greedily as long as they don't form a cycle, using a **Union-Find (Disjoint Set Union)** structure with path compression and union by rank to detect cycles in near O(1) amortized time. Kruskal's is often simpler to reason about when edges are given as a list; Prim's is natural when you're generating edges from coordinates (e.g., all pairwise Manhattan distances).

A related trick: "minimize the maximum edge weight along a path" (bottleneck path) can be solved either by binary searching on the answer + BFS/DFS feasibility check, or by a Prim's/Dijkstra-like traversal where you track the max edge seen so far instead of the sum.

## Complexity
- Dijkstra (binary heap): Time O((V + E) log V), Space O(V + E)
- Bellman-Ford: Time O(V · E), Space O(V)
- Bellman-Ford with K-stop cap: Time O(K · E), Space O(V)
- Prim's (binary heap): Time O(E log V), Space O(V + E)
- Kruskal's (sort + Union-Find): Time O(E log E), Space O(V + E)

## C++ Template
```cpp
#include <bits/stdc++.h>
using namespace std;

// Dijkstra skeleton — shortest path from src, non-negative weights
vector<int> dijkstra(int n, vector<vector<pair<int,int>>>& adj, int src) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue; // stale entry
        for (auto& [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// Union-Find for Kruskal's MST
struct DSU {
    vector<int> parent, rank_;
    DSU(int n) : parent(n), rank_(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank_[a] < rank_[b]) swap(a, b);
        parent[b] = a;
        if (rank_[a] == rank_[b]) rank_[a]++;
        return true;
    }
};
```

## Common Pitfalls
- Using Dijkstra on a graph with negative edge weights — it will silently produce wrong answers because it never revisits a "finalized" node.
- Forgetting the stale-entry check (`if (d > dist[u]) continue;`) — the same node can be pushed multiple times with different distances.
- For K-stops-constrained problems, using plain Dijkstra's greedy finalization instead of Bellman-Ford-style relaxation — a path with more edges but fewer stops can beat a "shorter" path that exceeds the stop budget.
- Off-by-one on the stop/edge limit (K stops means K+1 edges).
- Forgetting path compression or union by rank in Union-Find, degrading it to O(N) per operation on adversarial inputs.
- Using `int` overflow when summing many large edge weights — prefer `long long` for distance accumulators in large graphs.

# Graphs

## Pattern Overview
Graph problems represent entities and their connections using an adjacency list (or an implicit grid), then explore them with DFS (path-by-path, natural for flood fill and cycle detection) or BFS (level-by-level, needed for shortest paths in unweighted graphs). Cycle detection, connected components, and topological sort (Kahn's algorithm) are the recurring building blocks, all running in O(V+E).

## When to Use It
- The problem describes entities and relationships/connections between them: grids of cells, nodes with neighbors, courses with prerequisites, cities with roads.
- You need to find connected components, count islands/regions, or determine reachability between two points.
- The problem mentions "prerequisites," "dependencies," or "must happen before," which signals a directed graph and possibly topological sort.
- You need to detect a cycle (e.g., "can all courses be completed?", "is this a valid tree?").
- The problem asks for a deep copy / clone of a linked structure with arbitrary connections.
- Water/fire/infection "spreads" from boundary cells inward, or vice versa — a classic multi-source BFS/DFS signal.

## Core Idea
Most graph problems start with choosing a representation. An **adjacency list** (`vector<vector<int>>` or `unordered_map<Node*, vector<Node*>>`) is the standard choice — it uses O(V+E) space and lets you iterate a node's neighbors in O(degree) time, which is what DFS/BFS need. Grids are graphs too: each cell is a node, and its up/down/left/right neighbors are edges, often generated on the fly with a `{dr, dc}` direction array instead of an explicit adjacency list.

**DFS vs BFS** is mostly a matter of what you need: DFS (recursive or with an explicit stack) is natural for exhaustively exploring one path at a time — flood fill, connected components, cycle detection with a recursion-stack check. BFS (with a `queue`) explores level-by-level and is the right tool whenever "shortest path" in an unweighted graph or "distance from source" matters, and it's also commonly used for flood-fill-style problems because it avoids deep recursion on large grids. Both need a `visited` structure (boolean grid/array or a hash set) to avoid revisiting nodes and infinite-looping on cycles — forgetting this is the single most common graph bug.

**Cycle detection** differs by graph type. In an undirected graph, a visited neighbor that isn't the immediate parent means a cycle (or use Union-Find: if two nodes being connected are already in the same set, adding that edge creates a cycle — this is also how "is this a valid tree" is checked, since a tree is exactly a connected, acyclic graph with exactly n-1 edges). In a directed graph, you need to track nodes currently "in progress" on the recursion stack (three-color DFS: unvisited / visiting / visited) — revisiting a "visiting" node means a cycle.

**Topological sort** orders nodes so every edge points forward, and only exists for a DAG (no cycles). The iterative way is **Kahn's algorithm**: compute in-degree for every node, start a queue with all in-degree-0 nodes, repeatedly pop a node, "remove" its outgoing edges by decrementing neighbors' in-degrees, and enqueue any neighbor that hits in-degree 0. If you process fewer than V nodes total, a cycle exists (some nodes never reach in-degree 0). The recursive alternative uses DFS with post-order finishing times pushed onto a stack, reversed at the end.

## Complexity
- Time: O(V + E) for DFS, BFS, Kahn's topological sort, and Union-Find-based cycle detection (Union-Find is O(V + E·α(V)), effectively linear).
- Space: O(V + E) for the adjacency list, plus O(V) for the visited set/array and O(V) for the BFS queue or DFS recursion stack in the worst case.

## C++ Template
```cpp
#include <bits/stdc++.h>
using namespace std;

// Generic BFS traversal template over an adjacency list.
vector<int> bfs(int start, vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<int> order;
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true; // mark on enqueue, not on dequeue, to avoid duplicate enqueues
                q.push(v);
            }
        }
    }
    return order;
}

// Generic Kahn's topological sort with cycle detection.
bool topoSort(int n, vector<vector<int>>& adj, vector<int>& order) {
    vector<int> indeg(n, 0);
    for (int u = 0; u < n; ++u)
        for (int v : adj[u]) indeg[v]++;

    queue<int> q;
    for (int i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u]) if (--indeg[v] == 0) q.push(v);
    }
    return (int)order.size() == n; // false means a cycle exists
}
```

## Common Pitfalls
- Forgetting the `visited` set/array entirely, causing infinite loops on cyclic graphs or repeated re-processing.
- Marking a node visited on *dequeue* instead of on *enqueue* in BFS, which lets the same node be pushed multiple times and wastes time/memory (harmless for correctness in simple cases, but wrong when tracking distances or first-visit order).
- Confusing undirected-graph cycle detection (check neighbor isn't the parent) with directed-graph cycle detection (need a three-state visiting/visited distinction, not just a boolean).
- Off-by-one or bounds errors on grid neighbor checks — forgetting to check `0 <= r < m && 0 <= c < n` before indexing.
- For "clone graph"-style problems, forgetting to check the hashmap *before* creating a new node for a neighbor, resulting in duplicate nodes instead of reusing the already-cloned one.
- Assuming topological sort is unique — any valid ordering that respects all edges is acceptable, and Kahn's queue order depends on iteration/insertion order.

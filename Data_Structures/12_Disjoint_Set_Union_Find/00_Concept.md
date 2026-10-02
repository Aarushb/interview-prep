# Disjoint Set Union / Union-Find

## Overview
A DSU maintains a collection of disjoint (non-overlapping) sets over a fixed universe of elements, each set represented as a tree whose root is that set's "representative". Internally it's just an array `parent[]` (each element points to its parent, a root points to itself) plus an array `rank[]` (or `size[]`) used to keep the trees shallow. Two operations drive everything: `find(x)` walks parent pointers up to the root, and `unite(x, y)` finds both roots and links one under the other. Two optimizations make this near-constant time: **path compression** (during `find`, re-point every visited node directly to the root, flattening the tree for future queries) and **union by rank/size** (when uniting, attach the smaller/shallower tree under the root of the larger/deeper one, preventing tall chains from forming).

## Operations & Complexity
| Operation | Time | Space |
|---|---|---|
| find(x) (with path compression) | O(alpha(n)) amortized, near O(1) | O(1) |
| unite(x, y) (union by rank/size + path compression) | O(alpha(n)) amortized, near O(1) | O(1) |
| connected(x, y) | O(alpha(n)) amortized | O(1) |
| countSets() | O(1) (maintained incrementally) | O(1) |
| overall storage (n elements) | — | O(n) |

alpha(n) is the inverse Ackermann function, which grows so slowly it is effectively <= 4 for any n that could ever be represented in memory — so in practice these operations are treated as O(1) amortized. Without both optimizations, a naive DSU degrades to O(n) per `find` in the worst case (a long chain).

## When It's Used in Interviews
- Detecting cycles / redundant edges in an undirected graph while building it incrementally (e.g. Redundant Connection).
- Counting connected components (e.g. Number of Provinces, number of islands via union-find).
- Kruskal's minimum spanning tree algorithm (union components as edges are added).
- "Are these two things connected/grouped together" queries that arrive online, mixed with union operations, on a graph that only grows (no edge deletions).
- Accounts merging, friend circles, network connectivity problems.

## Trade-offs
- vs BFS/DFS per query: BFS/DFS answers "are x and y connected" in O(V+E) per query on a static graph; DSU answers each query in near O(1) but only supports incremental union (no edge removal) and needs preprocessing (unions) as edges arrive.
- vs recomputing connected components from scratch: DSU updates incrementally in near O(1) per union instead of O(V+E) full recomputation after every edge addition.
- Limitation: classic DSU does not support "un-union" (splitting a set back apart) or edge deletion efficiently — it's a one-directional (merge-only) structure.

/*
PROBLEM 1: Number of Provinces (LeetCode 547)
DESCRIPTION: There are n cities. `isConnected[i][j] = 1` if city i and city j are directly
connected, 0 otherwise (isConnected[i][i] = 1 always). A province is a group of directly or
indirectly connected cities. Return the total number of provinces.
CONSTRAINTS: 1 <= n <= 200, isConnected is an n x n symmetric matrix.
EXAMPLE INPUT/OUTPUT:
  Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
  Output: 2
*/

/*
APPROACH:
This is exactly "count connected components." Create a DSU over the n cities. For every pair (i,
j) with i < j where isConnected[i][j] == 1, unite(i, j) — this merges their provinces if they
weren't already merged. After processing the whole matrix, the DSU's maintained set counter directly
gives the number of provinces (no need to scan for distinct roots afterward). Time: O(n^2 *
alpha(n)) to scan the matrix and perform near-O(1) unions, which is effectively O(n^2) — already
optimal since just reading the n x n input matrix is O(n^2).
*/

#include <bits/stdc++.h>
using namespace std;

class DisjointSetUnion {
private:
    vector<int> parent;
    vector<int> rank_;
    int numSets;

public:
    explicit DisjointSetUnion(int n) : parent(n), rank_(n, 0), numSets(n) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x), rootY = find(y);
        if (rootX == rootY) return false;
        if (rank_[rootX] < rank_[rootY]) parent[rootX] = rootY;
        else if (rank_[rootX] > rank_[rootY]) parent[rootY] = rootX;
        else { parent[rootY] = rootX; rank_[rootX]++; }
        numSets--;
        return true;
    }

    bool connected(int x, int y) { return find(x) == find(y); }
    int countSets() const { return numSets; }
};

int findCircleNum(vector<vector<int>>& isConnected) {
    int n = (int)isConnected.size();
    DisjointSetUnion dsu(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (isConnected[i][j] == 1) {
                dsu.unite(i, j);
            }
        }
    }

    return dsu.countSets();
}

/*
PROBLEM 2: Redundant Connection (LeetCode 684)
DESCRIPTION: A graph started as a tree with n nodes labeled 1..n, but one extra edge was added,
creating exactly one cycle. Given `edges` (the n edges of this graph, each as [u, v]), find the
edge that, if removed, makes the graph a tree again. If multiple answers exist, return the one
that occurs last in the input.
CONSTRAINTS: n == edges.length, 3 <= n <= 1000, 1 <= u, v <= n, u != v, no repeated edges.
EXAMPLE INPUT/OUTPUT:
  Input: edges = [[1,2],[1,3],[2,3]]
  Output: [2,3]
*/

/*
APPROACH:
Process edges in input order, using DSU to build the graph incrementally. For each edge [u, v]:
if u and v are already connected (find(u) == find(v)), then this edge closes a cycle — adding it
is redundant, and since we process edges in order, the FIRST such edge we find (which, since only
one cycle exists, is also the LAST edge overall that creates a redundancy) is the answer required
by the problem ("return the answer that occurs last in the input" — equivalently, the first edge
whose two endpoints are already connected via previously-processed edges, since a tree-plus-one-
extra-edge graph has exactly one such edge). Otherwise, unite(u, v) to add the edge to the growing
forest. Time: O(n * alpha(n)), effectively O(n).
*/

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = (int)edges.size();
    DisjointSetUnion dsu(n + 1); // nodes are labeled 1..n

    for (auto& edge : edges) {
        int u = edge[0], v = edge[1];
        if (dsu.connected(u, v)) {
            return edge; // this edge creates the cycle -> redundant
        }
        dsu.unite(u, v);
    }

    return {}; // unreachable given problem guarantees
}

int main() {
    // Problem 1: Number of Provinces
    {
        vector<vector<int>> isConnected = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
        cout << "Number of Provinces: " << findCircleNum(isConnected) << endl; // Expected: 2
    }
    {
        vector<vector<int>> isConnected = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        cout << "Number of Provinces: " << findCircleNum(isConnected) << endl; // Expected: 3
    }

    // Problem 2: Redundant Connection
    {
        vector<vector<int>> edges = {{1, 2}, {1, 3}, {2, 3}};
        vector<int> result = findRedundantConnection(edges);
        cout << "Redundant Connection: [" << result[0] << ", " << result[1] << "]" << endl;
        // Expected: [2, 3]
    }
    {
        vector<vector<int>> edges = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
        vector<int> result = findRedundantConnection(edges);
        cout << "Redundant Connection: [" << result[0] << ", " << result[1] << "]" << endl;
        // Expected: [1, 4]
    }

    return 0;
}

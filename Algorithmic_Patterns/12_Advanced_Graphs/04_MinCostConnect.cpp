/*
PROBLEM: Min Cost to Connect All Points (LeetCode 1584)
DESCRIPTION: You are given an array points representing integer coordinates of some points on
a 2D-plane, where points[i] = [xi, yi]. The cost of connecting two points [xi, yi] and
[xj, yj] is the Manhattan distance between them: |xi - xj| + |yi - yj|. Return the minimum cost
to make all points connected. All points are connected if there is exactly one simple path
between any two points.
CONSTRAINTS: 1 <= points.length <= 1000, -10^6 <= xi, yi <= 10^6, all pairs (xi, yi) distinct.
EXAMPLE INPUT/OUTPUT:
  points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
  Output: 20
  (an MST connecting all 5 points has total edge weight 20)
*/

/*
APPROACH:
This is a Minimum Spanning Tree problem: every pair of points has an implicit edge weighted by
Manhattan distance, and we want the cheapest set of edges connecting all points with no cycles.
Since the graph is dense (complete graph on up to 1000 points => ~500k edges), I use Prim's
algorithm with a min-priority-queue, which grows a tree from one starting point, always adding
the cheapest edge connecting a new point to the tree. This is O(E log V) with a heap, which
comfortably handles the up-to-~500k implicit edges. Kruskal's with Union-Find would also work
but requires materializing and sorting all O(n^2) edges explicitly, which is less memory
friendly here; Prim's naturally computes edge weights on the fly from the visited set.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 1) return 0;

        vector<bool> inMST(n, false);
        vector<int> minEdge(n, INT_MAX); // cheapest known edge connecting node i to the tree
        minEdge[0] = 0;

        // (edge weight, node)
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0, 0});

        int totalCost = 0;
        int edgesUsed = 0;

        while (!pq.empty() && edgesUsed < n) {
            auto [w, u] = pq.top();
            pq.pop();
            if (inMST[u]) continue; // stale entry
            inMST[u] = true;
            totalCost += w;
            edgesUsed++;

            for (int v = 0; v < n; v++) {
                if (inMST[v]) continue;
                int dist = abs(points[u][0] - points[v][0]) + abs(points[u][1] - points[v][1]);
                if (dist < minEdge[v]) {
                    minEdge[v] = dist;
                    pq.push({dist, v});
                }
            }
        }

        return totalCost;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> points1 = {{0,0},{2,2},{3,10},{5,2},{7,0}};
    cout << "Test 1: " << sol.minCostConnectPoints(points1) << " (expected 20)" << endl;

    vector<vector<int>> points2 = {{3,12},{-2,5},{-4,1}};
    cout << "Test 2: " << sol.minCostConnectPoints(points2) << " (expected 18)" << endl;

    vector<vector<int>> points3 = {{0,0}};
    cout << "Test 3: " << sol.minCostConnectPoints(points3) << " (expected 0, single point)" << endl;

    return 0;
}

/*
PROBLEM: Swim in Rising Water (LeetCode 778)
DESCRIPTION: You are given an n x n integer matrix grid where each value grid[i][j] represents
the elevation at that point (i, j). The rain starts to fall at time 0. At time t, the water
level is t, meaning any cell with elevation less than or equal to t is submerged/flooded. You
can swim from a square to another 4-directionally adjacent square if and only if the elevation
of both squares is at most the water level at that time. You start at (0, 0) and want to reach
(n-1, n-1). Return the minimum time until you can reach the target.
CONSTRAINTS: n == grid.length == grid[i].length, 1 <= n <= 50,
0 <= grid[i][j] < n^2, grid contains every value from 0 to n^2 - 1 exactly once.
EXAMPLE INPUT/OUTPUT:
  grid = [[0,2],[1,3]]
  Output: 3
  (at t=3, every cell is submerged, allowing the path (0,0)->(1,0)->(1,1); the max elevation
   along that path is 3, and no path with max elevation < 3 exists since (0,0) and (1,1) are
   not adjacent and every other path also crosses a cell of elevation >= 3)
*/

/*
APPROACH:
The answer is the minimum possible "maximum elevation along a path" from start to end — a
bottleneck shortest path problem. I solve this with a modified Dijkstra/Prim's-style traversal:
instead of summing edge weights, the "distance" to a cell is the maximum elevation encountered
so far along the best path to reach it. Using a min-priority-queue on this bottleneck value
lets us pop the globally best next cell to expand, exactly like Dijkstra, and it's O(n^2 log n).
An equally valid approach (implemented in comments below) is binary search on the answer t
combined with a BFS/DFS that only visits cells with elevation <= t, checking reachability;
that's O(n^2 log(n^2)). The priority-queue approach is used here since it avoids a second
parameter to tune and runs in a single pass.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> best(n, vector<int>(n, INT_MAX)); // min bottleneck to reach cell
        best[0][0] = grid[0][0];

        // (max elevation along path so far, row, col)
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
        pq.push({grid[0][0], 0, 0});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!pq.empty()) {
            auto [t, r, c] = pq.top();
            pq.pop();
            if (t > best[r][c]) continue; // stale entry
            if (r == n - 1 && c == n - 1) return t;

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                int nt = max(t, grid[nr][nc]); // bottleneck: worst elevation so far
                if (nt < best[nr][nc]) {
                    best[nr][nc] = nt;
                    pq.push({nt, nr, nc});
                }
            }
        }

        return best[n-1][n-1];
    }
};

int main() {
    Solution sol;

    vector<vector<int>> grid1 = {{0,2},{1,3}};
    cout << "Test 1: " << sol.swimInWater(grid1) << " (expected 3)" << endl;

    vector<vector<int>> grid2 = {
        {0,1,2,3,4},
        {24,23,22,21,5},
        {12,13,14,15,16},
        {11,17,18,19,20},
        {10,9,8,7,6}
    };
    cout << "Test 2: " << sol.swimInWater(grid2) << " (expected 16)" << endl;

    return 0;
}

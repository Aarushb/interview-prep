/*
PROBLEM: Unique Paths
DESCRIPTION: There is a robot on an m x n grid. The robot is initially located at the top-left
corner (grid[0][0]). The robot tries to move to the bottom-right corner (grid[m-1][n-1]). The
robot can only move either down or right at any point in time. Given the two integers m and n,
return the number of possible unique paths that the robot can take to reach the bottom-right
corner.
CONSTRAINTS: 1 <= m, n <= 100. The answer is guaranteed to be less than or equal to 2 * 10^9.
EXAMPLE INPUT/OUTPUT:
  Input: m = 3, n = 7  -> Output: 28
  Input: m = 3, n = 2  -> Output: 3
*/

/*
APPROACH:
This is the base example of 2D grid DP: let dp[i][j] be the number of ways to reach cell (i, j)
from (0, 0) moving only right or down. Since the robot can only arrive at (i, j) from directly
above (i-1, j) or directly left (i, j-1), the recurrence is simply dp[i][j] = dp[i-1][j] +
dp[i][j-1], with the entire first row and first column initialized to 1 (only one way to walk
straight along an edge). We fill row by row so every dependency is already computed, then
space-optimize to a single rolling 1D array since each row only depends on the row above it.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        // dp[j] represents the number of ways to reach the current row's column j.
        vector<long long> dp(n, 1LL); // first row: exactly one way to reach every cell (all rights)

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[j] += dp[j - 1]; // dp[j] (from above) + dp[j-1] (from left, already updated this row)
            }
        }
        return (int)dp[n - 1];
    }
};

int main() {
    Solution sol;

    cout << sol.uniquePaths(3, 7) << endl; // expected 28
    cout << sol.uniquePaths(3, 2) << endl; // expected 3
    cout << sol.uniquePaths(1, 1) << endl; // expected 1
    cout << sol.uniquePaths(7, 3) << endl; // expected 28 (symmetric)

    return 0;
}

/*
PROBLEM: Climbing Stairs (LeetCode 70)
DESCRIPTION: You are climbing a staircase. It takes n steps to reach the top. Each time you can
either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
CONSTRAINTS: 1 <= n <= 45.
EXAMPLE INPUT/OUTPUT:
  n = 2 -> Output: 2  (1+1, 2)
  n = 3 -> Output: 3  (1+1+1, 1+2, 2+1)
*/

/*
APPROACH:
Let dp[i] = number of distinct ways to reach step i. The last move to reach step i was either a
single 1-step hop from step i-1, or a 2-step hop from step i-2, so dp[i] = dp[i-1] + dp[i-2] —
this is exactly the Fibonacci recurrence. Base cases: dp[0] = 1 (one way to "do nothing" and
stand at the ground) and dp[1] = 1 (only one way to take a single step). Since each dp[i] only
depends on the two previous values, we space-optimize from an O(n) array down to two rolling
variables, giving O(n) time and O(1) space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if (n <= 1) return 1;

        int prev2 = 1; // dp[0]
        int prev1 = 1; // dp[1]

        for (int i = 2; i <= n; i++) {
            int cur = prev1 + prev2; // dp[i] = dp[i-1] + dp[i-2]
            prev2 = prev1;
            prev1 = cur;
        }

        return prev1;
    }
};

int main() {
    Solution sol;

    cout << "Test 1 (n=2): " << sol.climbStairs(2) << " (expected 2)" << endl;
    cout << "Test 2 (n=3): " << sol.climbStairs(3) << " (expected 3)" << endl;
    cout << "Test 3 (n=5): " << sol.climbStairs(5) << " (expected 8)" << endl;
    cout << "Test 4 (n=1): " << sol.climbStairs(1) << " (expected 1)" << endl;

    return 0;
}

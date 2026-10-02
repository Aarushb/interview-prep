/*
PROBLEM: House Robber (LeetCode 198)
DESCRIPTION: You are a professional robber planning to rob houses along a street. Each house
has a certain amount of money stashed, but adjacent houses have connected security systems, and
it will automatically contact the police if two adjacent houses were broken into on the same
night. Given an integer array nums representing the amount of money at each house, return the
maximum amount of money you can rob tonight without alerting the police (i.e., without robbing
two adjacent houses).
CONSTRAINTS: 1 <= nums.length <= 100, 0 <= nums[i] <= 400.
EXAMPLE INPUT/OUTPUT:
  nums = [1,2,3,1] -> Output: 4  (rob house 0 and house 2: 1 + 3 = 4)
  nums = [2,7,9,3,1] -> Output: 12  (rob house 0, 2, 4: 2 + 9 + 1 = 12)
*/

/*
APPROACH:
Let dp[i] = the maximum money obtainable considering only the first i houses (0-indexed houses
0..i-1). At house i-1, we either skip it (carry forward dp[i-1]) or rob it (take nums[i-1] plus
the best from two houses back, dp[i-2], since we can't rob the immediate neighbor). So
dp[i] = max(dp[i-1], dp[i-2] + nums[i-1]). Base cases: dp[0] = 0 (no houses, no money) and
dp[1] = nums[0] (only one house available). Since the transition only looks back two steps, we
roll it into two variables instead of a full array, giving O(n) time and O(1) space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];

        int prev2 = 0;        // dp[0]
        int prev1 = nums[0];  // dp[1]

        for (int i = 2; i <= n; i++) {
            int cur = max(prev1, prev2 + nums[i - 1]); // skip house i-1 vs rob it
            prev2 = prev1;
            prev1 = cur;
        }

        return prev1;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {1, 2, 3, 1};
    cout << "Test 1: " << sol.rob(nums1) << " (expected 4)" << endl;

    vector<int> nums2 = {2, 7, 9, 3, 1};
    cout << "Test 2: " << sol.rob(nums2) << " (expected 12)" << endl;

    vector<int> nums3 = {5};
    cout << "Test 3: " << sol.rob(nums3) << " (expected 5)" << endl;

    vector<int> nums4 = {2, 1, 1, 2};
    cout << "Test 4: " << sol.rob(nums4) << " (expected 4)" << endl;

    return 0;
}

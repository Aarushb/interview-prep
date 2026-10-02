/*
PROBLEM: Longest Increasing Subsequence (LeetCode 300)
DESCRIPTION: Given an integer array nums, return the length of the longest strictly increasing
subsequence. A subsequence is a sequence derived from the array by deleting some or no elements
without changing the order of the remaining elements.
CONSTRAINTS: 1 <= nums.length <= 2500, -10^4 <= nums[i] <= 10^4.
EXAMPLE INPUT/OUTPUT:
  nums = [10,9,2,5,3,7,101,18] -> Output: 4  (the subsequence [2,3,7,101], or [2,3,7,18])
  nums = [0,1,0,3,2,3] -> Output: 4  (the subsequence [0,1,2,3])
*/

/*
APPROACH:
The classic O(n^2) DP defines dp[i] = length of the longest increasing subsequence ending
exactly at index i, with dp[i] = 1 + max(dp[j]) over all j < i where nums[j] < nums[i] (or 1 if
no such j exists), and the answer is max(dp). That's straightforward but O(n^2).

The optimized O(n log n) approach uses "patience sorting": maintain an array `tails` where
tails[k] holds the smallest possible tail value of any increasing subsequence of length k+1
seen so far. For each new number, binary search (lower_bound) for the first element in `tails`
that is >= num and overwrite it (this represents replacing that subsequence's tail with a
smaller value, which keeps future extensions easier), or append if num is larger than every
element in `tails`. The final length of `tails` is the LIS length. Note `tails` is NOT itself a
valid LIS, only its length is meaningful — this is the key insight that makes the trick work.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // O(n log n) patience-sorting approach
    int lengthOfLIS(vector<int>& nums) {
        vector<int> tails; // tails[k] = smallest tail value of an increasing subsequence of length k+1

        for (int num : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), num);
            if (it == tails.end()) {
                tails.push_back(num); // num extends the longest subsequence so far
            } else {
                *it = num; // replace to keep the tail as small as possible for this length
            }
        }

        return tails.size();
    }

    // O(n^2) alternative, included for reference/comparison
    int lengthOfLIS_Quadratic(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        vector<int> dp(n, 1);
        int best = 1;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            best = max(best, dp[i]);
        }
        return best;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "Test 1 (n log n): " << sol.lengthOfLIS(nums1) << " (expected 4)" << endl;
    cout << "Test 1 (n^2):     " << sol.lengthOfLIS_Quadratic(nums1) << " (expected 4)" << endl;

    vector<int> nums2 = {0, 1, 0, 3, 2, 3};
    cout << "Test 2 (n log n): " << sol.lengthOfLIS(nums2) << " (expected 4)" << endl;

    vector<int> nums3 = {7, 7, 7, 7, 7, 7, 7};
    cout << "Test 3 (n log n): " << sol.lengthOfLIS(nums3) << " (expected 1)" << endl;

    return 0;
}

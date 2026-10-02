/*
PROBLEM: Maximum Subarray
DESCRIPTION: Given an integer array nums, find the subarray with the largest sum, and return its
sum. A subarray is a contiguous non-empty sequence of elements within an array.
CONSTRAINTS: 1 <= nums.length <= 10^5. -10^4 <= nums[i] <= 10^4.
EXAMPLE INPUT/OUTPUT:
  Input: nums = [-2,1,-3,4,-1,2,1,-5,4] -> Output: 6 (subarray [4,-1,2,1])
  Input: nums = [1]                     -> Output: 1
  Input: nums = [5,4,-1,7,8]            -> Output: 23
*/

/*
APPROACH:
This is the base example of the greedy pattern: Kadane's algorithm. The key insight is a running
invariant: "curSum" tracks the best sum of a subarray ending exactly at the current index. At each
element, we greedily decide whether extending the previous subarray is still worthwhile — if
curSum has gone negative, it can only drag down any future sum, so it's strictly better to
restart the subarray at the current element (curSum = nums[i]) rather than carry a negative
prefix forward. This greedy "reset when negative" choice is locally optimal and provably never
loses to any alternative, since a negative prefix never helps a suffix sum. We track the global
best across all positions as we scan once, giving O(n) time and O(1) space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int curSum = nums[0];
        int best = nums[0];

        for (int i = 1; i < (int)nums.size(); i++) {
            curSum = max(nums[i], curSum + nums[i]); // restart here, or extend previous run
            best = max(best, curSum);
        }
        return best;
    }
};

int main() {
    Solution sol;

    vector<int> n1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << sol.maxSubArray(n1) << endl; // expected 6

    vector<int> n2 = {1};
    cout << sol.maxSubArray(n2) << endl; // expected 1

    vector<int> n3 = {5, 4, -1, 7, 8};
    cout << sol.maxSubArray(n3) << endl; // expected 23

    vector<int> n4 = {-3, -1, -2};
    cout << sol.maxSubArray(n4) << endl; // expected -1

    return 0;
}

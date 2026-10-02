/*
PROBLEM: Subarray Sums Divisible by K
DESCRIPTION: Given an integer array nums and an integer k, return the number of non-empty
subarrays that have a sum divisible by k.
CONSTRAINTS:
- 1 <= nums.length <= 3 * 10^4
- -10^4 <= nums[i] <= 10^4
- 2 <= k <= 10^4
EXAMPLE INPUT/OUTPUT:
Input: nums = [4,5,0,-2,-3,1], k = 5 -> Output: 7
Input: nums = [5], k = 9 -> Output: 0
*/

/*
APPROACH:
Two prefix sums that share the same remainder modulo k define a subarray between them whose
sum is divisible by k (since (prefixJ - prefixI) % k == 0 exactly when prefixJ % k ==
prefixI % k). So instead of hashing raw prefix sums, we hash the *remainder* of the running
sum modulo k and count how many times each remainder has occurred. For every new remainder we
add the count of prior occurrences of that same remainder to our answer, then increment that
remainder's count. Since C++'s % can return negative values for negative operands, we normalize
with ((rem % k) + k) % k. Seed the map with {0: 1} for subarrays starting at index 0. O(n) time,
O(k) space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        vector<int> remainderCount(k, 0);
        remainderCount[0] = 1; // empty prefix has remainder 0
        int runningSum = 0;
        int count = 0;

        for (int num : nums) {
            runningSum += num;
            int rem = ((runningSum % k) + k) % k; // normalize to [0, k-1]
            count += remainderCount[rem];
            remainderCount[rem]++;
        }
        return count;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {4, 5, 0, -2, -3, 1};
    cout << "Input: nums=[4,5,0,-2,-3,1], k=5 -> Output: " << sol.subarraysDivByK(nums1, 5)
         << " (Expected: 7)" << endl;

    vector<int> nums2 = {5};
    cout << "Input: nums=[5], k=9 -> Output: " << sol.subarraysDivByK(nums2, 9)
         << " (Expected: 0)" << endl;

    return 0;
}

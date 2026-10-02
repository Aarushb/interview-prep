/*
PROBLEM: Subarray Sum Equals K
DESCRIPTION: Given an array of integers nums and an integer k, return the total number of
subarrays whose sum equals to k. A subarray is a contiguous non-empty sequence of elements
within an array.
CONSTRAINTS:
- 1 <= nums.length <= 2 * 10^4
- -1000 <= nums[i] <= 1000
- -10^7 <= k <= 10^7
EXAMPLE INPUT/OUTPUT:
Input: nums = [1,1,1], k = 2 -> Output: 2
Input: nums = [1,2,3], k = 3 -> Output: 2
*/

/*
APPROACH:
Maintain a running prefix sum while scanning left to right, and a hashmap that counts how many
times each prefix-sum value has occurred so far. For the subarray ending at the current index
to sum to k, there must be some earlier prefix sum equal to (runningSum - k) — because
runningSum - earlierPrefixSum = k defines exactly that subarray. So at each step we look up
(runningSum - k) in the map and add its count to the answer, then record the current
runningSum in the map. Seeding the map with {0: 1} handles subarrays that start at index 0.
This is O(n) time and O(n) space, versus the O(n^2) brute force of checking every subarray.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<long long, int> prefixCount;
        prefixCount[0] = 1;
        long long runningSum = 0;
        int count = 0;

        for (int num : nums) {
            runningSum += num;
            auto it = prefixCount.find(runningSum - k);
            if (it != prefixCount.end()) {
                count += it->second;
            }
            prefixCount[runningSum]++;
        }
        return count;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {1, 1, 1};
    cout << "Input: nums=[1,1,1], k=2 -> Output: " << sol.subarraySum(nums1, 2)
         << " (Expected: 2)" << endl;

    vector<int> nums2 = {1, 2, 3};
    cout << "Input: nums=[1,2,3], k=3 -> Output: " << sol.subarraySum(nums2, 3)
         << " (Expected: 2)" << endl;

    return 0;
}

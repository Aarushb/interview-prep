/*
PROBLEM: Contiguous Array
DESCRIPTION: Given a binary array nums, return the maximum length of a contiguous subarray
with an equal number of 0 and 1.
CONSTRAINTS:
- 1 <= nums.length <= 10^5
- nums[i] is either 0 or 1.
EXAMPLE INPUT/OUTPUT:
Input: nums = [0,1] -> Output: 2
Input: nums = [0,1,0] -> Output: 2
Input: nums = [0,1,1,1,1,1,0,0,0] -> Output: 6
*/

/*
APPROACH:
Remap every 0 to -1 and every 1 to +1. Now "equal number of 0s and 1s in a subarray" is
equivalent to "that subarray's sum is 0" under the remapped values. Track a running sum and
the first index at which each running-sum value was seen using a hashmap. If the same running
sum reoccurs at a later index, everything between those two indices sums to zero, meaning
equal 0s and 1s — the length of that subarray is (currentIndex - firstSeenIndex). We keep the
maximum such length. Seed the map with {0: -1} to correctly handle subarrays that start at
index 0. This is O(n) time and O(n) space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> firstIndexOfSum;
        firstIndexOfSum[0] = -1; // sum of 0 seen "before" the array starts
        int runningSum = 0;
        int maxLen = 0;

        for (int i = 0; i < static_cast<int>(nums.size()); i++) {
            runningSum += (nums[i] == 0) ? -1 : 1;

            auto it = firstIndexOfSum.find(runningSum);
            if (it != firstIndexOfSum.end()) {
                maxLen = max(maxLen, i - it->second);
            } else {
                firstIndexOfSum[runningSum] = i;
            }
        }
        return maxLen;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {0, 1};
    cout << "Input: [0,1] -> Output: " << sol.findMaxLength(nums1) << " (Expected: 2)" << endl;

    vector<int> nums2 = {0, 1, 0};
    cout << "Input: [0,1,0] -> Output: " << sol.findMaxLength(nums2) << " (Expected: 2)" << endl;

    vector<int> nums3 = {0, 1, 1, 1, 1, 1, 0, 0, 0};
    cout << "Input: [0,1,1,1,1,1,0,0,0] -> Output: " << sol.findMaxLength(nums3)
         << " (Expected: 6)" << endl;

    return 0;
}

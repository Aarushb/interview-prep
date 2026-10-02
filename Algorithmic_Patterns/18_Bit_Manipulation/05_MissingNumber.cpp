/*
PROBLEM: Missing Number
DESCRIPTION: Given an array nums containing n distinct numbers in the range [0, n], return the
only number in the range that is missing from the array.
CONSTRAINTS:
- n == nums.length
- 1 <= n <= 10^4
- 0 <= nums[i] <= n
- All the numbers of nums are unique.
EXAMPLE INPUT/OUTPUT:
Input: nums = [3,0,1] -> Output: 2
Input: nums = [0,1] -> Output: 2
Input: nums = [9,6,4,2,3,5,7,0,1] -> Output: 8
*/

/*
APPROACH:
XOR every index 0..n with every value in nums, plus XOR in n itself (since indices only go up
to n-1 but the range is [0, n]). Every value that is present in both the index sequence and the
array cancels out via x ^ x = 0, leaving only the missing number. This avoids the O(n) extra
space of a hash set and the overflow risk of the "sum formula" approach, running in O(n) time
and O(1) space with a single pass.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int result = static_cast<int>(nums.size()); // account for index n
        for (int i = 0; i < static_cast<int>(nums.size()); i++) {
            result ^= i ^ nums[i];
        }
        return result;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {3, 0, 1};
    cout << "Input: [3,0,1] -> Output: " << sol.missingNumber(nums1) << " (Expected: 2)" << endl;

    vector<int> nums2 = {0, 1};
    cout << "Input: [0,1] -> Output: " << sol.missingNumber(nums2) << " (Expected: 2)" << endl;

    vector<int> nums3 = {9, 6, 4, 2, 3, 5, 7, 0, 1};
    cout << "Input: [9,6,4,2,3,5,7,0,1] -> Output: " << sol.missingNumber(nums3)
         << " (Expected: 8)" << endl;

    return 0;
}

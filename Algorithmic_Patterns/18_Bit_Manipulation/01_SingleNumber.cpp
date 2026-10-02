/*
PROBLEM: Single Number
DESCRIPTION: Given a non-empty array of integers `nums`, every element appears twice except
for one. Find that single one. You must implement a solution with a linear runtime complexity
and use only constant extra space.
CONSTRAINTS:
- 1 <= nums.length <= 3 * 10^4
- -3 * 10^4 <= nums[i] <= 3 * 10^4
- Each element in the array appears twice except for one element which appears only once.
EXAMPLE INPUT/OUTPUT:
Input: nums = [2,2,1] -> Output: 1
Input: nums = [4,1,2,1,2] -> Output: 4
Input: nums = [1] -> Output: 1
*/

/*
APPROACH:
The key insight is XOR's self-cancellation property: x ^ x = 0 and x ^ 0 = x. XOR is also
commutative and associative, so XOR-ing every element together lets all paired duplicates
cancel each other out (in any order), leaving only the value that appears once. This gives
an O(n) time, O(1) space solution in a single pass — no hashmap or sorting needed.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num;
        }
        return result;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {2, 2, 1};
    cout << "Input: [2,2,1] -> Output: " << sol.singleNumber(nums1) << " (Expected: 1)" << endl;

    vector<int> nums2 = {4, 1, 2, 1, 2};
    cout << "Input: [4,1,2,1,2] -> Output: " << sol.singleNumber(nums2) << " (Expected: 4)" << endl;

    vector<int> nums3 = {1};
    cout << "Input: [1] -> Output: " << sol.singleNumber(nums3) << " (Expected: 1)" << endl;

    return 0;
}

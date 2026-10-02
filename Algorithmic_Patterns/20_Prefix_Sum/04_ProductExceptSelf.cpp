/*
PROBLEM: Product of Array Except Self
DESCRIPTION: Given an integer array nums, return an array answer such that answer[i] is equal
to the product of all the elements of nums except nums[i]. You must write an algorithm that
runs in O(n) time and without using the division operation. The output array does not count as
extra space for space complexity analysis.
CONSTRAINTS:
- 2 <= nums.length <= 10^5
- -30 <= nums[i] <= 30
- The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
EXAMPLE INPUT/OUTPUT:
Input: nums = [1,2,3,4] -> Output: [24,12,8,6]
Input: nums = [-1,1,0,-3,3] -> Output: [0,0,9,0,0]
*/

/*
APPROACH:
This is the prefix/suffix variant of the prefix-sum pattern, but with products: answer[i] is
the product of the prefix product (everything strictly left of i) times the suffix product
(everything strictly right of i). We compute this without division and in O(1) extra space
(beyond the output array) by doing two passes over the output array itself: first fill it with
prefix products left-to-right, then do a second pass right-to-left multiplying in a running
suffix product. This avoids both division (which breaks on zeros) and the O(n) extra space of
separate prefix/suffix arrays.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> answer(n, 1);

        // First pass: answer[i] holds product of everything to the left of i
        int prefix = 1;
        for (int i = 0; i < n; i++) {
            answer[i] = prefix;
            prefix *= nums[i];
        }

        // Second pass: multiply in the product of everything to the right of i
        int suffix = 1;
        for (int i = n - 1; i >= 0; i--) {
            answer[i] *= suffix;
            suffix *= nums[i];
        }

        return answer;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {1, 2, 3, 4};
    vector<int> res1 = sol.productExceptSelf(nums1);
    cout << "Input: [1,2,3,4] -> Output: [";
    for (size_t i = 0; i < res1.size(); i++) cout << res1[i] << (i + 1 < res1.size() ? "," : "");
    cout << "] (Expected: [24,12,8,6])" << endl;

    vector<int> nums2 = {-1, 1, 0, -3, 3};
    vector<int> res2 = sol.productExceptSelf(nums2);
    cout << "Input: [-1,1,0,-3,3] -> Output: [";
    for (size_t i = 0; i < res2.size(); i++) cout << res2[i] << (i + 1 < res2.size() ? "," : "");
    cout << "] (Expected: [0,0,9,0,0])" << endl;

    return 0;
}

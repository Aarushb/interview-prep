/*
PROBLEM: Range Sum Query - Immutable
DESCRIPTION: Given an integer array nums, handle multiple queries of the following type:
Calculate the sum of the elements of nums between indices left and right inclusive where
left <= right. Implement the NumArray class:
- NumArray(int[] nums) Initializes the object with the integer array nums.
- int sumRange(int left, int right) Returns the sum of the elements of nums between indices
  left and right inclusive.
CONSTRAINTS:
- 1 <= nums.length <= 10^4
- -10^5 <= nums[i] <= 10^5
- 0 <= left <= right < nums.length
- At most 10^4 calls will be made to sumRange.
EXAMPLE INPUT/OUTPUT:
Input: ["NumArray","sumRange","sumRange","sumRange"], [[[-2,0,3,-5,2,-1]],[0,2],[2,5],[0,5]]
Output: [null,1,-1,-3]
*/

/*
APPROACH:
This is the base example of the prefix sum pattern: since the array is immutable and there are
many queries, precompute a prefix sum array once in the constructor (O(n)) where prefix[i] is
the sum of the first i elements. Each sumRange query then becomes O(1): prefix[right+1] -
prefix[left]. Using a length n+1 prefix array with prefix[0] = 0 avoids special-casing left = 0.
*/

#include <bits/stdc++.h>
using namespace std;

class NumArray {
public:
    NumArray(vector<int>& nums) {
        prefix.resize(nums.size() + 1, 0);
        for (int i = 0; i < static_cast<int>(nums.size()); i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }

    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }

private:
    vector<int> prefix;
};

int main() {
    vector<int> nums = {-2, 0, 3, -5, 2, -1};
    NumArray numArray(nums);

    cout << "sumRange(0,2) -> " << numArray.sumRange(0, 2) << " (Expected: 1)" << endl;
    cout << "sumRange(2,5) -> " << numArray.sumRange(2, 5) << " (Expected: -1)" << endl;
    cout << "sumRange(0,5) -> " << numArray.sumRange(0, 5) << " (Expected: -3)" << endl;

    return 0;
}

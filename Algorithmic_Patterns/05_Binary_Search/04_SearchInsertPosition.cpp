/*
PROBLEM: Search Insert Position
DESCRIPTION: Given a sorted array of distinct integers nums and a target value, return the index if target is found. If not, return the index where it would be if it were inserted in order. You must write an algorithm with O(log n) runtime complexity.
CONSTRAINTS:
- 1 <= nums.length <= 10^4
- -10^4 <= nums[i] <= 10^4
- nums contains distinct values sorted in ascending order.
- -10^4 <= target <= 10^4
EXAMPLE INPUT/OUTPUT:
Input: nums = [1,3,5,6], target = 5
Output: 2

Input: nums = [1,3,5,6], target = 2
Output: 1
*/

/*
APPROACH:
This is standard binary search, but instead of returning -1 when the target isn't found, I
return where it would belong. The trick is that when the loop ends (left > right), left has
naturally converged to the first index whose value is >= target — exactly the correct
insertion point, whether or not target actually exists in the array. So I just run the usual
binary search and return left at the end. Still O(log n) time, O(1) space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return left;  // Insert position
    }
};

int main() {
    Solution sol;
    vector<int> nums = {1,3,5,6};
    cout << sol.searchInsert(nums, 5) << endl;  // 2
    cout << sol.searchInsert(nums, 2) << endl;  // 1
    return 0;
}

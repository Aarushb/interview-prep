/*
PROBLEM: Search in Rotated Sorted Array
DESCRIPTION: There is an integer array nums sorted in ascending order (with distinct values). Prior to being passed to your function, nums is possibly rotated at an unknown pivot index. Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
CONSTRAINTS:
- 1 <= nums.length <= 5000
- -10^4 <= nums[i] <= 10^4
- All values of nums are unique.
- nums is an ascending array that is possibly rotated.
- -10^4 <= target <= 10^4
- Must run in O(log n) time.
EXAMPLE INPUT/OUTPUT:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1
*/

#include <bits/stdc++.h>
using namespace std;

/*
APPROACH:
Even though the array isn't fully sorted anymore, I can still binary search because at
least one half of any subarray (left..mid or mid..right) is always properly sorted. So at
each step I first figure out which half is sorted by comparing nums[left] to nums[mid],
then check whether target falls inside that sorted half's range. If it does, I search that
half; otherwise the target must be in the other (unsorted) half, so I search there instead.
This preserves O(log n) time and O(1) space, same as standard binary search.
*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) return mid;
            
            // Determine which half is sorted
            if (nums[left] <= nums[mid]) {
                // Left half is sorted
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                // Right half is sorted
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        return -1;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {4,5,6,7,0,1,2};
    cout << "Found at index: " << sol.search(nums, 0) << endl;
    return 0;
}

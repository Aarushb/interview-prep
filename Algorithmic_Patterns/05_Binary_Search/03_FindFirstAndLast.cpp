/*
PROBLEM: Find First and Last Position of Element in Sorted Array
DESCRIPTION: Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value. If target is not found in the array, return [-1, -1]. You must write an algorithm with O(log n) runtime complexity.
CONSTRAINTS:
- 0 <= nums.length <= 10^5
- -10^9 <= nums[i] <= 10^9
- nums is a non-decreasing array.
- -10^9 <= target <= 10^9
EXAMPLE INPUT/OUTPUT:
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
*/

/*
APPROACH:
Since I need both the first and last index of target, I run two slightly modified binary
searches instead of one. For the first occurrence, whenever nums[mid] == target I record it
but keep searching the left half (right = mid - 1) in case an earlier occurrence exists. For
the last occurrence, I do the mirror image: record the match and keep searching the right
half (left = mid + 1). Each search is still O(log n), so the whole solution is O(log n)
overall with O(1) extra space, just two passes instead of one.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> result = {-1, -1};
        result[0] = findFirst(nums, target);
        result[1] = findLast(nums, target);
        return result;
    }
    
private:
    int findFirst(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1, result = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                result = mid;
                right = mid - 1;  // Continue left
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return result;
    }
    
    int findLast(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1, result = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                result = mid;
                left = mid + 1;  // Continue right
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return result;
    }
};

int main() {
    Solution sol;
    vector<int> nums = {5,7,7,8,8,10};
    vector<int> result = sol.searchRange(nums, 8);
    cout << "[" << result[0] << "," << result[1] << "]" << endl;
    return 0;
}

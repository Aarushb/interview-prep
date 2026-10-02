/*
PROBLEM: Binary Search
DESCRIPTION: Given an array of integers nums which is sorted in ascending order, and an integer target, write a function to search target in nums. If target exists, then return its index. Otherwise, return -1.
You must write an algorithm with O(log n) runtime complexity.
CONSTRAINTS:
- 1 <= nums.length <= 10^4
- -10^4 < nums[i], target < 10^4
- All integers in nums are unique.
- nums is sorted in ascending order.
EXAMPLE INPUT/OUTPUT:
Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4

Input: nums = [-1,0,3,5,9,12], target = 2
Output: -1
*/

#include <bits/stdc++.h>
using namespace std;

/*
APPROACH:
This is classic binary search, so I'd keep two pointers, left and right, bounding the
search space and repeatedly check the middle element. If the array is sorted, comparing
nums[mid] to target lets me discard half the remaining elements every step, since
everything on the wrong side of mid must also be on the wrong side of target. I use
left + (right - left) / 2 instead of (left + right) / 2 to avoid integer overflow, and
loop while left <= right so a single remaining element still gets checked. Each iteration
halves the search space, which is exactly why this runs in O(log n) time with O(1) space.
*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left <= right) {
            // Avoid overflow: don't use (left + right) / 2
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) {
                return mid;  // Found
            } else if (nums[mid] < target) {
                left = mid + 1;  // Search right half
            } else {
                right = mid - 1;  // Search left half
            }
        }
        
        return -1;  // Not found
    }
    
    // Recursive version (less preferred in interviews)
    int searchRecursive(vector<int>& nums, int target) {
        return binarySearchHelper(nums, target, 0, nums.size() - 1);
    }
    
private:
    int binarySearchHelper(vector<int>& nums, int target, int left, int right) {
        if (left > right) return -1;
        
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            return binarySearchHelper(nums, target, mid + 1, right);
        } else {
            return binarySearchHelper(nums, target, left, mid - 1);
        }
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> nums1 = {-1, 0, 3, 5, 9, 12};
    cout << "Test 1: " << sol.search(nums1, 9) << endl;
    // Expected: 4
    
    // Test Case 2
    vector<int> nums2 = {-1, 0, 3, 5, 9, 12};
    cout << "Test 2: " << sol.search(nums2, 2) << endl;
    // Expected: -1
    
    // Test Case 3 - Single element
    vector<int> nums3 = {5};
    cout << "Test 3: " << sol.search(nums3, 5) << endl;
    // Expected: 0
    
    // Test Case 4 - Target at beginning
    vector<int> nums4 = {1, 2, 3, 4, 5};
    cout << "Test 4: " << sol.search(nums4, 1) << endl;
    // Expected: 0
    
    // Test Case 5 - Target at end
    vector<int> nums5 = {1, 2, 3, 4, 5};
    cout << "Test 5: " << sol.search(nums5, 5) << endl;
    // Expected: 4
    
    return 0;
}

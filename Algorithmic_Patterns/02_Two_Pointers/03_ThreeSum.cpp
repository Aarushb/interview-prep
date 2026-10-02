/*
PROBLEM: 3Sum
DESCRIPTION: Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
Notice that the solution set must not contain duplicate triplets.
CONSTRAINTS:
- 3 <= nums.length <= 3000
- -10^5 <= nums[i] <= 10^5
EXAMPLE INPUT/OUTPUT:
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].

Input: nums = [0,1,1]
Output: []

Input: nums = [0,0,0]
Output: [[0,0,0]]
*/

/*
APPROACH:
I first sort the array, then fix one element at a time and reduce the remaining problem to a Two Sum
on a sorted subarray using two pointers, looking for pairs that sum to the negative of the fixed
element. To avoid duplicate triplets, I skip over repeated values for the fixed element and for both
pointers whenever a match is found. Sorting plus two pointers brings this down from the O(n^3) brute
force to O(n^2).
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

This problem extends Two Sum II to THREE numbers. It's a classic TWO POINTERS problem.

BRUTE FORCE:
- Three nested loops to check all triplets
- Time: O(n³), Space: O(1)

OPTIMIZED APPROACH:
1. SORT the array first
2. Fix one element (outer loop)
3. Use TWO POINTERS on remaining array to find pairs that sum to -fixed_element
4. Skip duplicates to avoid duplicate triplets

ALGORITHM:
1. Sort the array
2. For i from 0 to n-3:
   a. Skip duplicate values for i
   b. Set target = -nums[i]
   c. Use two pointers (left = i+1, right = n-1)
   d. Find pairs that sum to target
   e. Skip duplicates for left and right pointers
3. Return all unique triplets

TIME COMPLEXITY: O(n²)
- Sorting: O(n log n)
- Outer loop: O(n)
- Inner two pointers: O(n)
- Total: O(n log n) + O(n²) = O(n²)

SPACE COMPLEXITY: O(1) or O(n)
- O(1) if we don't count the output
- O(n) for sorting (depending on sort implementation)

TRICKS:
1. ALWAYS sort array first for two pointers problems
2. Skip duplicates at THREE places: outer loop, left pointer, right pointer
3. Convert 3Sum to 2Sum by fixing one element
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        
        // Step 1: Sort the array
        sort(nums.begin(), nums.end());
        
        // Step 2: Fix first element and find pairs for remaining
        for (int i = 0; i < n - 2; i++) {
            // Skip duplicates for first element
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            
            // Now find pairs that sum to -nums[i]
            int target = -nums[i];
            int left = i + 1;
            int right = n - 1;
            
            while (left < right) {
                int sum = nums[left] + nums[right];
                
                if (sum == target) {
                    // Found a triplet
                    result.push_back({nums[i], nums[left], nums[right]});
                    
                    // Skip duplicates for left pointer
                    while (left < right && nums[left] == nums[left + 1]) {
                        left++;
                    }
                    
                    // Skip duplicates for right pointer
                    while (left < right && nums[right] == nums[right - 1]) {
                        right--;
                    }
                    
                    left++;
                    right--;
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        
        return result;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> result1 = sol.threeSum(nums1);
    cout << "Test 1: ";
    for (auto& triplet : result1) {
        cout << "[" << triplet[0] << "," << triplet[1] << "," << triplet[2] << "] ";
    }
    cout << endl;
    // Expected: [[-1,-1,2],[-1,0,1]]
    
    // Test Case 2
    vector<int> nums2 = {0, 1, 1};
    vector<vector<int>> result2 = sol.threeSum(nums2);
    cout << "Test 2: ";
    for (auto& triplet : result2) {
        cout << "[" << triplet[0] << "," << triplet[1] << "," << triplet[2] << "] ";
    }
    cout << endl;
    // Expected: []
    
    // Test Case 3
    vector<int> nums3 = {0, 0, 0};
    vector<vector<int>> result3 = sol.threeSum(nums3);
    cout << "Test 3: ";
    for (auto& triplet : result3) {
        cout << "[" << triplet[0] << "," << triplet[1] << "," << triplet[2] << "] ";
    }
    cout << endl;
    // Expected: [[0,0,0]]
    
    // Test Case 4
    vector<int> nums4 = {-2, 0, 1, 1, 2};
    vector<vector<int>> result4 = sol.threeSum(nums4);
    cout << "Test 4: ";
    for (auto& triplet : result4) {
        cout << "[" << triplet[0] << "," << triplet[1] << "," << triplet[2] << "] ";
    }
    cout << endl;
    // Expected: [[-2,0,2],[-2,1,1]]
    
    return 0;
}

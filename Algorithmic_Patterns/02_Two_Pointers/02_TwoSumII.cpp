/*
PROBLEM: Two Sum II - Input Array Is Sorted
DESCRIPTION: Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.
CONSTRAINTS:
- 2 <= numbers.length <= 3 * 10^4
- -1000 <= numbers[i] <= 1000
- numbers is sorted in non-decreasing order
- -1000 <= target <= 1000
- The tests are generated such that there is exactly one solution
EXAMPLE INPUT/OUTPUT:
Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].

Input: numbers = [2,3,4], target = 6
Output: [1,3]

Input: numbers = [-1,0], target = -1
Output: [1,2]
*/

/*
APPROACH:
Because the array is already sorted, I can use two pointers instead of a hash map: one starting at
the left, one at the right. If the sum at the pointers is too small I move the left pointer right to
increase it, and if it's too large I move the right pointer left to decrease it; an exact match gives
the answer immediately. The sorted order guarantees this greedy movement never skips the correct
pair, reducing space from O(n) to O(1) compared to the hash map approach.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

This problem is a classic example of TWO POINTERS on a SORTED array.

NAIVE APPROACH:
- Use hash map like regular Two Sum
- Time: O(n), Space: O(n)

OPTIMAL APPROACH (Two Pointers):
Since the array is SORTED, we can use two pointers:
- One at the beginning (left)
- One at the end (right)
- Calculate sum = numbers[left] + numbers[right]
- If sum == target → Found the answer
- If sum < target → We need a larger sum, so move left pointer right (left++)
- If sum > target → We need a smaller sum, so move right pointer left (right--)
- Time: O(n), Space: O(1)

WHY THIS WORKS:
1. If sum is too small, the only way to increase it is to move left pointer right (larger value)
2. If sum is too large, the only way to decrease it is to move right pointer left (smaller value)
3. The sorted property guarantees we won't miss the solution

TRICK:
- The sorted array is the KEY to using two pointers instead of hash map
- This saves space: O(n) → O(1)
- Always check if array is sorted when you see "find pair with sum"
*/

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;
        
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            
            if (sum == target) {
                // Return 1-indexed positions
                return {left + 1, right + 1};
            } else if (sum < target) {
                // Need larger sum, move left pointer right
                left++;
            } else {
                // Need smaller sum, move right pointer left
                right--;
            }
        }
        
        return {};  // No solution (shouldn't happen per constraints)
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> result1 = sol.twoSum(nums1, target1);
    cout << "Test 1: [" << result1[0] << ", " << result1[1] << "]" << endl;
    // Expected: [1, 2]
    
    // Test Case 2
    vector<int> nums2 = {2, 3, 4};
    int target2 = 6;
    vector<int> result2 = sol.twoSum(nums2, target2);
    cout << "Test 2: [" << result2[0] << ", " << result2[1] << "]" << endl;
    // Expected: [1, 3]
    
    // Test Case 3
    vector<int> nums3 = {-1, 0};
    int target3 = -1;
    vector<int> result3 = sol.twoSum(nums3, target3);
    cout << "Test 3: [" << result3[0] << ", " << result3[1] << "]" << endl;
    // Expected: [1, 2]
    
    // Test Case 4 - Large array
    vector<int> nums4 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int target4 = 19;
    vector<int> result4 = sol.twoSum(nums4, target4);
    cout << "Test 4: [" << result4[0] << ", " << result4[1] << "]" << endl;
    // Expected: [9, 10]
    
    // Test Case 5 - Negative numbers
    vector<int> nums5 = {-5, -3, -1, 0, 2, 4};
    int target5 = -4;
    vector<int> result5 = sol.twoSum(nums5, target5);
    cout << "Test 5: [" << result5[0] << ", " << result5[1] << "]" << endl;
    // Expected: [1, 3] (-5 + -1 = -6, -3 + -1 = -4)
    
    return 0;
}

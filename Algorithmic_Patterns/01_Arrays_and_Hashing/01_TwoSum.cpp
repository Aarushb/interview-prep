/*
PROBLEM: Two Sum
DESCRIPTION: Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
You may assume that each input would have exactly one solution, and you may not use the same element twice.
You can return the answer in any order.
CONSTRAINTS:
- 2 <= nums.length <= 10^4
- -10^9 <= nums[i] <= 10^9
- -10^9 <= target <= 10^9
- Only one valid answer exists.
EXAMPLE INPUT/OUTPUT:
Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: nums[0] + nums[1] = 2 + 7 = 9

Input: nums = [3,2,4], target = 6
Output: [1,2]
*/

/*
APPROACH:
I'd use a hash map to trade space for time. As I scan the array once, for each number I compute
its complement (target - num) and check whether I've already seen it in the map; if so, I return
both indices immediately. Otherwise I store the current number and its index for future lookups.
This works in a single O(n) pass because by the time I reach index i, everything before it is
already recorded, which guarantees I never reuse the same element twice.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

This is the quintessential hash map problem and demonstrates why hash tables are powerful.

BRUTE FORCE APPROACH (O(n²)):
- For each element, check all other elements to find complement
- Two nested loops
- Time: O(n²), Space: O(1)

OPTIMIZED APPROACH (O(n)):
- Use hash map to store elements we've seen with their indices
- For each element, calculate complement = target - current_element
- Check if complement exists in hash map
- If yes, return [hash_map[complement], current_index]
- If no, store current element in hash map

KEY INSIGHT:
Instead of looking for pairs simultaneously, we can:
1. For each number, we know what its pair should be (target - num)
2. Check if we've already seen that pair
3. If not, remember this number for future elements

TRICK:
We only need ONE pass through the array because:
- When we're at index i, we've already stored all elements before i
- So if complement exists, it must be before current position
- This automatically ensures we don't use same element twice
*/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // Hash map to store: number -> its index
        unordered_map<int, int> seen;
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            // Check if complement exists in our hash map
            if (seen.count(complement)) {
                return {seen[complement], i};
            }
            
            // Store current number and its index
            seen[nums[i]] = i;
        }
        
        return {};  // No solution found (shouldn't happen per constraints)
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> result1 = sol.twoSum(nums1, target1);
    cout << "Test 1: [" << result1[0] << ", " << result1[1] << "]" << endl;
    // Expected: [0, 1]
    
    // Test Case 2
    vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    vector<int> result2 = sol.twoSum(nums2, target2);
    cout << "Test 2: [" << result2[0] << ", " << result2[1] << "]" << endl;
    // Expected: [1, 2]
    
    // Test Case 3
    vector<int> nums3 = {3, 3};
    int target3 = 6;
    vector<int> result3 = sol.twoSum(nums3, target3);
    cout << "Test 3: [" << result3[0] << ", " << result3[1] << "]" << endl;
    // Expected: [0, 1]
    
    // Test Case 4 - Negative numbers
    vector<int> nums4 = {-1, -2, -3, -4, -5};
    int target4 = -8;
    vector<int> result4 = sol.twoSum(nums4, target4);
    cout << "Test 4: [" << result4[0] << ", " << result4[1] << "]" << endl;
    // Expected: [2, 4] (-3 + -5 = -8)
    
    return 0;
}

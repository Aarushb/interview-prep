/*
PROBLEM: Longest Consecutive Sequence
DESCRIPTION: Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.
You must write an algorithm that runs in O(n) time.
CONSTRAINTS:
- 0 <= nums.length <= 10^5
- -10^9 <= nums[i] <= 10^9
EXAMPLE INPUT/OUTPUT:
Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive sequence is [1, 2, 3, 4]. Therefore its length is 4.

Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
Explanation: The longest consecutive sequence is [0,1,2,3,4,5,6,7,8]
*/

/*
APPROACH:
I put every number into a hash set for O(1) lookups, then for each number I check whether it's the
start of a sequence, i.e., whether num-1 is missing from the set. If it is a start, I count upward
(num+1, num+2, ...) as long as consecutive numbers exist in the set, tracking the longest run found.
Because I only expand from true sequence starts, each number is visited a bounded number of times
overall, which keeps the algorithm O(n) despite the nested-looking loop.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

This is a classic problem that demonstrates intelligent use of hash sets.

NAIVE APPROACH: Sort and count
- Sort array: O(n log n)
- Scan linearly counting consecutive runs
- Time: O(n log n) - violates O(n) constraint!

OPTIMAL APPROACH: Hash Set Intelligence
The key insight: We only need to start counting from the BEGINNING of a sequence.

TRICK:
For number 'x', it's the start of a sequence if (x-1) doesn't exist in the array.
Example: [100, 4, 200, 1, 3, 2]
- When we see 1: check if 0 exists → NO, so 1 is a sequence start
- When we see 2: check if 1 exists → YES, so 2 is NOT a start (skip it)
- When we see 3: check if 2 exists → YES, skip
- When we see 4: check if 3 exists → YES, skip

ALGORITHM:
1. Put all numbers in unordered_set for O(1) lookup
2. For each number:
   - If (number - 1) exists, skip (not a sequence start)
   - Else, count consecutive numbers: number, number+1, number+2...
3. Track maximum length

TIME COMPLEXITY:
- Though nested loop appears O(n²), the inner while loop only runs for sequence starts
- Each number is visited at most twice (once in outer loop, once in inner counting)
- Total: O(n)

SPACE: O(n) for the hash set
*/

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        // Put all numbers in set for O(1) lookup
        unordered_set<int> numSet(nums.begin(), nums.end());
        
        int maxLength = 0;
        
        for (int num : numSet) {
            // Only start counting if this is the beginning of a sequence
            // i.e., (num - 1) doesn't exist
            if (numSet.count(num - 1) == 0) {
                int currentNum = num;
                int currentLength = 1;
                
                // Count consecutive numbers
                while (numSet.count(currentNum + 1)) {
                    currentNum++;
                    currentLength++;
                }
                
                maxLength = max(maxLength, currentLength);
            }
        }
        
        return maxLength;
    }
    
    // Alternative: Sorting approach (O(n log n) - not optimal but simpler)
    int longestConsecutiveSort(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        sort(nums.begin(), nums.end());
        
        int maxLength = 1;
        int currentLength = 1;
        
        for (int i = 1; i < nums.size(); i++) {
            // Skip duplicates
            if (nums[i] == nums[i-1]) {
                continue;
            }
            
            // Consecutive
            if (nums[i] == nums[i-1] + 1) {
                currentLength++;
            } else {
                // Sequence broken
                maxLength = max(maxLength, currentLength);
                currentLength = 1;
            }
        }
        
        return max(maxLength, currentLength);
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> nums1 = {100, 4, 200, 1, 3, 2};
    cout << "Test 1: " << sol.longestConsecutive(nums1) << endl;
    // Expected: 4 (sequence: 1,2,3,4)
    
    // Test Case 2
    vector<int> nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    cout << "Test 2: " << sol.longestConsecutive(nums2) << endl;
    // Expected: 9 (sequence: 0,1,2,3,4,5,6,7,8)
    
    // Test Case 3 - Empty array
    vector<int> nums3 = {};
    cout << "Test 3: " << sol.longestConsecutive(nums3) << endl;
    // Expected: 0
    
    // Test Case 4 - Single element
    vector<int> nums4 = {1};
    cout << "Test 4: " << sol.longestConsecutive(nums4) << endl;
    // Expected: 1
    
    // Test Case 5 - No consecutive
    vector<int> nums5 = {1, 3, 5, 7, 9};
    cout << "Test 5: " << sol.longestConsecutive(nums5) << endl;
    // Expected: 1
    
    // Test Case 6 - All consecutive
    vector<int> nums6 = {5, 4, 3, 2, 1};
    cout << "Test 6: " << sol.longestConsecutive(nums6) << endl;
    // Expected: 5
    
    // Test Case 7 - With duplicates
    vector<int> nums7 = {1, 2, 0, 1, 2, 3};
    cout << "Test 7: " << sol.longestConsecutive(nums7) << endl;
    // Expected: 4 (sequence: 0,1,2,3)
    
    cout << "\n=== Using Sort Approach ===" << endl;
    vector<int> nums8 = {100, 4, 200, 1, 3, 2};
    cout << "Test 8 (Sort): " << sol.longestConsecutiveSort(nums8) << endl;
    // Expected: 4
    
    return 0;
}

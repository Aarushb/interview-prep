/*
PROBLEM: Trapping Rain Water
DESCRIPTION: Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.
CONSTRAINTS:
- n == height.length
- 1 <= n <= 2 * 10^4
- 0 <= height[i] <= 10^5
EXAMPLE INPUT/OUTPUT:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. 
In this case, 6 units of rain water are being trapped.

Input: height = [4,2,0,3,2,5]
Output: 9
*/

/*
APPROACH:
The water trapped at any position is bounded by the shorter of the tallest bar to its left and to
its right, so I use two pointers moving inward from both ends while tracking left_max and right_max.
Whenever height[left] < height[right], I know the left side's boundary is the limiting one, so I
process and advance the left pointer (and symmetrically for the right); this avoids needing to
precompute both max arrays up front. This greedy two-pointer approach solves the problem in O(n)
time and O(1) space, versus O(n) space for the DP version.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

This is an ADVANCED TWO POINTERS problem that requires deep understanding.

KEY INSIGHT:
Water trapped at position i = min(max_left[i], max_right[i]) - height[i]
- max_left[i] = tallest bar to the left of i
- max_right[i] = tallest bar to the right of i
- Water level is determined by the SHORTER of the two boundaries

APPROACH 1: Brute Force O(n²)
- For each position, scan left and right to find max heights
- Calculate water trapped

APPROACH 2: Dynamic Programming O(n), O(n) space
- Precompute max_left and max_right arrays
- Then calculate water for each position

APPROACH 3: Two Pointers O(n), O(1) space ⭐ OPTIMAL
The key insight:
- We don't need to know BOTH max_left and max_right at the same time
- We only need to know which one is SMALLER
- If left_max < right_max, we KNOW water level is determined by left_max
- Vice versa

ALGORITHM:
1. Initialize left = 0, right = n - 1
2. Track left_max and right_max
3. While left < right:
   - If height[left] < height[right]:
     - Water at left is determined by left_max (we know right side is taller)
     - Update left_max and calculate water
     - Move left++
   - Else:
     - Water at right is determined by right_max
     - Update right_max and calculate water
     - Move right--

WHY THIS WORKS:
- At each step, we process the side with smaller height
- For that side, we KNOW the other side is taller, so it won't limit water level
- Water level is determined by the max on the same side

TRICK:
Move the pointer with SMALLER height. The water level for that position is guaranteed
to be determined by the max on its side (not the other side).
*/

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) return 0;
        
        int left = 0, right = height.size() - 1;
        int left_max = 0, right_max = 0;
        int water = 0;
        
        while (left < right) {
            if (height[left] < height[right]) {
                // Process left side
                if (height[left] >= left_max) {
                    left_max = height[left];  // Update max, no water trapped
                } else {
                    water += left_max - height[left];  // Trap water
                }
                left++;
            } else {
                // Process right side
                if (height[right] >= right_max) {
                    right_max = height[right];  // Update max, no water trapped
                } else {
                    water += right_max - height[right];  // Trap water
                }
                right--;
            }
        }
        
        return water;
    }
    
    // Alternative cleaner version
    int trapClean(vector<int>& height) {
        int left = 0, right = height.size() - 1;
        int left_max = height[left], right_max = height[right];
        int water = 0;
        
        while (left < right) {
            if (left_max < right_max) {
                left++;
                left_max = max(left_max, height[left]);
                water += left_max - height[left];
            } else {
                right--;
                right_max = max(right_max, height[right]);
                water += right_max - height[right];
            }
        }
        
        return water;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> height1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Test 1: " << sol.trap(height1) << endl;
    // Expected: 6
    
    // Test Case 2
    vector<int> height2 = {4, 2, 0, 3, 2, 5};
    cout << "Test 2: " << sol.trap(height2) << endl;
    // Expected: 9
    
    // Test Case 3 - No water trapped
    vector<int> height3 = {1, 2, 3, 4, 5};
    cout << "Test 3: " << sol.trap(height3) << endl;
    // Expected: 0
    
    // Test Case 4 - Descending
    vector<int> height4 = {5, 4, 3, 2, 1};
    cout << "Test 4: " << sol.trap(height4) << endl;
    // Expected: 0
    
    // Test Case 5 - Valley
    vector<int> height5 = {3, 0, 0, 2, 0, 4};
    cout << "Test 5: " << sol.trap(height5) << endl;
    // Expected: 10
    
    // Test Case 6 - Single valley
    vector<int> height6 = {5, 2, 1, 2, 1, 5};
    cout << "Test 6: " << sol.trap(height6) << endl;
    // Expected: 14
    
    return 0;
}

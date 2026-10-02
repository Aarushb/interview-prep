/*
PROBLEM: Container With Most Water
DESCRIPTION: You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).
Find two lines that together with the x-axis form a container, such that the container contains the most water.
Return the maximum amount of water a container can store.
Notice that you may not slant the container.
CONSTRAINTS:
- n == height.length
- 2 <= n <= 10^5
- 0 <= height[i] <= 10^4
EXAMPLE INPUT/OUTPUT:
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The max area is between index 1 (height=8) and index 8 (height=7).
Area = min(8, 7) * (8 - 1) = 7 * 7 = 49

Input: height = [1,1]
Output: 1
*/

/*
APPROACH:
I start with the widest possible container, pointers at both ends of the array, since width is
maximized there and can only shrink as pointers move inward. At each step I compute the area using
the shorter of the two lines and always move the pointer at the shorter line inward, because keeping
it fixed could never produce a larger area than what's already been checked. This greedy elimination
guarantees the optimal container is found in a single O(n) pass.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

This is a classic GREEDY + TWO POINTERS problem.

BRUTE FORCE:
- Try all pairs of lines
- For each pair, calculate area = min(height[i], height[j]) * (j - i)
- Track maximum
- Time: O(n²), Space: O(1)

OPTIMAL APPROACH (Two Pointers):
Start with widest container (leftmost and rightmost lines):
- Initialize left = 0, right = n - 1
- Calculate area with current pointers
- Move the pointer pointing to SHORTER line inward
- Why? Because area is limited by shorter line, and moving it gives chance for taller line
- Keep tracking maximum area
- Time: O(n), Space: O(1)

WHY MOVE SHORTER LINE?
- Area = min(height[left], height[right]) * (right - left)
- Width decreases as we move pointers inward
- To compensate, we need taller lines
- Moving the taller line pointer can ONLY decrease area (same or shorter height, less width)
- Moving the shorter line pointer gives CHANCE to increase area (potentially taller line)

PROOF OF CORRECTNESS:
- We start with maximum width
- At each step, we eliminate the configurations that CAN'T be better than current
- If height[left] < height[right], any container using left with indices between left and right
  will have: same or less height (height[left]) AND less width → can't be better
- So it's safe to eliminate left and move to left + 1

TRICK:
Always move the pointer pointing to the SHORTER line.
This is a greedy choice that guarantees we don't miss the optimal solution.
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int maxWater = 0;
        
        while (left < right) {
            // Calculate current area
            int width = right - left;
            int currentHeight = min(height[left], height[right]);
            int area = width * currentHeight;
            
            maxWater = max(maxWater, area);
            
            // Move pointer pointing to shorter line
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return maxWater;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> height1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    cout << "Test 1: " << sol.maxArea(height1) << endl;
    // Expected: 49
    
    // Test Case 2
    vector<int> height2 = {1, 1};
    cout << "Test 2: " << sol.maxArea(height2) << endl;
    // Expected: 1
    
    // Test Case 3
    vector<int> height3 = {4, 3, 2, 1, 4};
    cout << "Test 3: " << sol.maxArea(height3) << endl;
    // Expected: 16 (between index 0 and 4)
    
    // Test Case 4
    vector<int> height4 = {1, 2, 1};
    cout << "Test 4: " << sol.maxArea(height4) << endl;
    // Expected: 2 (between index 0 and 2)
    
    // Test Case 5 - All same height
    vector<int> height5 = {5, 5, 5, 5};
    cout << "Test 5: " << sol.maxArea(height5) << endl;
    // Expected: 15 (5 * 3)
    
    return 0;
}

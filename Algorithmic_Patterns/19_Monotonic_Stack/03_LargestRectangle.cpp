/*
PROBLEM: Largest Rectangle in Histogram
DESCRIPTION: Given an array of integers heights representing the histogram's bar height where
the width of each bar is 1, return the area of the largest rectangle in the histogram.
CONSTRAINTS:
- 1 <= heights.length <= 10^5
- 0 <= heights[i] <= 10^4
EXAMPLE INPUT/OUTPUT:
Input: heights = [2,1,5,6,2,3] -> Output: 10
Input: heights = [2,4] -> Output: 4
*/

/*
APPROACH:
For every bar, the largest rectangle that uses that bar as its limiting (shortest) height
extends as far left and right as possible while staying >= that bar's height. We find those
boundaries efficiently with an increasing monotonic stack of indices: when we encounter a bar
shorter than the one on top of the stack, that shorter bar is the right boundary for the
popped bar, and the new stack top (after popping) is the left boundary. We append a sentinel
height of 0 at the end to force-flush every remaining bar on the stack. This computes the
answer in a single O(n) pass instead of the O(n^2) brute force of checking every (left, right)
pair.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st; // increasing stack of indices
        int maxArea = 0;
        int n = heights.size();

        for (int i = 0; i <= n; i++) {
            int curHeight = (i == n) ? 0 : heights[i]; // sentinel flushes the stack at the end
            while (!st.empty() && heights[st.top()] > curHeight) {
                int height = heights[st.top()];
                st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            st.push(i);
        }
        return maxArea;
    }
};

int main() {
    Solution sol;

    vector<int> heights1 = {2, 1, 5, 6, 2, 3};
    cout << "Input: [2,1,5,6,2,3] -> Output: " << sol.largestRectangleArea(heights1)
         << " (Expected: 10)" << endl;

    vector<int> heights2 = {2, 4};
    cout << "Input: [2,4] -> Output: " << sol.largestRectangleArea(heights2)
         << " (Expected: 4)" << endl;

    return 0;
}

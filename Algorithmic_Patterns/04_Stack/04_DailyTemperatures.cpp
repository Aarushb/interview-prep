/*
PROBLEM: Daily Temperatures
DESCRIPTION: Given an array of integers temperatures represents the daily temperatures, return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature. If there is no future day for which this is possible, keep answer[i] == 0 instead.
CONSTRAINTS:
- 1 <= temperatures.length <= 10^5
- 30 <= temperatures[i] <= 100
EXAMPLE INPUT/OUTPUT:
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]

Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]

Input: temperatures = [30,60,90]
Output: [1,1,0]
*/

/*
APPROACH:
This is a "next greater element" problem, which is the classic signal for a monotonic stack. Instead of
storing temperatures, I store indices in a stack that I keep in decreasing-temperature order from bottom
to top. As I scan each day, I pop every index off the stack whose temperature is lower than today's —
each pop means "today is the answer for that earlier day," so I compute the day difference and record it
in the result array, then push today's index. Any indices left in the stack at the end never find a warmer
day, so they correctly stay at their default 0. Because each index is pushed and popped at most once, the
whole algorithm is O(n) despite the nested-looking while loop.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

Classic MONOTONIC STACK problem (next greater element variant).

BRUTE FORCE:
- For each day, scan forward to find warmer day
- TIME: O(n²), SPACE: O(1)

OPTIMAL (Monotonic Decreasing Stack):
- Use stack to store indices of days waiting for warmer temperature
- Stack maintains decreasing temperature order
- When we find warmer day, pop all cooler days and update their answer
- TIME: O(n), SPACE: O(n)

WHY O(n)?
Each element is pushed and popped at most once → 2n operations = O(n)

ALGORITHM:
1. Initialize result array with 0s
2. Use stack to store indices
3. For each day i:
   - While stack not empty AND current temp > temp at stack top:
     * Found answer for day at stack top
     * Calculate days difference
     * Pop from stack
   - Push current day index to stack
4. Return result

TRICK:
Store INDICES in stack, not temperatures!
This allows us to calculate the number of days difference.

MONOTONIC STACK PROPERTY:
Stack maintains temperatures in decreasing order (from bottom to top).
When we encounter warmer temperature, we pop all cooler ones.
*/

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> result(n, 0);
        stack<int> st;  // Store indices
        
        for (int i = 0; i < n; i++) {
            // Pop all days with cooler temperature
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int prevDay = st.top();
                st.pop();
                result[prevDay] = i - prevDay;
            }
            
            // Push current day
            st.push(i);
        }
        
        // Days remaining in stack have no warmer future day (already 0)
        return result;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> temps1 = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> result1 = sol.dailyTemperatures(temps1);
    cout << "Test 1: ";
    for (int x : result1) cout << x << " ";
    cout << endl;
    // Expected: 1 1 4 2 1 1 0 0
    
    // Test Case 2
    vector<int> temps2 = {30, 40, 50, 60};
    vector<int> result2 = sol.dailyTemperatures(temps2);
    cout << "Test 2: ";
    for (int x : result2) cout << x << " ";
    cout << endl;
    // Expected: 1 1 1 0
    
    // Test Case 3
    vector<int> temps3 = {30, 60, 90};
    vector<int> result3 = sol.dailyTemperatures(temps3);
    cout << "Test 3: ";
    for (int x : result3) cout << x << " ";
    cout << endl;
    // Expected: 1 1 0
    
    // Test Case 4 - Decreasing
    vector<int> temps4 = {100, 90, 80, 70};
    vector<int> result4 = sol.dailyTemperatures(temps4);
    cout << "Test 4: ";
    for (int x : result4) cout << x << " ";
    cout << endl;
    // Expected: 0 0 0 0
    
    return 0;
}

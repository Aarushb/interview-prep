/*
PROBLEM: Best Time to Buy and Sell Stock
DESCRIPTION: You are given an array prices where prices[i] is the price of a given stock on the ith day.
You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
CONSTRAINTS:
- 1 <= prices.length <= 10^5
- 0 <= prices[i] <= 10^4
EXAMPLE INPUT/OUTPUT:
Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: No profit possible.
*/

/*
APPROACH:
I'd frame this as an implicit sliding window: I want to buy low and sell high, but the sell must happen
after the buy. So I walk the array once, keeping track of the minimum price seen so far — that's my
effective "left edge" of the window. At every day I check what profit I'd get by selling today against
that running minimum, and keep the best one seen. Because I always update the minimum after computing the
day's profit, I never accidentally buy and sell on the same day. This gives O(n) time and O(1) space with
a single pass, no nested loops needed.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

This is the SIMPLEST sliding window problem - actually a ONE PASS scan.

NAIVE APPROACH:
- Try all pairs (buy day, sell day) where buy < sell
- Track maximum profit
- Time: O(n²), Space: O(1)

OPTIMAL APPROACH (Sliding Window / One Pass):
Key insight: To maximize profit, buy at minimum price and sell at maximum price AFTER that.
- Track minimum price seen so far
- For each day, calculate profit if we sell today (price today - min price)
- Update maximum profit
- Time: O(n), Space: O(1)

WHY THIS IS SLIDING WINDOW:
- Window expands to the right (current price)
- Window left boundary is the minimum price so far
- We're finding maximum difference in a valid range

ALGORITHM:
1. Initialize minPrice = infinity, maxProfit = 0
2. For each price:
   a. Calculate potential profit = price - minPrice
   b. Update maxProfit if this profit is better
   c. Update minPrice if current price is lower
3. Return maxProfit

TRICK:
Always update minPrice AFTER checking profit, not before.
This ensures we don't buy and sell on the same day.
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;
        
        for (int price : prices) {
            // Calculate profit if we sell today
            maxProfit = max(maxProfit, price - minPrice);
            
            // Update minimum price seen so far
            minPrice = min(minPrice, price);
        }
        
        return maxProfit;
    }
    
    // Alternative: More explicit sliding window style
    int maxProfitWindow(vector<int>& prices) {
        int left = 0;  // Buy day
        int maxProfit = 0;
        
        for (int right = 1; right < prices.size(); right++) {
            // If price goes down, move buy day forward
            if (prices[right] < prices[left]) {
                left = right;
            } else {
                // Calculate profit and update max
                maxProfit = max(maxProfit, prices[right] - prices[left]);
            }
        }
        
        return maxProfit;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    cout << "Test 1: " << sol.maxProfit(prices1) << endl;
    // Expected: 5
    
    // Test Case 2
    vector<int> prices2 = {7, 6, 4, 3, 1};
    cout << "Test 2: " << sol.maxProfit(prices2) << endl;
    // Expected: 0
    
    // Test Case 3 - Single price
    vector<int> prices3 = {1};
    cout << "Test 3: " << sol.maxProfit(prices3) << endl;
    // Expected: 0
    
    // Test Case 4 - Best profit at end
    vector<int> prices4 = {1, 2, 3, 4, 5};
    cout << "Test 4: " << sol.maxProfit(prices4) << endl;
    // Expected: 4
    
    // Test Case 5 - Multiple valleys
    vector<int> prices5 = {3, 3, 5, 0, 0, 3, 1, 4};
    cout << "Test 5: " << sol.maxProfit(prices5) << endl;
    // Expected: 4 (buy at 0, sell at 4)
    
    return 0;
}

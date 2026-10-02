/*
PROBLEM: Best Time to Buy and Sell Stock with Cooldown
DESCRIPTION: You are given an array prices where prices[i] is the price of a given stock on the
i-th day. Find the maximum profit you can achieve. You may complete as many transactions as you
like (buy one and sell one share of the stock multiple times) with the following restrictions:
after you sell your stock, you cannot buy stock on the next day (cooldown one day). You may not
engage in multiple transactions simultaneously (you must sell the stock before you buy again).
CONSTRAINTS: 1 <= prices.length <= 5000. 0 <= prices[i] <= 1000.
EXAMPLE INPUT/OUTPUT:
  Input: prices = [1,2,3,0,2] -> Output: 3 (buy=1, sell=2, cooldown, buy=0, sell=2 => (2-1)+(2-0)=3)
  Input: prices = [1]         -> Output: 0
*/

/*
APPROACH:
This is state-machine DP, a 2D DP where one dimension is the day and the other is a small set of
discrete states: HOLD (currently holding a stock), SOLD (just sold today, must cool down
tomorrow), and REST (not holding, free to buy). Transitions per day: hold[i] = max(hold[i-1],
rest[i-1] - price[i]) (keep holding, or buy today from a resting state); sold[i] = hold[i-1] +
price[i] (sell what we held); rest[i] = max(rest[i-1], sold[i-1]) (stay resting, or just finished
a cooldown after selling). The answer is the max of sold/rest on the last day (we'd never want to
end while still holding). Since each day only depends on the previous day, we roll the three
states into O(1) extra space instead of a full table.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n <= 1) return 0;

        // hold: max profit while currently holding a stock
        // sold: max profit having just sold today (must cool down tomorrow)
        // rest: max profit while not holding and not in cooldown (free to buy)
        long long hold = LLONG_MIN, sold = 0, rest = 0;

        for (int i = 0; i < n; i++) {
            long long prevHold = hold, prevSold = sold, prevRest = rest;
            hold = max(prevHold, prevRest - prices[i]);
            sold = prevHold + prices[i];
            rest = max(prevRest, prevSold);
        }
        return (int)max(sold, rest);
    }
};

int main() {
    Solution sol;

    vector<int> p1 = {1, 2, 3, 0, 2};
    cout << sol.maxProfit(p1) << endl; // expected 3

    vector<int> p2 = {1};
    cout << sol.maxProfit(p2) << endl; // expected 0

    vector<int> p3 = {1, 2, 4};
    cout << sol.maxProfit(p3) << endl; // expected 3

    vector<int> p4 = {6, 1, 3, 2, 4, 7};
    cout << sol.maxProfit(p4) << endl; // expected 6

    return 0;
}

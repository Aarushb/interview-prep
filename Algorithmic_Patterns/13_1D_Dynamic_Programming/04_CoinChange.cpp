/*
PROBLEM: Coin Change (LeetCode 322)
DESCRIPTION: You are given an integer array coins representing coins of different denominations
and an integer amount representing a total amount of money. Return the fewest number of coins
needed to make up that amount. If that amount of money cannot be made up by any combination of
the coins, return -1. You may assume an unlimited supply of each coin denomination.
CONSTRAINTS: 1 <= coins.length <= 12, 1 <= coins[i] <= 2^31 - 1, 0 <= amount <= 10^4.
EXAMPLE INPUT/OUTPUT:
  coins = [1,2,5], amount = 11 -> Output: 3  (11 = 5 + 5 + 1)
  coins = [2], amount = 3 -> Output: -1  (impossible with only 2's)
*/

/*
APPROACH:
Let dp[a] = minimum number of coins needed to make amount a, with dp[0] = 0 as the base case
(zero coins needed to make amount 0). For each amount a from 1 to target, we try every coin
denomination c <= a and take dp[a] = min(dp[a], dp[a - c] + 1) — this is the "unbounded
knapsack" pattern since each coin can be reused unlimited times, so the loop order is amount
outer, coin inner (using the coin doesn't remove it from future consideration). Unreachable
amounts are initialized to a sentinel "infinity" (amount+1, since that many coins can never
actually be needed) so any addition doesn't overflow and unreached amounts are easy to detect.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int INF = amount + 1; // sentinel: more coins than could ever be needed
        vector<int> dp(amount + 1, INF);
        dp[0] = 0;

        for (int a = 1; a <= amount; a++) {
            for (int c : coins) {
                if (c <= a) {
                    dp[a] = min(dp[a], dp[a - c] + 1);
                }
            }
        }

        return dp[amount] == INF ? -1 : dp[amount];
    }
};

int main() {
    Solution sol;

    vector<int> coins1 = {1, 2, 5};
    cout << "Test 1: " << sol.coinChange(coins1, 11) << " (expected 3)" << endl;

    vector<int> coins2 = {2};
    cout << "Test 2: " << sol.coinChange(coins2, 3) << " (expected -1)" << endl;

    vector<int> coins3 = {1};
    cout << "Test 3: " << sol.coinChange(coins3, 0) << " (expected 0)" << endl;

    vector<int> coins4 = {1, 3, 4, 5};
    cout << "Test 4: " << sol.coinChange(coins4, 7) << " (expected 2, i.e. 3+4)" << endl;

    return 0;
}

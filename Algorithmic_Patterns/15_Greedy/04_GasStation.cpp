/*
PROBLEM: Gas Station
DESCRIPTION: There are n gas stations along a circular route, where the amount of gas at station
i is gas[i]. You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from
station i to its next station (i + 1). You begin the journey with an empty tank at one of the gas
stations. Given two integer arrays gas and cost, return the starting gas station's index if you
can travel around the circuit once in the clockwise direction, otherwise return -1. If there
exists a solution, it is guaranteed to be unique.
CONSTRAINTS: n == gas.length == cost.length. 1 <= n <= 10^5. 0 <= gas[i], cost[i] <= 10^4.
EXAMPLE INPUT/OUTPUT:
  Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2] -> Output: 3
  Input: gas = [2,3,4], cost = [3,4,3]         -> Output: -1
*/

/*
APPROACH:
Two greedy facts combine to solve this in one pass. First, a feasible starting point exists iff
total gas >= total cost (sum(gas) - sum(cost) >= 0) — if the total deficit is negative, no start
can work. Second, given that a solution exists, we can find it greedily: track a running tank
balance as we simulate starting from index 0; whenever the running balance goes negative at some
index i, no station between the current candidate start and i could have been a valid start
either (starting anywhere in that stretch only makes the deficit at i worse or equal, since we'd
arrive at i with even less surplus), so we discard all of them and set the candidate start to
i + 1, resetting the running balance to 0. This exchange argument means a single linear scan
finds the unique answer without ever restarting the simulation from scratch.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        long long totalBalance = 0; // sum(gas) - sum(cost) over the whole circuit
        long long tank = 0;          // running balance since the current candidate start
        int start = 0;

        for (int i = 0; i < n; i++) {
            int diff = gas[i] - cost[i];
            totalBalance += diff;
            tank += diff;
            if (tank < 0) {
                start = i + 1; // this stretch can't be, or contain, a valid start
                tank = 0;
            }
        }
        return totalBalance >= 0 ? start : -1;
    }
};

int main() {
    Solution sol;

    vector<int> gas1 = {1, 2, 3, 4, 5}, cost1 = {3, 4, 5, 1, 2};
    cout << sol.canCompleteCircuit(gas1, cost1) << endl; // expected 3

    vector<int> gas2 = {2, 3, 4}, cost2 = {3, 4, 3};
    cout << sol.canCompleteCircuit(gas2, cost2) << endl; // expected -1

    vector<int> gas3 = {5, 1, 2, 3, 4}, cost3 = {4, 4, 1, 5, 1};
    cout << sol.canCompleteCircuit(gas3, cost3) << endl; // expected 4

    return 0;
}

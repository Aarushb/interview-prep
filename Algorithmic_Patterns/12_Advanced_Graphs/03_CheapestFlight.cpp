/*
PROBLEM: Cheapest Flights Within K Stops (LeetCode 787)
DESCRIPTION: There are n cities connected by some number of flights. You are given an array
flights where flights[i] = [fromi, toi, pricei] indicates a flight from city fromi to city toi
with cost pricei. You are also given three integers src, dst, and k, return the cheapest price
from src to dst with at most k stops. If there is no such route, return -1.
CONSTRAINTS: 1 <= n <= 100, 0 <= flights.length <= (n * (n-1) / 2), flights[i].length == 3,
0 <= fromi, toi < n, fromi != toi, 1 <= pricei <= 10^4, 0 <= src, dst, k < n, src != dst.
EXAMPLE INPUT/OUTPUT:
  n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
  Output: 700
  (0->1->3 costs 100+600=700 with 1 stop; 0->1->2->3 costs 400 but uses 2 stops, exceeding k=1)
*/

/*
APPROACH:
Plain Dijkstra doesn't work here because its greedy "finalize on pop" assumption breaks when a
path with more edges (more stops) but a bounded stop count can be cheaper than a "globally
shortest" path that uses too many stops. Instead we use a Bellman-Ford-style relaxation: run
exactly k+1 rounds (k stops means at most k+1 edges), and in each round relax every edge using
a snapshot of the previous round's costs (a copy, so we don't chain multiple relaxations within
the same round, which would effectively allow unlimited stops in one pass). This guarantees
each round adds at most one more edge to any path, respecting the stop limit exactly.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<int> cost(n, INT_MAX);
        cost[src] = 0;

        // k stops allowed => at most k+1 edges => k+1 relaxation rounds
        for (int round = 0; round <= k; round++) {
            vector<int> next = cost; // snapshot: only use costs from previous round
            for (auto& f : flights) {
                int u = f[0], v = f[1], w = f[2];
                if (cost[u] == INT_MAX) continue;
                if (cost[u] + w < next[v]) {
                    next[v] = cost[u] + w;
                }
            }
            cost = next;
        }

        return cost[dst] == INT_MAX ? -1 : cost[dst];
    }
};

int main() {
    Solution sol;

    vector<vector<int>> flights1 = {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
    cout << "Test 1: " << sol.findCheapestPrice(4, flights1, 0, 3, 1) << " (expected 700)" << endl;

    vector<vector<int>> flights2 = {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
    cout << "Test 2: " << sol.findCheapestPrice(4, flights2, 0, 3, 2) << " (expected 400)" << endl;

    vector<vector<int>> flights3 = {{0,1,100},{1,2,100},{0,2,500}};
    cout << "Test 3: " << sol.findCheapestPrice(3, flights3, 0, 2, 0) << " (expected 500)" << endl;

    vector<vector<int>> flights4 = {{0,1,100}};
    cout << "Test 4: " << sol.findCheapestPrice(3, flights4, 0, 2, 5) << " (expected -1, unreachable)" << endl;

    return 0;
}

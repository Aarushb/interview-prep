/*
PROBLEM: Network Delay Time (LeetCode 743)
DESCRIPTION: You are given a network of n nodes, labeled from 1 to n. You are also given times,
a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node,
vi is the target node, and wi is the time it takes for a signal to travel from source to target.
We will send a signal from a given node k. Return the minimum time it takes for all the n nodes
to receive the signal. If it is impossible for all n nodes to receive the signal, return -1.
CONSTRAINTS: 1 <= k <= n <= 100, 1 <= times.length <= 6000, times[i].length == 3,
1 <= ui, vi <= n, ui != vi, 0 <= wi <= 100, all pairs (ui, vi) are unique.
EXAMPLE INPUT/OUTPUT:
  times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
  Output: 2
  (signal reaches node 1 and 3 at time 1, node 4 at time 2; max = 2)
*/

/*
APPROACH:
This is a direct application of Dijkstra's algorithm: the "time for all nodes to receive the
signal" is just the maximum of the shortest-path distances from source k to every node. Build
an adjacency list, run Dijkstra from k with a min-priority-queue on (time, node), and track the
maximum finite distance found. If any node remains unreached (distance still infinity) after
the algorithm finishes, return -1 since not all nodes can receive the signal.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int,int>>> adj(n + 1); // 1-indexed nodes
        for (auto& t : times) {
            adj[t[0]].push_back({t[1], t[2]});
        }

        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        pq.push({0, k});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;
            for (auto& [v, w] : adj[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        int maxTime = 0;
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INT_MAX) return -1; // unreachable node
            maxTime = max(maxTime, dist[i]);
        }
        return maxTime;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> times1 = {{2,1,1},{2,3,1},{3,4,1}};
    cout << "Test 1: " << sol.networkDelayTime(times1, 4, 2) << " (expected 2)" << endl;

    vector<vector<int>> times2 = {{1,2,1}};
    cout << "Test 2: " << sol.networkDelayTime(times2, 2, 1) << " (expected 1)" << endl;

    vector<vector<int>> times3 = {{1,2,1}};
    cout << "Test 3: " << sol.networkDelayTime(times3, 2, 2) << " (expected -1, unreachable)" << endl;

    return 0;
}

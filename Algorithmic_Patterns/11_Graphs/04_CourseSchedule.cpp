/*
PROBLEM: Course Schedule
DESCRIPTION: There are numCourses courses labeled 0 to numCourses - 1. You are given an array
prerequisites where prerequisites[i] = [a_i, b_i] indicates that you must take course b_i first
if you want to take course a_i. Return true if you can finish all courses, otherwise false.
CONSTRAINTS: 1 <= numCourses <= 2000; 0 <= prerequisites.length <= 5000;
prerequisites[i].length == 2; 0 <= a_i, b_i < numCourses; all pairs prerequisites[i] are distinct.
EXAMPLE INPUT/OUTPUT: numCourses = 2, prerequisites = [[1,0]] -> true (take 0, then 1);
numCourses = 2, prerequisites = [[1,0],[0,1]] -> false (cycle: 0 needs 1, 1 needs 0).
*/

/*
APPROACH:
Model courses as a directed graph where an edge b -> a means "b must be taken before a," and
compute each course's in-degree (number of unmet prerequisites). Run Kahn's algorithm: start a
queue with every course that has in-degree 0 (no prerequisites), and repeatedly dequeue a course,
"complete" it, and decrement the in-degree of each course that depended on it, enqueueing any
that drop to 0. If every course eventually gets dequeued, all prerequisites could be satisfied in
some order; if some courses never reach in-degree 0, they're stuck in a cycle and can never be
scheduled, so the answer is false.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites){
        vector<vector<int>> adj(numCourses);
        vector<int> indeg(numCourses,0);
        for(auto& p: prerequisites){ adj[p[1]].push_back(p[0]); indeg[p[0]]++; }
        queue<int> q; for(int i=0;i<numCourses;i++) if(indeg[i]==0) q.push(i);
        int taken=0;
        while(!q.empty()){
            int u=q.front(); q.pop(); taken++;
            for(int v: adj[u]) if(--indeg[v]==0) q.push(v);
        }
        return taken==numCourses;
    }
};

int main(){
    Solution sol;
    vector<vector<int>> pre1={{1,0}}; // possible
    cout << boolalpha << sol.canFinish(2, pre1) << "\n";
    vector<vector<int>> pre2={{1,0},{0,1}}; // cycle
    cout << sol.canFinish(2, pre2) << "\n";
    return 0;
}

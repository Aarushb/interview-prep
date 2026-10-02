/*
PROBLEM: Graph Valid Tree
DESCRIPTION: Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is
a pair of nodes), write a function to check whether these edges form a valid tree, i.e. the
graph is connected and contains no cycles.
CONSTRAINTS: 1 <= n <= 2000; 0 <= edges.length <= 5000; edges[i].length == 2;
0 <= a_i, b_i < n; a_i != b_i; there are no self-loops or repeated edges.
EXAMPLE INPUT/OUTPUT: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]] -> true;
n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]] -> false (cycle);
n = 4, edges = [[0,1],[2,3]] -> false (disconnected).
*/

/*
APPROACH:
A graph with n nodes is a valid tree exactly when it is connected and acyclic, which is
equivalent (for a simple undirected graph) to having exactly n - 1 edges *and* no cycles among
them — so first reject immediately if the edge count isn't n - 1. Then use a Union-Find (Disjoint
Set Union) structure: process each edge and try to union its two endpoints; if the two endpoints
are already in the same set, that edge would create a cycle, so return false. If every edge
unions two previously-separate components without conflict, combined with the correct edge count,
the graph must be a single connected acyclic component, i.e. a valid tree.
*/

#include <bits/stdc++.h>
using namespace std;

class DSU{
    vector<int> p, r;
public:
    DSU(int n): p(n), r(n,0){ iota(p.begin(), p.end(), 0); }
    int find(int x){ return p[x]==x? x : p[x]=find(p[x]); }
    bool unite(int a,int b){ a=find(a); b=find(b); if(a==b) return false; if(r[a]<r[b]) swap(a,b); p[b]=a; if(r[a]==r[b]) r[a]++; return true; }
};

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges){
        if((int)edges.size()!=n-1) return false;
        DSU dsu(n);
        for(auto& e: edges){ if(!dsu.unite(e[0], e[1])) return false; }
        return true;
    }
};

int main(){
    Solution sol;
    vector<vector<int>> e1={{0,1},{0,2},{0,3},{1,4}}; // tree
    cout << boolalpha << sol.validTree(5, e1) << "\n";
    vector<vector<int>> e2={{0,1},{1,2},{2,3},{1,3},{1,4}}; // cycle
    cout << sol.validTree(5, e2) << "\n";
    vector<vector<int>> e3={{0,1},{2,3}}; // disconnected
    cout << sol.validTree(4, e3) << "\n";
    return 0;
}

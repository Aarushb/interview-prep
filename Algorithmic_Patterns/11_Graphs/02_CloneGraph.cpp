/*
PROBLEM: Clone Graph
DESCRIPTION: Given a reference of a node in a connected undirected graph, return a deep copy
(clone) of the graph. Each node contains a value and a list of its neighbors.
CONSTRAINTS: The number of nodes in the graph is in the range [0, 100]; 1 <= Node.val <= 100;
Node.val is unique for each node; there are no repeated edges and no self-loops; the graph is
connected.
EXAMPLE INPUT/OUTPUT: node 1 with neighbors [2,4], node 2 with neighbors [1,3], node 3 with
neighbors [2,4], node 4 with neighbors [1,3] -> a structurally identical graph of newly
allocated nodes.
*/

/*
APPROACH:
Use BFS starting from the given node, and maintain a hashmap from original node pointers to
their cloned counterparts. Clone the start node first and enqueue it; for every node dequeued,
walk its original neighbors, cloning any neighbor not already in the map (and enqueueing it for
later processing), then wire the clone's neighbor list to point at the (already or newly)
cloned neighbor. Checking the map before allocating is essential — it's what prevents infinite
loops and duplicate clones on a graph with cycles.
*/

#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val; vector<Node*> neighbors;
    Node(): val(0) {}
    Node(int _val): val(_val) {}
};

class Solution {
public:
    Node* cloneGraph(Node* node){
        if(!node) return nullptr;
        unordered_map<Node*, Node*> mp;
        queue<Node*> q; q.push(node);
        mp[node]= new Node(node->val);
        while(!q.empty()){
            Node* cur=q.front(); q.pop();
            for(auto* nei: cur->neighbors){
                if(!mp.count(nei)){
                    mp[nei]=new Node(nei->val);
                    q.push(nei);
                }
                mp[cur]->neighbors.push_back(mp[nei]);
            }
        }
        return mp[node];
    }
};

static Node* buildSimple(){
    Node* n1=new Node(1); Node* n2=new Node(2); Node* n3=new Node(3); Node* n4=new Node(4);
    n1->neighbors={n2,n4}; n2->neighbors={n1,n3}; n3->neighbors={n2,n4}; n4->neighbors={n1,n3};
    return n1;
}

int main(){
    Solution sol; Node* start = buildSimple();
    Node* copy = sol.cloneGraph(start);
    // Print first node and its neighbors to verify
    cout << copy->val << ":";
    for(auto* n: copy->neighbors) cout << n->val << " ";
    cout << "\n";
    return 0;
}

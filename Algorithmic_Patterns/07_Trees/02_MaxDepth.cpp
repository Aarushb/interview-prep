/*
PROBLEM: Maximum Depth of Binary Tree
DESCRIPTION: Given root, return its maximum depth (longest path from root to leaf in nodes).
CONSTRAINTS:
- The number of nodes in the tree is in the range [0, 10^4].
- -100 <= Node.val <= 100
EXAMPLE INPUT/OUTPUT:
Input: [3,9,20,null,null,15,7] -> Output: 3
*/

/*
APPROACH:
Depth naturally decomposes into subproblems: the depth of the tree rooted at a node is 1
plus the larger of its two subtree depths. This is a classic post-order DFS -- compute both
children's answers first, then combine them for the parent. The base case (null node)
returns 0, which cleanly handles both leaves and the empty-tree edge case.
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val; TreeNode* left; TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (!root) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};

TreeNode* simple(const vector<optional<int>>& v) {
    if (v.empty() || !v[0]) return nullptr;
    vector<TreeNode*> n(v.size(), nullptr);
    for (size_t i=0;i<v.size();i++) if (v[i]) n[i]=new TreeNode(*v[i]);
    for (size_t i=0;i<v.size();i++) if (n[i]) {
        size_t l=2*i+1,r=2*i+2; if(l<v.size()) n[i]->left=n[l]; if(r<v.size()) n[i]->right=n[r];
    }
    return n[0];
}

int main() {
    Solution sol;
    cout << sol.maxDepth(simple({3,9,20,{}, {},15,7})) << "\n"; // 3
    cout << sol.maxDepth(simple({1,2})) << "\n"; // 2
    cout << sol.maxDepth(nullptr) << "\n"; // 0
    return 0;
}

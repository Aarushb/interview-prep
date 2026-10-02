/*
PROBLEM: Invert Binary Tree
DESCRIPTION: Given the root of a binary tree, invert the tree and return its root.
CONSTRAINTS:
- The number of nodes in the tree is in the range [0, 100].
- -100 <= Node.val <= 100
EXAMPLE INPUT/OUTPUT:
Input: [4,2,7,1,3,6,9]
Output: [4,7,2,9,6,3,1]
*/

/*
APPROACH:
This is a straightforward tree recursion problem: at each node, swap the left and right
children, then recurse into both subtrees. The base case is a null node, which requires no
work. Pre-order and post-order swap ordering both work here since the swap is local to each
node and doesn't depend on the children having already been inverted.
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val; TreeNode* left; TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;
        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};

TreeNode* build(const vector<optional<int>>& vals) {
    if (vals.empty() || !vals[0].has_value()) return nullptr;
    vector<TreeNode*> nodes(vals.size(), nullptr);
    for (size_t i = 0; i < vals.size(); i++) if (vals[i].has_value()) nodes[i] = new TreeNode(*vals[i]);
    for (size_t i = 0; i < vals.size(); i++) if (nodes[i]) {
        size_t l = 2*i+1, r = 2*i+2;
        if (l < vals.size()) nodes[i]->left = nodes[l];
        if (r < vals.size()) nodes[i]->right = nodes[r];
    }
    return nodes[0];
}

void preorder(TreeNode* root) {
    if (!root) { cout << "null "; return; }
    cout << root->val << ' ';
    preorder(root->left);
    preorder(root->right);
}

int main() {
    Solution sol;
    TreeNode* root = build({4,2,7,1,3,6,9});
    cout << "Preorder before: "; preorder(root); cout << "\n";
    sol.invertTree(root);
    cout << "Preorder after:  "; preorder(root); cout << "\n";
    return 0;
}

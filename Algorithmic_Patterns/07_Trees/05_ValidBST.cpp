/*
PROBLEM: Validate Binary Search Tree
DESCRIPTION: Return true if a binary tree is a valid BST (left < node < right for all nodes).
CONSTRAINTS:
- The number of nodes in the tree is in the range [1, 10^4].
- -2^31 <= Node.val <= 2^31 - 1
EXAMPLE INPUT/OUTPUT:
Input: [2,1,3] -> true
Input: [5,1,4,null,null,3,6] -> false (3 in right subtree of 5 is invalid)
*/

/*
APPROACH:
Comparing a node only to its immediate children is insufficient -- a node deep in a left
subtree could still violate the BST property relative to a much higher ancestor. The fix is
to pass down a valid (lo, hi) range that narrows on every recursive call, so a violation is
caught no matter how deep it occurs. Using long long bounds (LLONG_MIN/LLONG_MAX) avoids overflow
issues when a node's value sits at INT_MIN/INT_MAX -- on platforms where `long` is only 32 bits
(e.g. Windows/LLP64), `long` would be no wider than `int` and this bound trick would silently fail,
so `long long` (guaranteed >= 64 bits) is required for it to be correct everywhere.
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode { int val; TreeNode* left; TreeNode* right; TreeNode(int x):val(x),left(nullptr),right(nullptr){} };

class Solution {
public:
    bool isValidBST(TreeNode* root) { return valid(root, LLONG_MIN, LLONG_MAX); }
private:
    bool valid(TreeNode* n, long long lo, long long hi) {
        if (!n) return true;
        if (n->val <= lo || n->val >= hi) return false;
        return valid(n->left, lo, n->val) && valid(n->right, n->val, hi);
    }
};

TreeNode* build(const vector<optional<int>>& v) {
    if (v.empty() || !v[0]) return nullptr;
    vector<TreeNode*> n(v.size(), nullptr);
    for (size_t i=0;i<v.size();i++) if (v[i]) n[i]=new TreeNode(*v[i]);
    for (size_t i=0;i<v.size();i++) if (n[i]) { size_t l=2*i+1,r=2*i+2; if(l<v.size()) n[i]->left=n[l]; if(r<v.size()) n[i]->right=n[r]; }
    return n[0];
}

int main(){
    Solution sol;
    cout << boolalpha;
    cout << sol.isValidBST(build({2,1,3})) << "\n"; // true
    cout << sol.isValidBST(build({5,1,4,{}, {},3,6})) << "\n"; // false
    cout << sol.isValidBST(nullptr) << "\n"; // true
    return 0;
}

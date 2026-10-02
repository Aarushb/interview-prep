/*
PROBLEM: Same Tree
DESCRIPTION: Given roots p and q, determine if the two binary trees are structurally identical and have the same node values.
CONSTRAINTS:
- The number of nodes in each tree is in the range [0, 100].
- -10^4 <= Node.val <= 10^4
EXAMPLE INPUT/OUTPUT:
Input: p = [1,2,3], q = [1,2,3] -> true
Input: p = [1,2], q = [1,null,2] -> false
*/

/*
APPROACH:
Two trees are identical only if their roots match in both structure and value, so the
recursion mirrors both trees in lockstep. Handle the two base cases first -- both null
(true) and exactly one null (false) -- before comparing values and recursing on both child
pairs. Short-circuiting with && means the moment any mismatch is found the recursion stops
early rather than continuing to walk the rest of the trees.
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode { int val; TreeNode* left; TreeNode* right; TreeNode(int x):val(x),left(nullptr),right(nullptr){} };

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;
        if (!p || !q) return false;
        if (p->val != q->val) return false;
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

TreeNode* build(const vector<optional<int>>& v) {
    if (v.empty() || !v[0]) return nullptr;
    vector<TreeNode*> n(v.size(), nullptr);
    for (size_t i=0;i<v.size();i++) if (v[i]) n[i]=new TreeNode(*v[i]);
    for (size_t i=0;i<v.size();i++) if (n[i]) {
        size_t l=2*i+1,r=2*i+2; if(l<v.size()) n[i]->left=n[l]; if(r<v.size()) n[i]->right=n[r];
    }
    return n[0];
}

int main(){
    Solution sol;
    cout << boolalpha;
    cout << sol.isSameTree(build({1,2,3}), build({1,2,3})) << "\n"; // true
    cout << sol.isSameTree(build({1,2}), build({1,{},2})) << "\n"; // false
    cout << sol.isSameTree(build({}), build({})) << "\n"; // true
    return 0;
}

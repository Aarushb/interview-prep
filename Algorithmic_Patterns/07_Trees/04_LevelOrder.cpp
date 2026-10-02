/*
PROBLEM: Binary Tree Level Order Traversal
DESCRIPTION: Return level-order traversal of node values from root to leaves.
CONSTRAINTS:
- The number of nodes in the tree is in the range [0, 2000].
- -1000 <= Node.val <= 1000
EXAMPLE INPUT/OUTPUT:
Input: [3,9,20,null,null,15,7]
Output: [[3],[9,20],[15,7]]
*/

/*
APPROACH:
Level order traversal is BFS, not DFS, since it needs to group nodes by depth. The trick is
to snapshot the queue's size at the start of each iteration of the outer while loop so
exactly one level's worth of nodes is processed before moving on to the next level. Each
processed node pushes its non-null children onto the queue, which become the next level.
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode { int val; TreeNode* left; TreeNode* right; TreeNode(int x):val(x),left(nullptr),right(nullptr){} };

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res; if (!root) return res;
        queue<TreeNode*> q; q.push(root);
        while (!q.empty()) {
            int sz = q.size();
            vector<int> level;
            for (int i=0;i<sz;i++) {
                auto* cur = q.front(); q.pop();
                level.push_back(cur->val);
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            res.push_back(level);
        }
        return res;
    }
};

TreeNode* build(const vector<optional<int>>& v) {
    if (v.empty() || !v[0]) return nullptr;
    vector<TreeNode*> n(v.size(), nullptr);
    for (size_t i=0;i<v.size();i++) if (v[i]) n[i]=new TreeNode(*v[i]);
    for (size_t i=0;i<v.size();i++) if (n[i]) { size_t l=2*i+1,r=2*i+2; if(l<v.size()) n[i]->left=n[l]; if(r<v.size()) n[i]->right=n[r]; }
    return n[0];
}

void printLevels(const vector<vector<int>>& lv){
    cout << "[";
    for (size_t i=0;i<lv.size();i++){
        cout << "[";
        for (size_t j=0;j<lv[i].size();j++){
            cout << lv[i][j];
            if (j+1<lv[i].size()) cout << ",";
        }
        cout << "]"; if (i+1<lv.size()) cout << ",";
    }
    cout << "]\n";
}

int main(){
    Solution sol;
    auto levels = sol.levelOrder(build({3,9,20,{}, {},15,7}));
    printLevels(levels);
    auto empty = sol.levelOrder(nullptr);
    printLevels(empty);
    return 0;
}

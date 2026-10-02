/*
PROBLEM 1: Insert into a Binary Search Tree (LeetCode 701)
DESCRIPTION: Given the root of a BST and a value to insert, insert the value into the
BST such that the resulting tree is still a valid BST. Return the root.
CONSTRAINTS: Value being inserted does not already exist in the tree.
EXAMPLE: root = [4,2,7,1,3], val = 5 -> [4,2,7,1,3,5]
*/

/*
APPROACH:
Standard recursive BST descent: if val < node->val go left, if val > node->val go right;
when we hit nullptr, that's the correct spot — create a new node there. Any valid
insertion position works since the problem doesn't require balance, just correctness of
the BST property. O(h) time, O(h) recursion stack.
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (root == nullptr) return new TreeNode(val);
    if (val < root->val) root->left = insertIntoBST(root->left, val);
    else root->right = insertIntoBST(root->right, val);
    return root;
}

/*
PROBLEM 2: Lowest Common Ancestor of a BST (LeetCode 235)
DESCRIPTION: Given a BST and two nodes p and q (both guaranteed to exist in the tree),
find their lowest common ancestor.
CONSTRAINTS: All values are unique; p != q.
EXAMPLE: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8 -> 6
*/

/*
APPROACH:
Exploit the BST ordering property directly instead of doing a general tree LCA search:
starting at root, if both p->val and q->val are less than node->val, the LCA must be in
the left subtree (recurse/iterate left); if both are greater, it must be in the right
subtree; otherwise (p and q split, or one equals node->val) node is the LCA — this is
the first point where the search paths to p and q diverge (or one of them IS the
current node). O(h) time, O(1) extra space using the iterative version below.
*/

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    TreeNode* node = root;
    while (node != nullptr) {
        if (p->val < node->val && q->val < node->val) {
            node = node->left;
        } else if (p->val > node->val && q->val > node->val) {
            node = node->right;
        } else {
            return node;
        }
    }
    return nullptr; // unreachable given problem guarantees
}

int main() {
    cout << "--- Insert into a Binary Search Tree ---\n";
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    root = insertIntoBST(root, 5);

    // print inorder to confirm sorted order including the new value
    function<void(TreeNode*)> inorder = [&](TreeNode* n) {
        if (!n) return;
        inorder(n->left);
        cout << n->val << " ";
        inorder(n->right);
    };
    cout << "inorder after insert(5): ";
    inorder(root);
    cout << "(expected: 1 2 3 4 5 7)\n\n";

    cout << "--- Lowest Common Ancestor of a BST ---\n";
    TreeNode* r = new TreeNode(6);
    r->left = new TreeNode(2);
    r->right = new TreeNode(8);
    r->left->left = new TreeNode(0);
    r->left->right = new TreeNode(4);
    r->right->left = new TreeNode(7);
    r->right->right = new TreeNode(9);
    r->left->right->left = new TreeNode(3);
    r->left->right->right = new TreeNode(5);

    TreeNode* p = r->left;             // node 2
    TreeNode* q = r->right;            // node 8
    cout << "LCA(2, 8) = " << lowestCommonAncestor(r, p, q)->val << " (expected 6)\n";

    TreeNode* p2 = r->left;            // node 2
    TreeNode* q2 = r->left->right;     // node 4
    cout << "LCA(2, 4) = " << lowestCommonAncestor(r, p2, q2)->val << " (expected 2)\n";

    return 0;
}

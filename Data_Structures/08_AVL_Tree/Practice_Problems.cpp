/*
PROBLEM 1: AVL Rotation Demo
DESCRIPTION: Insert carefully chosen sequences of values into an AVL tree so that each
of the four rebalancing cases (LL, RR, LR, RL) is triggered at least once, printing the
tree's height and root balance factor after each insert to demonstrate that the tree
never drifts out of the AVL invariant (balance factor always in [-1, 1]).
CONSTRAINTS: Small, hand-picked integer sequences chosen specifically to force each case.
EXAMPLE: Inserting 30, 20, 10 forces an LL rotation at the root.
*/

/*
APPROACH:
Reuse the same self-balancing AVL insert logic as Implementation.cpp (a minimal
self-contained copy here, since Practice_Problems.cpp must stand alone): each insert
walks down to the right BST position, then on the way back up recomputes height and
balance factor at every ancestor, applying a single rotation (LL/RR) or a double
rotation (LR/RL) whenever a node's balance factor exceeds +-1. We deliberately choose
four small 3-node sequences, one per rotation case:
  - LL: 30, 20, 10  (heavy on left-of-left)   -> single right rotation
  - RR: 10, 20, 30  (heavy on right-of-right) -> single left rotation
  - LR: 30, 10, 20  (heavy on left-of-right)  -> left rotation then right rotation
  - RL: 10, 30, 20  (heavy on right-of-left)  -> right rotation then left rotation
After each insert we print height + root balance factor to show the tree self-corrects
back to a balance factor within [-1, 1] every time.
*/

#include <bits/stdc++.h>
using namespace std;

struct AVLNode {
    int val;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int v) : val(v), left(nullptr), right(nullptr), height(1) {}
};

int heightOf(AVLNode* n) { return n == nullptr ? 0 : n->height; }
int balanceOf(AVLNode* n) { return n == nullptr ? 0 : heightOf(n->left) - heightOf(n->right); }
void updateHeight(AVLNode* n) { n->height = 1 + max(heightOf(n->left), heightOf(n->right)); }

AVLNode* rotateRight(AVLNode* z) {
    AVLNode* y = z->left;
    AVLNode* t = y->right;
    y->right = z;
    z->left = t;
    updateHeight(z);
    updateHeight(y);
    return y;
}

AVLNode* rotateLeft(AVLNode* z) {
    AVLNode* y = z->right;
    AVLNode* t = y->left;
    y->left = z;
    z->right = t;
    updateHeight(z);
    updateHeight(y);
    return y;
}

AVLNode* insertAVL(AVLNode* node, int val) {
    if (node == nullptr) return new AVLNode(val);
    if (val < node->val) node->left = insertAVL(node->left, val);
    else if (val > node->val) node->right = insertAVL(node->right, val);
    else return node;

    updateHeight(node);
    int balance = balanceOf(node);

    if (balance > 1 && balanceOf(node->left) < 0) node->left = rotateLeft(node->left);   // LR fix-up
    if (balance > 1) return rotateRight(node);                                            // LL / LR

    if (balance < -1 && balanceOf(node->right) > 0) node->right = rotateRight(node->right); // RL fix-up
    if (balance < -1) return rotateLeft(node);                                              // RR / RL

    return node;
}

void preorderPrint(AVLNode* node) {
    if (node == nullptr) return;
    cout << node->val << "(bf=" << balanceOf(node) << ") ";
    preorderPrint(node->left);
    preorderPrint(node->right);
}

void runDemo(const string& label, vector<int> values) {
    cout << "-- " << label << " --\n";
    AVLNode* root = nullptr;
    for (int v : values) {
        root = insertAVL(root, v);
        cout << "insert(" << v << ") -> height=" << heightOf(root)
             << " rootBalance=" << balanceOf(root) << "\n";
    }
    cout << "preorder structure (val(bf)): ";
    preorderPrint(root);
    cout << "\n\n";
}

/*
PROBLEM 2: Check if a Binary Tree is Height-Balanced (LeetCode 110)
DESCRIPTION: Given a binary tree, determine if it is height-balanced: for every node,
the height difference between its left and right subtrees is at most 1.
CONSTRAINTS: Tree can be arbitrary (not necessarily a BST).
EXAMPLE: [3,9,20,null,null,15,7] -> true; [1,2,2,3,3,null,null,4,4] -> false
*/

/*
APPROACH:
Naive approach recomputes height at every node from scratch (O(n) per node -> O(n^2)
total). Instead, do a single bottom-up post-order pass that returns the height of each
subtree while simultaneously checking balance: a helper returns -1 as a sentinel meaning
"already found unbalanced" and otherwise returns the actual height. Any -1 bubbling up
from either child immediately propagates up (short-circuiting further checks), and at
each node we also check |leftHeight - rightHeight| <= 1. This achieves O(n) total time,
O(h) recursion stack, computing balance and height together in one pass.
*/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

int checkHeight(TreeNode* node) {
    if (node == nullptr) return 0;

    int leftHeight = checkHeight(node->left);
    if (leftHeight == -1) return -1; // left subtree already unbalanced

    int rightHeight = checkHeight(node->right);
    if (rightHeight == -1) return -1; // right subtree already unbalanced

    if (abs(leftHeight - rightHeight) > 1) return -1; // this node is unbalanced

    return 1 + max(leftHeight, rightHeight);
}

bool isBalanced(TreeNode* root) {
    return checkHeight(root) != -1;
}

int main() {
    cout << "=== AVL Rotation Demo ===\n";
    runDemo("LL case", {30, 20, 10});
    runDemo("RR case", {10, 20, 30});
    runDemo("LR case", {30, 10, 20});
    runDemo("RL case", {10, 30, 20});

    cout << "=== Check if a Binary Tree is Height-Balanced ===\n";
    // Balanced tree: [3,9,20,null,null,15,7]
    TreeNode* balanced = new TreeNode(3);
    balanced->left = new TreeNode(9);
    balanced->right = new TreeNode(20);
    balanced->right->left = new TreeNode(15);
    balanced->right->right = new TreeNode(7);
    cout << "balanced tree isBalanced: " << isBalanced(balanced) << " (expected 1)\n";

    // Unbalanced tree: [1,2,2,3,3,null,null,4,4]
    TreeNode* unbalanced = new TreeNode(1);
    unbalanced->left = new TreeNode(2);
    unbalanced->right = new TreeNode(2);
    unbalanced->left->left = new TreeNode(3);
    unbalanced->left->right = new TreeNode(3);
    unbalanced->left->left->left = new TreeNode(4);
    unbalanced->left->left->right = new TreeNode(4);
    cout << "unbalanced tree isBalanced: " << isBalanced(unbalanced) << " (expected 0)\n";

    return 0;
}

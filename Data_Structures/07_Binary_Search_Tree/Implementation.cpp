/*
PROBLEM: Binary Search Tree — Custom Implementation
DESCRIPTION: Implement a BST from scratch, supporting insert, search, erase (all three
deletion cases: leaf, one child, two children), inorder traversal, and findMin/findMax,
without relying on std::set/std::map.
CONSTRAINTS: General-purpose implementation for distinct integer values; no duplicate
handling is required (standard interview assumption unless stated otherwise).
EXAMPLE INPUT/OUTPUT: See main() below for a runnable usage demo.
*/

/*
APPROACH:
Each Node holds val, left, right. The BST invariant (left < node < right) is maintained
recursively:
- insert(val): recurse left if val < node->val, right if val > node->val, and when we
  hit a null pointer, allocate a new node there. Returns the (possibly new) subtree root
  so parent pointers get reattached correctly. O(h) where h is tree height.
- search(val): same left/right recursion, return true on exact match, false on hitting
  null. O(h).
- findMin/findMax: keep following left/right children respectively until null. The
  minimum of a BST is always the leftmost node; the maximum is always the rightmost.
- erase(val): recurse to find the node. Three cases once found:
    1. Leaf (no children): simply delete it, parent's pointer becomes null.
    2. One child: splice the node out — parent points directly to the single child.
    3. Two children: cannot just delete it (would orphan both subtrees). Instead, find
       the inorder successor (the minimum value in the right subtree — the smallest
       value greater than node->val), copy that value into the current node, then
       recursively erase the successor's original node from the right subtree (which
       will hit case 1 or 2 since the successor has no left child by definition of being
       the minimum).
  Every case preserves the BST invariant. O(h).
- inorder traversal (left, node, right) visits values in strictly increasing order for a
  BST — this is the standard way to verify correctness.
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int v) : val(v), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    Node* insertHelper(Node* node, int val) {
        if (node == nullptr) return new Node(val);
        if (val < node->val) node->left = insertHelper(node->left, val);
        else if (val > node->val) node->right = insertHelper(node->right, val);
        // val == node->val: duplicate, no-op
        return node;
    }

    bool searchHelper(Node* node, int val) const {
        if (node == nullptr) return false;
        if (val == node->val) return true;
        return val < node->val ? searchHelper(node->left, val) : searchHelper(node->right, val);
    }

    Node* findMinNode(Node* node) const {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    Node* findMaxNode(Node* node) const {
        while (node->right != nullptr) node = node->right;
        return node;
    }

    Node* eraseHelper(Node* node, int val) {
        if (node == nullptr) return nullptr;

        if (val < node->val) {
            node->left = eraseHelper(node->left, val);
        } else if (val > node->val) {
            node->right = eraseHelper(node->right, val);
        } else {
            // Found the node to delete
            if (node->left == nullptr && node->right == nullptr) {
                // Case 1: leaf
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {
                // Case 2: only right child
                Node* rightChild = node->right;
                delete node;
                return rightChild;
            } else if (node->right == nullptr) {
                // Case 2: only left child
                Node* leftChild = node->left;
                delete node;
                return leftChild;
            } else {
                // Case 3: two children — replace with inorder successor
                Node* successor = findMinNode(node->right);
                node->val = successor->val;
                node->right = eraseHelper(node->right, successor->val);
            }
        }
        return node;
    }

    void inorderHelper(Node* node, vector<int>& out) const {
        if (node == nullptr) return;
        inorderHelper(node->left, out);
        out.push_back(node->val);
        inorderHelper(node->right, out);
    }

    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(int val) {
        root = insertHelper(root, val);
    }

    bool search(int val) const {
        return searchHelper(root, val);
    }

    void erase(int val) {
        root = eraseHelper(root, val);
    }

    vector<int> inorder() const {
        vector<int> out;
        inorderHelper(root, out);
        return out;
    }

    int findMin() const {
        if (root == nullptr) throw runtime_error("findMin() called on empty tree");
        return findMinNode(root)->val;
    }

    int findMax() const {
        if (root == nullptr) throw runtime_error("findMax() called on empty tree");
        return findMaxNode(root)->val;
    }
};

void printVec(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    BST tree;
    for (int v : {50, 30, 70, 20, 40, 60, 80, 10, 25}) {
        tree.insert(v);
    }

    cout << "inorder after inserts: ";
    printVec(tree.inorder()); // expected sorted: 10 20 25 30 40 50 60 70 80

    cout << "search(40): " << tree.search(40) << " (expected 1)\n";
    cout << "search(99): " << tree.search(99) << " (expected 0)\n";
    cout << "findMin(): " << tree.findMin() << " (expected 10)\n";
    cout << "findMax(): " << tree.findMax() << " (expected 80)\n";

    cout << "\n-- erase(20) [leaf] --\n";
    tree.erase(20);
    printVec(tree.inorder());

    cout << "\n-- erase(30) [one child: 25 remains] --\n";
    tree.erase(30);
    printVec(tree.inorder());

    cout << "\n-- erase(50) [two children: root] --\n";
    tree.erase(50);
    printVec(tree.inorder());

    return 0;
}

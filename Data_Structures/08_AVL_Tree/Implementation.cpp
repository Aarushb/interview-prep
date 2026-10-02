/*
PROBLEM: AVL Tree — Custom Implementation
DESCRIPTION: Implement a self-balancing AVL tree from scratch, supporting insert (with
rebalancing via all four rotation cases), erase (with rebalancing), search,
height/balance-factor tracking, and inorder traversal, without relying on
std::set/std::map.
CONSTRAINTS: General-purpose implementation for distinct integer values.
EXAMPLE INPUT/OUTPUT: See main() below for a runnable usage demo.
*/

/*
APPROACH:
Each Node stores val, left, right, and height (height of a leaf = 1; height of null =
0, tracked via a helper so we don't need to null-check everywhere). After every
insert/erase, as the recursion unwinds back up the path from the modified node to the
root, we:
  1. Recompute this node's height = 1 + max(height(left), height(right)).
  2. Compute its balance factor = height(left) - height(right).
  3. If |balance| > 1, the subtree is unbalanced and needs exactly one of four rotation
     patterns to fix, determined by the sign of this node's balance factor AND the sign
     of the *child's* balance factor (this second check is what distinguishes a
     "straight-line" case from a "zig-zag" case):

     - LL case (balance > 1 AND left child's balance >= 0): the heavy weight is on the
       left child's LEFT subtree — a straight left-left line. Fix with a single RIGHT
       rotation on the current node. Picture 3 nodes z (unbalanced) -> y (z.left) ->
       x (y.left): rotating right on z makes y the new subtree root, z becomes y's
       right child, and y's old right child becomes z's new left child (never lost,
       BST order preserved).

     - RR case (balance < -1 AND right child's balance <= 0): mirror of LL — heavy
       weight on the right child's RIGHT subtree. Fix with a single LEFT rotation on
       the current node.

     - LR case (balance > 1 AND left child's balance < 0): the heavy weight is on the
       left child's RIGHT subtree — a "zig-zag". A single rotation can't fix this
       directly, so we first LEFT-rotate the left child (turning it into an LL shape),
       then RIGHT-rotate the current node (now a clean LL case).

     - RL case (balance < -1 AND right child's balance > 0): mirror of LR — heavy
       weight on the right child's LEFT subtree. First RIGHT-rotate the right child
       (turning it into an RR shape), then LEFT-rotate the current node.

  A single rotation is O(1) (just pointer/height updates), and at most O(log n)
  rotations happen along the path per insert/delete (in practice insert needs at most
  one rotation; delete can need up to O(log n) rotations up the path), so both remain
  O(log n) overall — dominated by the O(log n) height of the tree itself.

  erase() reuses the same three deletion cases as a plain BST (leaf / one child / two
  children via inorder successor), but after splicing the node out, it also rebalances
  every ancestor on the way back up, exactly like insert does.
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* left;
    Node* right;
    int height;
    Node(int v) : val(v), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;

    int heightOf(Node* node) const {
        return node == nullptr ? 0 : node->height;
    }

    int balanceFactor(Node* node) const {
        return node == nullptr ? 0 : heightOf(node->left) - heightOf(node->right);
    }

    void updateHeight(Node* node) {
        node->height = 1 + max(heightOf(node->left), heightOf(node->right));
    }

    // Right rotation: promotes left child to be the new subtree root.
    Node* rotateRight(Node* z) {
        Node* y = z->left;
        Node* t = y->right;

        y->right = z;
        z->left = t;

        updateHeight(z); // z's height must be recomputed BEFORE y's (z is now lower)
        updateHeight(y);

        return y; // new subtree root
    }

    // Left rotation: promotes right child to be the new subtree root.
    Node* rotateLeft(Node* z) {
        Node* y = z->right;
        Node* t = y->left;

        y->left = z;
        z->right = t;

        updateHeight(z);
        updateHeight(y);

        return y; // new subtree root
    }

    Node* rebalance(Node* node) {
        updateHeight(node);
        int balance = balanceFactor(node);

        if (balance > 1) {
            // Left-heavy
            if (balanceFactor(node->left) < 0) {
                // LR case: left child is right-heavy -> rotate left child left first
                node->left = rotateLeft(node->left);
            }
            // LL case (or LR after the fix-up above): rotate current node right
            return rotateRight(node);
        }

        if (balance < -1) {
            // Right-heavy
            if (balanceFactor(node->right) > 0) {
                // RL case: right child is left-heavy -> rotate right child right first
                node->right = rotateRight(node->right);
            }
            // RR case (or RL after the fix-up above): rotate current node left
            return rotateLeft(node);
        }

        return node; // already balanced
    }

    Node* insertHelper(Node* node, int val) {
        if (node == nullptr) return new Node(val);
        if (val < node->val) node->left = insertHelper(node->left, val);
        else if (val > node->val) node->right = insertHelper(node->right, val);
        else return node; // duplicate, no-op

        return rebalance(node);
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

    Node* eraseHelper(Node* node, int val) {
        if (node == nullptr) return nullptr;

        if (val < node->val) {
            node->left = eraseHelper(node->left, val);
        } else if (val > node->val) {
            node->right = eraseHelper(node->right, val);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {
                Node* rightChild = node->right;
                delete node;
                return rightChild;
            } else if (node->right == nullptr) {
                Node* leftChild = node->left;
                delete node;
                return leftChild;
            } else {
                Node* successor = findMinNode(node->right);
                node->val = successor->val;
                node->right = eraseHelper(node->right, successor->val);
            }
        }

        return rebalance(node);
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
    AVLTree() : root(nullptr) {}
    ~AVLTree() { destroy(root); }

    void insert(int val) {
        root = insertHelper(root, val);
    }

    void erase(int val) {
        root = eraseHelper(root, val);
    }

    bool search(int val) const {
        return searchHelper(root, val);
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

    int treeHeight() const {
        return heightOf(root);
    }

    int rootBalanceFactor() const {
        return balanceFactor(root);
    }
};

void printVec(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << "\n";
}

int main() {
    AVLTree tree;

    cout << "Inserting 10, 20, 30 (would force an unbalanced RR chain in a plain BST):\n";
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    cout << "inorder: "; printVec(tree.inorder());
    cout << "height: " << tree.treeHeight() << " (expected 2, rebalanced via RR rotation, i.e. a single left rotation)\n";
    cout << "root balance factor: " << tree.rootBalanceFactor() << " (expected 0)\n\n";

    cout << "Inserting more values: 5, 40, 1, 25\n";
    for (int v : {5, 40, 1, 25}) tree.insert(v);
    cout << "inorder: "; printVec(tree.inorder()); // sorted
    cout << "height: " << tree.treeHeight() << " (should stay close to log2(n))\n\n";

    cout << "search(25): " << tree.search(25) << " (expected 1)\n";
    cout << "search(99): " << tree.search(99) << " (expected 0)\n\n";

    cout << "-- erase(20) --\n";
    tree.erase(20);
    cout << "inorder: "; printVec(tree.inorder());
    cout << "height after erase: " << tree.treeHeight() << "\n";
    cout << "root balance factor after erase: " << tree.rootBalanceFactor()
         << " (must be in [-1, 1])\n";

    return 0;
}

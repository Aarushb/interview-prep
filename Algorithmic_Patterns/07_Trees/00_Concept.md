# Trees

## Pattern Overview
Trees are recursively defined structures (a node plus left/right subtrees), so most tree problems are solved by recursive decomposition: define what a function returns for a node in terms of what it returns for that node's children. Traversals come in two families — DFS (pre/in/post-order) for exploring depth-first, and BFS (level-order) for processing nodes level by level — and information flows either top-down (via parameters) or bottom-up (via return values).

## When to Use It
- The input is explicitly a binary tree / `TreeNode*` (or an n-ary tree).
- The problem asks about depth, height, diameter, or balance of a structure.
- The problem asks about ancestors, paths (root-to-leaf, or any-node-to-any-node), or path sums.
- You need to compare, merge, serialize/deserialize, or transform (invert/mirror/flatten) a tree.
- The problem mentions "binary search tree" (BST) and asks you to validate, insert, delete, or find the k-th smallest/closest value.
- You need to process nodes "level by level" (this is a strong signal for BFS/level-order, not plain DFS).
- Recursion feels natural because the problem on the whole tree can be answered from the same problem on its left and right subtrees.

## Core Idea
Trees are recursively defined: a tree is a node plus a left subtree and a right subtree, each of which is itself a tree (or empty/null). This means almost every tree problem can be solved by recursive decomposition — define what the function returns for a node in terms of what it returns for that node's children, and trust the recursion to handle the rest ("recursive leap of faith"). The base case is always the null node, and getting that base case right (return 0? true? nullptr? an empty vector?) is usually the crux of getting the whole solution right.

There are two broad traversal families. DFS (depth-first search) goes as deep as possible before backtracking, and comes in three flavors depending on when you "visit" a node relative to its children: pre-order (visit, then left, then right — useful for copying/serializing top-down), in-order (left, visit, right — useful for BSTs since it yields sorted order), and post-order (left, right, visit — useful when a node's answer depends on its children's answers first, like height or diameter). BFS (breadth-first search), by contrast, processes nodes level by level using a queue, and is the go-to approach whenever the problem cares about depth/level grouping explicitly (e.g., "return each level as its own list", "find the rightmost node at each depth").

A large class of tree problems reduces to passing information down (top-down, via function parameters — e.g., valid BST ranges, current path, current depth) and/or returning information up (bottom-up, via return values — e.g., height, whether a subtree is balanced, count of nodes matching a condition). Many trickier problems (diameter, max path sum) need both simultaneously: compute a bottom-up value at each node while also updating a global/outer answer that considers paths passing *through* that node.

For BSTs specifically, the ordering invariant (left < node < right, recursively for the whole subtree, not just immediate children) unlocks O(log n) search/insert/delete on balanced trees, and in-order traversal always yields values in sorted order — a fact worth exploiting directly in many BST problems instead of re-deriving it.

## Complexity
- Time: O(n) for any traversal that visits every node once (most Trees problems). BST search/insert/delete is O(h) where h is the tree height — O(log n) if balanced, O(n) in the worst case (a degenerate/skewed tree).
- Space: O(h) for the recursion call stack in DFS (O(log n) balanced, O(n) worst case skewed). O(w) for BFS, where w is the maximum width of the tree (up to O(n) for a wide/complete tree). Iterative DFS with an explicit stack has the same O(h) space profile as recursive DFS.

## C++ Template
```cpp
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// --- Generic bottom-up DFS: compute a value from children, combine at parent ---
int dfs(TreeNode* node) {
    if (!node) return 0; // base case: define carefully per problem (0, true, INT_MIN, etc.)

    int leftResult = dfs(node->left);
    int rightResult = dfs(node->right);

    // combine children's results with this node to produce this node's answer
    return 1 + max(leftResult, rightResult);
}

// --- Generic top-down DFS: pass state down, e.g. BST range validation ---
bool validate(TreeNode* node, long lo, long hi) {
    if (!node) return true;
    if (node->val <= lo || node->val >= hi) return false;
    return validate(node->left, lo, node->val) && validate(node->right, node->val, hi);
}

// --- Generic BFS / level-order traversal ---
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int levelSize = q.size(); // snapshot size BEFORE the inner loop mutates the queue
        vector<int> level;
        for (int i = 0; i < levelSize; i++) {
            TreeNode* cur = q.front(); q.pop();
            level.push_back(cur->val);
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        result.push_back(level);
    }
    return result;
}
```

## Common Pitfalls
- Forgetting the null-node base case, or getting its return value wrong (e.g., returning `false` instead of `true` for "is this null subtree balanced/valid" — an empty tree is trivially valid).
- Validating a BST by comparing each node only to its immediate children instead of tracking a valid range from all ancestors — this misses violations from a grandparent or higher.
- Forgetting to snapshot the queue size before the inner loop in BFS, causing level boundaries to blur as newly-pushed children get consumed in the same "level".
- Not distinguishing between top-down (pass info down via parameters) and bottom-up (return info up) — using the wrong direction for a problem like diameter or max path sum leads to convoluted, buggy code instead of the clean combination of both.
- Mutating a global variable for "best answer so far" without also correctly computing and returning the value each recursive call needs to hand back to its parent (common bug in diameter/max-path-sum style problems).
- Assuming trees are balanced — recursion depth and complexity bounds can degrade to O(n) on skewed/degenerate trees (e.g., a tree built by inserting sorted data into a BST).

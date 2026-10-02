# AVL Tree

## Overview
An AVL tree is a self-balancing binary search tree. In addition to val/left/right, each
node stores its subtree `height`. After every insert or delete, the tree checks the
"balance factor" (height of left subtree minus height of right subtree) of each node on
the path back to the root, and performs rotations whenever that factor becomes -2 or +2,
restoring it to -1, 0, or +1. This keeps the tree height at O(log n) at all times,
regardless of insertion order — unlike a plain BST, which can degenerate to a linked
list.

## Operations & Complexity
| Operation | Time | Space |
|---|---|---|
| insert (with rebalancing) | O(log n) guaranteed | O(1) extra (O(log n) recursion stack) |
| erase (with rebalancing)  | O(log n) guaranteed | O(1) extra (O(log n) recursion stack) |
| search | O(log n) guaranteed | O(1) extra (O(log n) recursion stack) |
| findMin/findMax | O(log n) guaranteed | O(1) |
| rotation (single) | O(1) | O(1) |
| inorder traversal | O(n) | O(n) for output |

The key guarantee: height is always O(log n), so every operation that walks root-to-leaf
is O(log n) in the *worst* case, not just on average — this is the whole point of AVL
over a plain BST.

## When It's Used in Interviews
- Problems that explicitly require guaranteed O(log n) operations regardless of input
  order (a plain BST interviewers might reject if you point out it degrades to O(n) on
  sorted input).
- Understanding how `std::map`/`std::set`/Java's `TreeMap` achieve their guarantees
  internally (they use Red-Black trees, a looser-balance cousin of AVL, but the rotation
  mechanics are the same family of ideas).
- Follow-up questions like "what if the tree needs to stay balanced after many
  insertions/deletions?" after presenting a plain BST solution.
- Demonstrating understanding of tree rotations, a building block for other balanced
  structures (Red-Black trees, splay trees, treaps).

## Trade-offs
- **AVL vs plain BST**: AVL guarantees O(log n) height at the cost of extra bookkeeping
  (storing height, computing balance factors, performing rotations) on every insert and
  delete. A plain BST is simpler but has no guarantee — worst case O(n).
- **AVL vs Red-Black tree**: AVL trees are more rigidly balanced (height difference of at
  most 1 vs Red-Black's looser invariant), which makes AVL *searches* slightly faster,
  but AVL *insertions/deletions* can require more rotations to restore balance.
  Red-Black trees are usually preferred for write-heavy workloads (e.g., `std::map`);
  AVL trees are preferred for read-heavy workloads.
- **AVL vs hash map**: hash map gives O(1) average operations but no ordering; AVL gives
  O(log n) guaranteed with sorted-order traversal, range queries, and predecessor/
  successor operations.

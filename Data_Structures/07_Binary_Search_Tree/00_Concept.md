# Binary Search Tree (BST)

## Overview
A binary search tree is a node-based binary tree where each node stores a value, and a
left/right child pointer. The BST invariant: for every node, all values in its left
subtree are less than the node's value, and all values in its right subtree are greater
(assuming no duplicates). This ordering lets search, insert, and delete all follow a
single root-to-leaf path, discarding half the remaining candidates at each step —
*if* the tree is reasonably balanced. Nothing in a plain BST enforces balance, though,
so the tree's shape (and therefore its performance) depends entirely on insertion order.

## Operations & Complexity
| Operation | Time (balanced) | Time (worst case, degenerate) | Space |
|---|---|---|---|
| insert      | O(log n) | O(n) | O(1) extra (O(h) recursion stack) |
| search      | O(log n) | O(n) | O(1) extra (O(h) recursion stack) |
| erase       | O(log n) | O(n) | O(1) extra (O(h) recursion stack) |
| findMin/findMax | O(log n) | O(n) | O(1) |
| inorder traversal | O(n) | O(n) | O(h) recursion stack, O(n) for output |

Worst case occurs when values are inserted in sorted (or reverse-sorted) order, degrading
the tree into a linked list (height h = n). A self-balancing variant (e.g., AVL,
Red-Black) guarantees h = O(log n).

## When It's Used in Interviews
- Any problem that explicitly says "binary search tree" (validate BST, insert/delete/
  search into a BST, kth smallest element in a BST, BST iterator, LCA of a BST).
- Range queries where you need all values between lo and hi (inorder traversal with
  pruning).
- When you need an ordered structure with dynamic insert/delete and don't want to
  reimplement balancing logic (many interview problems assume/accept an unbalanced BST
  since inputs are small or already balanced).
- Understanding BSTs is also the prerequisite for AVL/Red-Black trees and for
  `std::map`/`std::set`, which are typically balanced BSTs internally.

## Trade-offs
- **BST vs hash map**: a hash map gives O(1) average search/insert/delete but no
  ordering; a BST gives O(log n) (when balanced) with the benefit of sorted-order
  traversal, range queries, and floor/ceiling operations.
- **BST vs AVL/Red-Black tree**: a plain BST is simpler to implement but offers no
  worst-case guarantee — an adversarial or sorted insertion order degrades it to O(n)
  per operation. A self-balancing tree guarantees O(log n) at the cost of extra
  bookkeeping (heights/colors) and rotation logic on every insert/delete.
- **BST vs sorted array**: a sorted array gives O(log n) search via binary search but
  O(n) insert/delete (shifting elements); a BST gives O(log n) for all three when
  balanced.

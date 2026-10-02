# Singly Linked List

## Overview
A singly linked list is a chain of nodes, each holding a value and a pointer (`next`) to the
following node. Unlike a dynamic array, memory is not contiguous — each node is a separate heap
allocation, connected only through pointers. The list class keeps a `head` pointer (and optionally
a `tail` pointer for O(1) `push_back`) and a `size` counter. Because each node only knows about the
node after it, traversal is one-directional: you cannot walk backward without restarting from head.

Insertion and deletion at the front are O(1) because they only touch `head` and one node's `next`
pointer, with no shifting of other elements — this is the core advantage over an array.

## Operations & Complexity
| Operation | Time | Space |
|---|---|---|
| `push_front` | O(1) | O(1) |
| `push_back` (with tail pointer) | O(1) | O(1) |
| `pop_front` | O(1) | O(1) |
| `insert_at(index, val)` | O(n) (walk to index) | O(1) |
| `erase_at(index)` | O(n) (walk to index) | O(1) |
| `find(val)` | O(n) | O(1) |
| traversal / print | O(n) | O(1) |

## When It's Used in Interviews
- Problems explicitly about linked lists (reversal, cycle detection, merging, middle node).
- When frequent insertions/deletions happen at the front or at a known node, and random access
  isn't needed.
- Fast/slow pointer (Floyd's) techniques for cycle detection or finding the middle.
- Implementing other structures (e.g., a hash map's separate-chaining buckets, or an LRU cache's
  ordering) where nodes need cheap insert/remove without shifting.

## Trade-offs
- **vs Dynamic Array**: O(1) insertion/removal at the front (vs O(n) shifting for an array), but
  O(n) random access (must walk from head) instead of O(1) indexing, and worse cache locality since
  nodes are scattered in memory.
- **vs Doubly Linked List**: Uses less memory per node (one pointer instead of two) but cannot
  traverse backward or delete a node in O(1) without already having a pointer to its predecessor.
- Extra memory overhead per element (the `next` pointer) compared to an array's zero-overhead
  contiguous storage.

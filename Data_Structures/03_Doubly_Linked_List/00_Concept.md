# Doubly Linked List

## Overview
A doubly linked list extends the singly linked list by giving each node two pointers: `next` (the
following node) and `prev` (the preceding node). This bidirectionality lets the list be traversed
in either direction and, critically, lets a node be removed in O(1) once you have a pointer to it
directly — no need to walk from head to find its predecessor, since `prev` is already known.

The list class typically keeps both a `head` and `tail` pointer, enabling O(1) push/pop at both
ends. This structure is the backbone of many real-world implementations, notably LRU caches, where
nodes need to be moved to/from the front in O(1) given only a pointer to them (usually obtained via
a hash map).

## Operations & Complexity
| Operation | Time | Space |
|---|---|---|
| `push_front` | O(1) | O(1) |
| `push_back` | O(1) | O(1) |
| `pop_front` | O(1) | O(1) |
| `pop_back` | O(1) | O(1) |
| `insert_at(index, val)` | O(n) (walk to index) | O(1) |
| `erase_at(index)` | O(n) (walk to index) | O(1) |
| removal given a node pointer | O(1) | O(1) |
| forward/backward traversal | O(n) | O(1) |

## When It's Used in Interviews
- LRU Cache (LeetCode 146): combine a DLL with a hash map from key -> node pointer to get O(1)
  get/put with O(1) eviction of the least-recently-used entry.
- Browser history / undo-redo stacks that need bidirectional navigation (back/forward).
- Any problem needing O(1) deletion of an arbitrary known node (e.g., "delete this node" variants).
- Deque implementations (push/pop from both ends in O(1)).

## Trade-offs
- **vs Singly Linked List**: Bidirectional traversal and O(1) arbitrary-node deletion cost an extra
  pointer (`prev`) per node — roughly 50% more memory overhead per element, plus more pointer
  bookkeeping on every insert/delete (both `next` and `prev` must be kept consistent).
- **vs Dynamic Array**: Still O(n) random access by index, but O(1) insert/delete at known
  positions/nodes versus O(n) shifting; worse cache locality due to non-contiguous heap allocations.
- The extra `prev` pointer pays off specifically when the algorithm needs to move backward or
  splice out a node without re-scanning from the head.

# Binary Heap (Min-Heap / Max-Heap)

## Overview
A binary heap is a complete binary tree stored implicitly in a dynamic array: for a node at index `i`, its children live at `2*i+1` and `2*i+2`, and its parent at `(i-1)/2`. The heap property (min-heap: parent <= children; max-heap: parent >= children) is maintained after every insertion/removal via two local repair operations: sift-up (bubble a new/changed element toward the root) and sift-down (push an element toward the leaves until the property holds). Because the tree is complete, the array representation needs no explicit pointers, giving excellent cache locality.

## Operations & Complexity
| Operation | Time | Space |
|---|---|---|
| push (insert) | O(log n) | O(1) amortized (array growth) |
| pop (extract top) | O(log n) | O(1) |
| top/peek | O(1) | O(1) |
| sift-up | O(log n) | O(1) |
| sift-down | O(log n) | O(1) |
| buildHeap(vector) | O(n) | O(1) extra (in-place) |

## When It's Used in Interviews
- "Kth largest/smallest element" problems.
- Priority-based scheduling (task schedulers, Dijkstra's/Prim's algorithms).
- Merging K sorted lists.
- Greedy problems needing "always process the smallest/largest remaining item" (e.g. rope/Huffman-style merge-cost minimization).
- Streaming median / top-K-so-far problems using two heaps.

## Trade-offs
- vs sorted array: insertion into a sorted array is O(n); a heap gives O(log n) insertion at the cost of only partial ordering (you can't binary search a heap).
- vs balanced BST (e.g. AVL/RB tree): a BST gives O(log n) insert/delete/find-any-element and in-order traversal, but a heap is simpler, more cache-friendly (array-backed, no pointers), and buildHeap is O(n) vs O(n log n) for inserting n elements one-by-one into a BST.
- vs std::priority_queue: functionally equivalent; implementing it by hand exposes the sift-up/sift-down mechanics and the O(n) buildHeap trick that the STL hides.

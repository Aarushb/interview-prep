# Stack

## Overview
A stack is a LIFO (Last-In, First-Out) structure: the most recently added element is always the
first one removed. It can be built on top of either a dynamic array or a linked list; here it is
implemented backed by a hand-rolled dynamic array (raw buffer with capacity doubling), because
array-backed stacks have better cache locality and avoid per-element heap allocation overhead. All
operations happen at one end (the "top"), which for an array-backed stack is simply the last valid
index — this means push/pop never require shifting any other elements, unlike inserting into the
middle of an array.

## Operations & Complexity
| Operation | Time | Space |
|---|---|---|
| `push` (amortized) | O(1) amortized, O(n) worst case (on resize) | O(1) amortized extra |
| `pop` | O(1) | O(1) |
| `top` / `peek` | O(1) | O(1) |
| `empty()` | O(1) | O(1) |
| `size()` | O(1) | O(1) |

## When It's Used in Interviews
- Matching/validating nested structures: parentheses, brackets, HTML tags.
- Expression evaluation: infix-to-postfix conversion, evaluating postfix/prefix expressions.
- Simulating recursion iteratively (DFS with an explicit stack, backtracking undo).
- Monotonic stack problems: next greater element, largest rectangle in histogram, daily
  temperatures.
- Implementing a queue using two stacks (tests understanding of amortized cost transfer).

## Trade-offs
- **Array-backed vs Linked-list-backed**: Array-backed gives better cache locality and no per-node
  allocation overhead, but occasionally pays an O(n) resize cost (amortized O(1) overall) and may
  waste some unused capacity. Linked-list-backed avoids resize costs entirely (true O(1) worst case
  per push/pop) but each element carries pointer overhead and worse cache behavior.
- **vs Queue**: A stack only allows access at one end (LIFO), whereas a queue allows FIFO access at
  two ends. Choosing wrong changes correctness (e.g., a stack cannot correctly simulate a queue's
  ordering without extra bookkeeping, as seen in "Implement Queue using Stacks").

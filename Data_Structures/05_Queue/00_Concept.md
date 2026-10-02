# Queue

## Overview
A queue is a linear, FIFO (First-In-First-Out) data structure: elements are added at the "tail" (enqueue) and removed from the "head" (dequeue). This implementation backs the queue with a circular (ring) buffer: a fixed-size array plus `head` and `tail` indices that wrap around using modulo arithmetic. When the buffer becomes full, a new, larger array is allocated and the existing elements are copied over in logical order (auto-resize), similar to how `std::vector` grows.

Using a circular buffer avoids the classic inefficiency of a naive array-based queue (shifting all elements left on every dequeue, which is O(n)). Instead, `head` simply advances by one (mod capacity) on dequeue, and `tail` advances by one (mod capacity) on enqueue, both O(1).

## Operations & Complexity
| Operation | Time | Space |
|---|---|---|
| enqueue    | O(1) amortized (O(n) on resize) | O(1) amortized |
| dequeue    | O(1) | O(1) |
| front      | O(1) | O(1) |
| empty      | O(1) | O(1) |
| size       | O(1) | O(1) |
| Overall storage | — | O(n) |

## When It's Used in Interviews
- BFS traversal of graphs/trees (level-order traversal, shortest path in unweighted graphs).
- Producer/consumer or task-scheduling simulations.
- Sliding-window style problems where you need strict FIFO order (as opposed to a deque,
  which needs access at both ends).
- Implementing higher-level structures, e.g. "Implement Stack using Queues" or
  "Moving Average from Data Stream".

## Trade-offs
- **Circular array vs linked list**: array-backed circular buffer gives better cache
  locality and no per-node allocation overhead, but requires resizing (amortized O(1))
  when full. A linked-list-backed queue never needs resizing and has true O(1) worst-case
  enqueue/dequeue, but pays allocation cost and pointer-chasing overhead per node.
- **Circular buffer vs naive array with shifting**: naive shifting makes dequeue O(n);
  the circular buffer keeps both ends O(1).
- **`std::queue` (adapter over `std::deque`)**: in real code you'd just use `std::queue`;
  this implementation exists purely to understand what happens underneath.

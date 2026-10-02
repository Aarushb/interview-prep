# Deque (Double-Ended Queue)

## Overview
A deque generalizes a queue by allowing insertion and removal at both ends in O(1). This implementation backs the deque with a circular (ring) buffer, just like the Queue implementation, but tracks both a `head` index (for front operations) and derives the tail position from `head + count`. Pushing to the front moves `head` backward (mod capacity, using `(head - 1 + capacity) % capacity` to stay non-negative); pushing to the back writes at `(head + count) % capacity`. When the buffer fills, it is resized (doubled) and elements are copied out into logical order starting at index 0, exactly as with the Queue.

## Operations & Complexity
| Operation | Time | Space |
|---|---|---|
| push_front | O(1) amortized (O(n) on resize) | O(1) amortized |
| push_back  | O(1) amortized (O(n) on resize) | O(1) amortized |
| pop_front  | O(1) | O(1) |
| pop_back   | O(1) | O(1) |
| front      | O(1) | O(1) |
| back       | O(1) | O(1) |
| empty      | O(1) | O(1) |
| size       | O(1) | O(1) |
| Overall storage | — | O(n) |

## When It's Used in Interviews
- Sliding window problems that need the current window's max/min in O(1) via a
  monotonic deque (e.g., "Sliding Window Maximum").
- Palindrome checks that consume from both ends simultaneously.
- Implementing an LRU-cache-like access pattern, undo/redo buffers, browser history.
- Any problem needing both stack-like (LIFO) and queue-like (FIFO) behavior from a
  single structure — a deque subsumes both.

## Trade-offs
- **Circular array vs doubly linked list**: array-backed circular buffer gives better
  cache locality and lower memory overhead per element, but needs periodic resizing
  (amortized O(1)); a doubly linked list gives true worst-case O(1) push/pop at both
  ends with no resizing, at the cost of per-node allocation and pointer overhead.
- **Deque vs Queue**: a queue only needs O(1) access at the two opposite ends (enqueue at
  tail, dequeue at head); a deque needs O(1) access at *all four* combinations (push/pop
  at both front and back), which is why algorithms like "sliding window maximum" require
  a deque rather than a plain queue.
- **`std::deque`**: in real code you'd just use `std::deque` (which internally uses a
  map of fixed-size chunks); this implementation exists to understand the underlying
  ring-buffer mechanics.

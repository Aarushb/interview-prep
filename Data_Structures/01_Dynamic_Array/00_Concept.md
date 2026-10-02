# Dynamic Array

## Overview
A dynamic array is a contiguous, resizable block of memory that grows automatically as elements are added. It is built on top of a raw fixed-size array (allocated with `new[]`), but unlike a plain array it tracks two quantities: `size` (number of elements actually stored) and `capacity` (number of slots currently allocated). When `size` reaches `capacity`, the array allocates a new, larger buffer (typically double the old capacity), copies the existing elements over, and frees the old buffer. This "capacity doubling" strategy is exactly how `std::vector` works internally, and implementing it from scratch is the goal here.

Because the underlying storage is contiguous, elements can be accessed in O(1) via pointer arithmetic (`data[i]`), and the array has excellent cache locality compared to linked structures.

## Operations & Complexity
| Operation | Time | Space |
|---|---|---|
| `operator[]` (access) | O(1) | O(1) |
| `push_back` (amortized) | O(1) amortized, O(n) worst case (on resize) | O(1) amortized extra |
| `pop_back` | O(1) | O(1) |
| `insert(index, val)` | O(n) (shift elements right) | O(1) |
| `erase(index)` | O(n) (shift elements left) | O(1) |
| `size()` / `capacity()` | O(1) | O(1) |
| `resize/grow` (reallocate + copy) | O(n) | O(n) new buffer |

## When It's Used in Interviews
- Any problem stating "array" or "in-place" operations (two-pointer, sliding window) assumes this structure.
- When you need O(1) random access by index (unlike a linked list).
- When the interviewer probes "how would you implement `std::vector`?" — expects capacity doubling and amortized analysis.
- Problems involving in-place compaction (remove duplicates, move zeroes) rely on understanding shifting costs.

## Trade-offs
- **vs Linked List**: Dynamic array gives O(1) random access and better cache locality, but insertion/deletion in the middle is O(n) (shifting) versus O(1) for a linked list once you have a node pointer. Linked lists avoid the occasional O(n) reallocation cost but have O(n) access and pointer-chasing overhead.
- **vs Fixed Array**: Dynamic array trades a small amount of wasted space (unused capacity) and occasional O(n) resize cost for the convenience of unbounded growth.
- Amortized doubling keeps the *average* cost of `push_back` at O(1) even though individual calls can be O(n); this is proven via the aggregate/accounting method.

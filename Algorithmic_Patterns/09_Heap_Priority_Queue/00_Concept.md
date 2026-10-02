# Heap / Priority Queue

## Pattern Overview
A heap (`std::priority_queue`) keeps the minimum or maximum element accessible in O(1), with O(log n) insertion/removal, making it the tool of choice for "running extreme" queries without re-sorting the whole collection. Common uses include bounded top-k heaps, the two-heap median-of-a-stream pattern, and merging k sorted sequences.

## When to Use It
- The problem asks for the "kth largest/smallest", "top k", or "k closest" elements.
- You need the running minimum or maximum of a dynamic (streaming) collection, where elements are added over time and you repeatedly need the extreme value.
- You need to merge multiple already-sorted sequences (lists, arrays, files) efficiently.
- The problem involves a "median of a stream" or any scenario needing quick access to the middle of a growing dataset.
- You need to greedily pick the "most frequent", "most remaining", or "highest priority" item at each step (e.g., task scheduling, reorganizing strings, Dijkstra's shortest path).
- Sorting the entire input would work but is overkill — you only need partial ordering or the top/bottom few elements.

## Core Idea
A heap (implemented in C++ via `std::priority_queue`) is a binary tree stored in an array that keeps either the minimum (min-heap) or maximum (max-heap) element at the root, accessible in O(1), with O(log n) insertion and removal. The key mental model for interviews is: a heap lets you maintain a "running extreme" efficiently without re-sorting the whole collection every time the data changes.

For "top k" style problems, the classic trick is to maintain a heap bounded to size k rather than pushing everything and sorting. To find the k *largest* elements, you counter-intuitively use a **min-heap** of size k: push every element, and whenever the heap exceeds size k, pop the minimum. Whatever survives at the end is exactly the k largest, and the top of the heap is the smallest of that set (useful for streaming "kth largest" queries). Symmetrically, use a **max-heap** of size k to find the k smallest elements. This bounded-heap trick keeps the heap small (O(k) space) and the total work at O(n log k) instead of O(n log n).

For problems needing the median of a stream, the two-heap pattern is standard: a max-heap holds the smaller half of the numbers, a min-heap holds the larger half, and you rebalance after every insertion so their sizes differ by at most one. The median is then either the top of the larger heap, or the average of both tops.

For merging k sorted structures (lists, arrays, iterators), push one "current" element per source into a min-heap keyed by value. Repeatedly pop the smallest, output it, and push the next element from that same source. This turns an O(k) linear scan per step into an O(log k) heap operation, giving O(N log k) total for N total elements.

C++'s `priority_queue` is a max-heap by default; pass `greater<T>` as the comparator for a min-heap, or a custom lambda/struct comparator for complex objects (e.g., pointers compared by an inner field, or a `pair` where you want to compare only one element).

## Complexity
- Time: O(log n) per push/pop; O(n log k) for bounded top-k processing of n items; O(N log k) for merging k sources with N total elements; two-heap median gives O(log n) per insert and O(1) per query.
- Space: O(n) to hold all elements in a heap, or O(k) for a bounded top-k heap.

## C++ Template
```cpp
#include <bits/stdc++.h>
using namespace std;

// Generic "top k" template: find the k largest elements using a bounded min-heap.
vector<int> topK(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap; // min-heap, size <= k
    for (int x : nums) {
        minHeap.push(x);
        if ((int)minHeap.size() > k) {
            minHeap.pop(); // evict the current smallest, keeping only the k largest so far
        }
    }
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top());
        minHeap.pop();
    }
    return result; // contains the k largest elements (unsorted order)
}

// Generic heap with a custom comparator (e.g., pair keyed by a secondary field).
struct Compare {
    bool operator()(const pair<int,int>& a, const pair<int,int>& b) {
        return a.first > b.first; // min-heap on .first
    }
};
// priority_queue<pair<int,int>, vector<pair<int,int>>, Compare> pq;
```

## Common Pitfalls
- Forgetting that `std::priority_queue` is a **max-heap by default**; using it unmodified when a min-heap was needed (or vice versa).
- Using a max-heap of size k when a min-heap of size k was needed for "k largest" problems (the trick is intentionally inverted — think about what you evict, not what you keep).
- Storing raw values in the heap when the tiebreak or secondary ordering matters (e.g., merging linked lists needs a comparator on `node->val`, not the pointer itself).
- Forgetting to rebalance both heaps in the two-heap median pattern after every insertion, which silently corrupts the median.
- Assuming heap iteration order is sorted — a heap only guarantees the root is the extreme value, not that the whole structure is sorted; you must pop repeatedly to extract elements in order.

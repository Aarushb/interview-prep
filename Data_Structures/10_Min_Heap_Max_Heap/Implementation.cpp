/*
PROBLEM: Binary Heap (Min-Heap / Max-Heap) — Custom Implementation
DESCRIPTION: Implement a binary heap from scratch backed by a dynamic array (not
std::priority_queue), supporting push, pop (extract top), top/peek, sift-up, sift-down, and
buildHeap(vector) in O(n). Make it configurable for min-heap or max-heap behavior via a
comparator template parameter.
CONSTRAINTS: General-purpose implementation over comparable elements (int used in the demo);
operations should be correct for arbitrary sequences of calls, including popping from an empty
heap (guarded) and building from an already-sorted or reverse-sorted vector.
EXAMPLE INPUT/OUTPUT: See main() below for a runnable usage demo.
*/

/*
APPROACH:
The heap is stored as a `vector<T>` representing a complete binary tree: for a node at index i,
its children are at 2*i+1 and 2*i+2, and its parent is at (i-1)/2. The heap property is defined
by a comparator `Comp` (default std::less<T> for a max-heap, or std::greater<T> for a min-heap):
a node's value must never satisfy `comp(parent, node)` — i.e. the parent must never be "worse"
than its children according to comp. Concretely with std::less, `comp(parent, child)` being true
means parent < child, which would violate max-heap order, so we swap.

- push(val): append val to the back of the array (next open leaf slot), then sift-up: repeatedly
  compare with its parent and swap while the heap property is violated, moving the new element
  up toward the root. O(log n) since the tree has O(log n) levels.
- pop(): the root (index 0) is the top. Move the LAST element into index 0, shrink the array by
  one, then sift-down from the root: repeatedly compare with children and swap with whichever
  child violates the property most, until no violation remains. O(log n).
- top(): return element at index 0. O(1).
- buildHeap(vector): instead of pushing n elements one at a time (O(n log n)), copy the vector in
  directly, then sift-down starting from the last non-leaf node (index n/2 - 1) down to index 0.
  Leaves (roughly the bottom half of the array) trivially satisfy the heap property already, so
  we skip them. This is O(n) overall (not O(n log n)) because most nodes are near the bottom and
  sift-down work shrinks geometrically as height decreases — the sum of (nodes at height h) *
  (sift-down cost ~ h) across all levels converges to O(n), a classic amortized-analysis result.
*/

#include <bits/stdc++.h>
using namespace std;

template <typename T, typename Comp = less<T>>
class BinaryHeap {
private:
    vector<T> data;
    Comp comp;

    void siftUp(int idx) {
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (comp(data[parent], data[idx])) {
                swap(data[parent], data[idx]);
                idx = parent;
            } else {
                break;
            }
        }
    }

    void siftDown(int idx) {
        int n = (int)data.size();
        while (true) {
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            int best = idx;

            if (left < n && comp(data[best], data[left])) best = left;
            if (right < n && comp(data[best], data[right])) best = right;

            if (best == idx) break;
            swap(data[idx], data[best]);
            idx = best;
        }
    }

public:
    BinaryHeap() {}

    // Builds a heap from an existing vector in O(n) time.
    void buildHeap(vector<T> input) {
        data = move(input);
        for (int i = (int)data.size() / 2 - 1; i >= 0; i--) {
            siftDown(i);
        }
    }

    void push(const T& val) {
        data.push_back(val);
        siftUp((int)data.size() - 1);
    }

    void pop() {
        if (data.empty()) return;
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) siftDown(0);
    }

    const T& top() const {
        return data.front();
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }
};

int main() {
    // Max-heap (default comparator: less<int>)
    cout << "-- Max-Heap --" << endl;
    BinaryHeap<int> maxHeap;
    for (int v : {5, 1, 9, 3, 7, 2}) maxHeap.push(v);
    cout << "Popped in order: ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;

    // Min-heap (comparator: greater<int> flips the ordering)
    cout << "-- Min-Heap --" << endl;
    BinaryHeap<int, greater<int>> minHeap;
    for (int v : {5, 1, 9, 3, 7, 2}) minHeap.push(v);
    cout << "Popped in order: ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;

    // buildHeap demo: O(n) construction from an existing vector
    cout << "-- buildHeap (min-heap) --" << endl;
    BinaryHeap<int, greater<int>> built;
    built.buildHeap({8, 4, 6, 1, 9, 2, 7});
    cout << "Top after buildHeap: " << built.top() << endl; // 1
    cout << "Popped in order: ";
    while (!built.empty()) {
        cout << built.top() << " ";
        built.pop();
    }
    cout << endl;

    return 0;
}

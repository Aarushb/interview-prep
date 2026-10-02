/*
PROBLEM 1: Kth Largest Element in an Array (LeetCode 215)
DESCRIPTION: Given an integer array `nums` and an integer `k`, return the kth largest element in
the array (kth largest in sorted order, not the kth distinct element).
CONSTRAINTS: 1 <= k <= nums.length <= 10^5, -10^4 <= nums[i] <= 10^4.
EXAMPLE INPUT/OUTPUT:
  Input: nums = [3,2,1,5,6,4], k = 2
  Output: 5
  Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
  Output: 4
*/

/*
APPROACH:
Use a MIN-heap (our own BinaryHeap<int, greater<int>>) of size at most k. Push each number; if the
heap grows beyond size k, pop the minimum. After processing all numbers, the heap holds exactly the
k largest numbers seen, and its top (the minimum of that group) is the kth largest overall — every
element remaining in the heap is >= it, and everything popped along the way was smaller than at
least k other elements. Time: O(n log k) since each push/pop on a heap of size k is O(log k) and we
do this for all n elements — much better than sorting the whole array (O(n log n)) when k is small.
*/

#include <bits/stdc++.h>
using namespace std;

// Reuse the same hand-rolled heap design as Implementation.cpp.
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
            } else break;
        }
    }

    void siftDown(int idx) {
        int n = (int)data.size();
        while (true) {
            int left = 2 * idx + 1, right = 2 * idx + 2, best = idx;
            if (left < n && comp(data[best], data[left])) best = left;
            if (right < n && comp(data[best], data[right])) best = right;
            if (best == idx) break;
            swap(data[idx], data[best]);
            idx = best;
        }
    }

public:
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
    const T& top() const { return data.front(); }
    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }
};

int findKthLargest(vector<int>& nums, int k) {
    BinaryHeap<int, greater<int>> minHeap; // min-heap of the k largest elements seen so far
    for (int num : nums) {
        minHeap.push(num);
        if ((int)minHeap.size() > k) {
            minHeap.pop();
        }
    }
    return minHeap.top();
}

/*
PROBLEM 2: Connect Ropes to Minimize Cost
DESCRIPTION: Given the lengths of n ropes, connect them into one rope. The cost of connecting two
ropes is the sum of their lengths. Find the minimum total cost to connect all ropes into one.
CONSTRAINTS: 1 <= n <= 10^5, 1 <= rope length <= 10^4.
EXAMPLE INPUT/OUTPUT:
  Input: ropes = [4, 3, 2, 6]
  Output: 29
    (connect 2+3=5, cost 5; connect 5+4=9, cost 9; connect 9+6=15, cost 15; total 5+9+15=29)
*/

/*
APPROACH:
Greedy: always connect the two currently-shortest ropes first (this minimizes how many times a
long rope's length gets "re-paid" as part of future connection costs). A MIN-heap makes "find the
two shortest" an O(log n) operation instead of O(n) linear scans. buildHeap all rope lengths in
O(n), then repeatedly: pop the two smallest, add their sum to the total cost, push the sum back as
a new "rope" (representing the merged rope), until only one rope (the fully merged one) remains.
Time: O(n log n) — n-1 merge steps, each doing O(1) pops/O(log n) pushes.
*/

int connectRopes(vector<int> ropes) {
    BinaryHeap<int, greater<int>> minHeap; // min-heap
    for (int len : ropes) minHeap.push(len);

    int totalCost = 0;
    while (minHeap.size() > 1) {
        int first = minHeap.top();
        minHeap.pop();
        int second = minHeap.top();
        minHeap.pop();
        int mergedCost = first + second;
        totalCost += mergedCost;
        minHeap.push(mergedCost);
    }
    return totalCost;
}

int main() {
    // Problem 1: Kth Largest Element in an Array
    {
        vector<int> nums = {3, 2, 1, 5, 6, 4};
        cout << "Kth Largest (k=2): " << findKthLargest(nums, 2) << endl; // Expected: 5
    }
    {
        vector<int> nums = {3, 2, 3, 1, 2, 4, 5, 5, 6};
        cout << "Kth Largest (k=4): " << findKthLargest(nums, 4) << endl; // Expected: 4
    }

    // Problem 2: Connect Ropes to Minimize Cost
    {
        vector<int> ropes = {4, 3, 2, 6};
        cout << "Min Cost to Connect Ropes: " << connectRopes(ropes) << endl; // Expected: 29
    }
    {
        vector<int> ropes = {1, 2, 3, 4, 5};
        cout << "Min Cost to Connect Ropes: " << connectRopes(ropes) << endl; // Expected: 33
    }

    return 0;
}

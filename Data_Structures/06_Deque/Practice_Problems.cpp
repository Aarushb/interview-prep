/*
PROBLEM 1: Sliding Window Maximum (LeetCode 239)
DESCRIPTION: Given an array nums and a sliding window of size k moving from left to
right, return the maximum value in each window.
CONSTRAINTS: 1 <= k <= nums.size(); values fit in int.
EXAMPLE: nums = [1,3,-1,-3,5,3,6,7], k = 3 -> [3,3,5,5,6,7]
*/

/*
APPROACH:
Maintain a monotonic deque of INDICES into nums, kept in decreasing order of their
values (front of deque = index of current window's maximum). For each new index i:
  1. Pop from the back while nums[back] <= nums[i] — those elements can never be the
     max again since nums[i] is later and at least as large.
  2. Push i to the back.
  3. Pop from the front if it has fallen out of the window (front index <= i - k).
  4. Once i >= k - 1, the front of the deque is the max for the current window.
Each index is pushed and popped at most once, so this runs in O(n) total despite the
nested-looking while loop.
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq; // stores indices, values in decreasing order
    vector<int> result;

    for (int i = 0; i < (int)nums.size(); i++) {
        // Remove indices whose values are smaller than the current value
        while (!dq.empty() && nums[dq.back()] <= nums[i]) {
            dq.pop_back();
        }
        dq.push_back(i);

        // Remove front index if it's outside the current window
        if (dq.front() <= i - k) {
            dq.pop_front();
        }

        // Window is fully formed once we've processed at least k elements
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }

    return result;
}

/*
PROBLEM 2: Design Circular Deque (LeetCode 641)
DESCRIPTION: Design a fixed-capacity circular double-ended queue supporting
insertFront, insertLast, deleteFront, deleteLast, getFront, getRear, isEmpty, isFull.
CONSTRAINTS: Capacity k is fixed at construction; all operations must be O(1).
EXAMPLE: MyCircularDeque(3); insertLast(1); insertLast(2); insertFront(3);
         insertFront(4) -> false (full); getRear() -> 2
*/

/*
APPROACH:
Classic fixed-size ring buffer with head/count tracking, same mechanics as the Deque
class above but with a hard capacity cap (insert operations return false instead of
resizing when full). head marks the front slot; the rear slot is
(head + count - 1) % capacity.
*/

class MyCircularDeque {
private:
    vector<int> buf;
    int head, count, capacity;

public:
    MyCircularDeque(int k) : buf(k), head(0), count(0), capacity(k) {}

    bool insertFront(int value) {
        if (isFull()) return false;
        head = (head - 1 + capacity) % capacity;
        buf[head] = value;
        count++;
        return true;
    }

    bool insertLast(int value) {
        if (isFull()) return false;
        int tail = (head + count) % capacity;
        buf[tail] = value;
        count++;
        return true;
    }

    bool deleteFront() {
        if (isEmpty()) return false;
        head = (head + 1) % capacity;
        count--;
        return true;
    }

    bool deleteLast() {
        if (isEmpty()) return false;
        count--;
        return true;
    }

    int getFront() {
        if (isEmpty()) return -1;
        return buf[head];
    }

    int getRear() {
        if (isEmpty()) return -1;
        return buf[(head + count - 1) % capacity];
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == capacity;
    }
};

int main() {
    cout << "--- Sliding Window Maximum ---\n";
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> result = maxSlidingWindow(nums, 3);
    cout << "result: ";
    for (int v : result) cout << v << " ";
    cout << "\n(expected: 3 3 5 5 6 7)\n\n";

    cout << "--- Design Circular Deque ---\n";
    MyCircularDeque dq(3);
    cout << "insertLast(1): " << dq.insertLast(1) << " (expected 1)\n";
    cout << "insertLast(2): " << dq.insertLast(2) << " (expected 1)\n";
    cout << "insertFront(3): " << dq.insertFront(3) << " (expected 1)\n";
    cout << "insertFront(4): " << dq.insertFront(4) << " (expected 0, deque full)\n";
    cout << "getRear(): " << dq.getRear() << " (expected 2)\n";
    cout << "isFull(): " << dq.isFull() << " (expected 1)\n";
    cout << "deleteLast(): " << dq.deleteLast() << " (expected 1)\n";
    cout << "insertFront(4): " << dq.insertFront(4) << " (expected 1)\n";
    cout << "getFront(): " << dq.getFront() << " (expected 4)\n";

    return 0;
}

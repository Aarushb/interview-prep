/*
PROBLEM 1: Implement Stack using Queues (LeetCode 225)
DESCRIPTION: Implement a LIFO stack using only two FIFO queues. The stack must support
push, pop, top, and empty, using only standard queue operations (push/enqueue,
peek/front, pop/dequeue, size, and empty).
CONSTRAINTS: At most a few hundred calls; values fit in int.
EXAMPLE: push(1), push(2), top() -> 2, pop() -> 2, pop() -> 1, empty() -> true
*/

/*
APPROACH:
Use two queues, q1 (main) and q2 (helper). To push x so that it ends up at the "front"
(so pop/top are O(1) at the cost of an O(n) push):
  1. Enqueue x into q2.
  2. Move all elements from q1 into q2 (preserving order), so x ends up first.
  3. Swap q1 and q2.
Now q1's front is always the most-recently-pushed element (LIFO order), so pop() and
top() are simply dequeue()/front() on q1 — O(1). push() is O(n).
*/

#include <bits/stdc++.h>
using namespace std;

class MyStack {
private:
    queue<int> q1, q2;

public:
    void push(int x) {
        q2.push(x);
        while (!q1.empty()) {
            q2.push(q1.front());
            q1.pop();
        }
        swap(q1, q2);
    }

    int pop() {
        int val = q1.front();
        q1.pop();
        return val;
    }

    int top() const {
        return q1.front();
    }

    bool empty() const {
        return q1.empty();
    }
};

/*
PROBLEM 2: Moving Average from Data Stream (LeetCode 346)
DESCRIPTION: Given a stream of integers and a window size, calculate the moving average
of all integers in the sliding window.
CONSTRAINTS: size is a positive integer; next() is called repeatedly with new values.
EXAMPLE: MovingAverage(3); next(1) -> 1.0; next(10) -> 5.5; next(3) -> 4.6667; next(5) -> 6.0
*/

/*
APPROACH:
Keep a queue holding at most `size` most-recent values plus a running `sum`. On next(x):
push x and add to sum; if the queue exceeds `size`, pop the oldest value and subtract it
from sum. The average is sum / current window length. Every call is O(1).
*/

class MovingAverage {
private:
    queue<int> window;
    int maxSize;
    double sum;

public:
    MovingAverage(int size) : maxSize(size), sum(0.0) {}

    double next(int val) {
        window.push(val);
        sum += val;
        if ((int)window.size() > maxSize) {
            sum -= window.front();
            window.pop();
        }
        return sum / window.size();
    }
};

int main() {
    cout << "--- Implement Stack using Queues ---\n";
    MyStack st;
    st.push(1);
    st.push(2);
    st.push(3);
    cout << "top: " << st.top() << " (expected 3)\n";
    cout << "pop: " << st.pop() << " (expected 3)\n";
    cout << "pop: " << st.pop() << " (expected 2)\n";
    cout << "empty? " << (st.empty() ? "yes" : "no") << " (expected no)\n";
    cout << "pop: " << st.pop() << " (expected 1)\n";
    cout << "empty? " << (st.empty() ? "yes" : "no") << " (expected yes)\n\n";

    cout << "--- Moving Average from Data Stream ---\n";
    MovingAverage ma(3);
    cout << ma.next(1) << " (expected 1)\n";
    cout << ma.next(10) << " (expected 5.5)\n";
    cout << ma.next(3) << " (expected 4.66667)\n";
    cout << ma.next(5) << " (expected 6)\n";

    return 0;
}

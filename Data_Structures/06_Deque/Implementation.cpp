/*
PROBLEM: Deque (Double-Ended Queue) — Custom Implementation
DESCRIPTION: Implement a double-ended queue from scratch, backed by a circular (ring)
buffer, supporting push_front, push_back, pop_front, pop_back, front, back, empty, and
size, without relying on std::deque.
CONSTRAINTS: General-purpose implementation; operations should be correct for arbitrary
sequences of calls at either end, and the buffer must auto-resize when it fills up.
EXAMPLE INPUT/OUTPUT: See main() below for a runnable usage demo.
*/

/*
APPROACH:
Same ring-buffer idea as the Queue implementation, but now the "front" pointer (head)
can move in both directions:
- push_back(x): write at (head + count) % capacity, increment count. Symmetric to
  Queue::enqueue.
- push_front(x): move head one step backward — head = (head - 1 + capacity) % capacity —
  then write x at the new head, increment count. Adding `capacity` before the modulo
  avoids negative indices in C++ (where -1 % capacity is implementation-defined/negative).
- pop_back(): decrement count, read/return buf[(head + count) % capacity] (the old
  tail index).
- pop_front(): read/return buf[head], then advance head = (head + 1) % capacity,
  decrement count. Symmetric to Queue::dequeue.

Because head can now wrap in either direction, growth (resize) works the same way as in
Queue: allocate a new array of double the capacity, copy elements out in logical order
starting at index 0 (reading from (head + i) % capacity for i in [0, count)), and reset
head to 0. All four push/pop operations remain amortized O(1) since growth is
geometric (doubling), same argument as std::vector.
*/

#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Deque {
private:
    vector<T> buf;
    int head;
    int count;
    int capacity;

    void resize(int newCapacity) {
        vector<T> newBuf(newCapacity);
        for (int i = 0; i < count; i++) {
            newBuf[i] = buf[(head + i) % capacity];
        }
        buf = move(newBuf);
        head = 0;
        capacity = newCapacity;
    }

    void ensureCapacity() {
        if (count == capacity) {
            resize(capacity * 2);
        }
    }

public:
    Deque(int initialCapacity = 4) : buf(initialCapacity), head(0), count(0), capacity(initialCapacity) {}

    void push_back(const T& val) {
        ensureCapacity();
        int tail = (head + count) % capacity;
        buf[tail] = val;
        count++;
    }

    void push_front(const T& val) {
        ensureCapacity();
        head = (head - 1 + capacity) % capacity;
        buf[head] = val;
        count++;
    }

    T pop_front() {
        if (empty()) throw runtime_error("pop_front() called on empty deque");
        T val = buf[head];
        head = (head + 1) % capacity;
        count--;
        return val;
    }

    T pop_back() {
        if (empty()) throw runtime_error("pop_back() called on empty deque");
        count--;
        int tail = (head + count) % capacity;
        return buf[tail];
    }

    T front() const {
        if (empty()) throw runtime_error("front() called on empty deque");
        return buf[head];
    }

    T back() const {
        if (empty()) throw runtime_error("back() called on empty deque");
        return buf[(head + count - 1) % capacity];
    }

    bool empty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }
};

int main() {
    Deque<int> dq(2); // start tiny so we can observe resizing

    dq.push_back(10);
    dq.push_front(5);
    dq.push_back(20);   // forces a resize
    dq.push_front(1);

    cout << "size: " << dq.size() << " (expected 4)\n";
    cout << "front: " << dq.front() << " (expected 1)\n";
    cout << "back: " << dq.back() << " (expected 20)\n";

    cout << "pop_front: " << dq.pop_front() << " (expected 1)\n";
    cout << "pop_back: " << dq.pop_back() << " (expected 20)\n";

    dq.push_back(30);
    dq.push_front(2);

    cout << "remaining front-to-back: ";
    Deque<int> copy = dq;
    while (!copy.empty()) {
        cout << copy.pop_front() << " ";
    }
    cout << "\n";

    cout << "empty? " << (dq.empty() ? "yes" : "no") << " (expected no)\n";

    return 0;
}

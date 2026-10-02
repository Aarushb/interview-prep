/*
PROBLEM: Queue — Custom Implementation
DESCRIPTION: Implement a FIFO queue from scratch, backed by a circular (ring) buffer,
supporting enqueue, dequeue, front, empty, and size, without relying on std::queue.
CONSTRAINTS: General-purpose implementation; operations should be correct for arbitrary
sequences of calls, and the buffer must auto-resize when it fills up.
EXAMPLE INPUT/OUTPUT: See main() below for a runnable usage demo.
*/

/*
APPROACH:
Store elements in a fixed-capacity array `buf`. Maintain `head` (index of the front
element) and `count` (number of elements currently stored); the tail insertion point is
computed as (head + count) % capacity, so we don't need a separate tail variable that
could go stale.

- enqueue(x): if count == capacity, grow the buffer (allocate a new array of double the
  capacity, copy elements out in logical FIFO order starting at head, reset head to 0),
  then write x at (head + count) % capacity and increment count. Amortized O(1), same
  argument as std::vector's doubling strategy.
- dequeue(): read buf[head], advance head = (head + 1) % capacity, decrement count. O(1).
- front(): return buf[head]. O(1).
- empty()/size(): O(1), just check count.

The "wraparound" is the key idea: indices don't reset to 0 on dequeue, they just cycle
through the array, so we never need to shift existing elements.
*/

#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Queue {
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

public:
    Queue(int initialCapacity = 4) : buf(initialCapacity), head(0), count(0), capacity(initialCapacity) {}

    void enqueue(const T& val) {
        if (count == capacity) {
            resize(capacity * 2);
        }
        int tail = (head + count) % capacity;
        buf[tail] = val;
        count++;
    }

    T dequeue() {
        if (empty()) throw runtime_error("dequeue() called on empty queue");
        T val = buf[head];
        head = (head + 1) % capacity;
        count--;
        return val;
    }

    T front() const {
        if (empty()) throw runtime_error("front() called on empty queue");
        return buf[head];
    }

    bool empty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }
};

int main() {
    Queue<int> q(2); // start tiny so we can observe resizing

    cout << "empty? " << (q.empty() ? "yes" : "no") << "\n";

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30); // forces a resize (capacity was 2)
    q.enqueue(40);

    cout << "size after 4 enqueues: " << q.size() << "\n";
    cout << "front: " << q.front() << "\n";

    cout << "dequeue: " << q.dequeue() << "\n"; // 10
    cout << "dequeue: " << q.dequeue() << "\n"; // 20

    q.enqueue(50); // reuse wrapped-around space
    q.enqueue(60);

    cout << "remaining elements in FIFO order: ";
    while (!q.empty()) {
        cout << q.dequeue() << " ";
    }
    cout << "\n";

    cout << "empty? " << (q.empty() ? "yes" : "no") << "\n";

    return 0;
}

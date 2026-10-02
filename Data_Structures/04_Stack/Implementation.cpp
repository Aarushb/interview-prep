/*
PROBLEM: Stack — Custom Implementation
DESCRIPTION: Implement a stack from scratch backed by a hand-rolled dynamic array (not std::stack
or std::vector), supporting push, pop, top, empty, size.
CONSTRAINTS: General-purpose implementation; operations should be correct for arbitrary sequences of calls.
EXAMPLE INPUT/OUTPUT: See main() below for a runnable usage demo.
*/

/*
APPROACH:
The stack is backed by a raw heap-allocated int buffer (`data`), tracking `_size` (elements in use)
and `_capacity` (allocated slots), exactly like a minimal dynamic array. `push` appends at index
`_size` and grows the buffer (doubling capacity) when full, giving amortized O(1) push. `pop` and
`top` operate on index `_size - 1` (the "top" of the stack), both O(1) since no shifting is needed —
LIFO access only ever touches the highest occupied index. This intentionally reimplements a small
dynamic array here (rather than reusing DynamicArray from another folder) to keep the stack
self-contained.
*/

#include <bits/stdc++.h>
using namespace std;

class Stack {
    int* data;
    int _size;
    int _capacity;

    void grow() {
        int newCapacity = (_capacity == 0) ? 1 : _capacity * 2;
        int* newData = new int[newCapacity];
        for (int i = 0; i < _size; i++) newData[i] = data[i];
        delete[] data;
        data = newData;
        _capacity = newCapacity;
    }

public:
    Stack() : data(nullptr), _size(0), _capacity(0) {}

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    ~Stack() {
        delete[] data;
    }

    // Amortized O(1).
    void push(int val) {
        if (_size == _capacity) grow();
        data[_size++] = val;
    }

    // O(1).
    void pop() {
        if (_size == 0) throw out_of_range("pop on empty stack");
        _size--;
    }

    // O(1).
    int top() const {
        if (_size == 0) throw out_of_range("top on empty stack");
        return data[_size - 1];
    }

    bool empty() const { return _size == 0; }
    int size() const { return _size; }

    void print() const {
        cout << "[bottom -> top]: [";
        for (int i = 0; i < _size; i++) {
            cout << data[i];
            if (i + 1 < _size) cout << ", ";
        }
        cout << "]\n";
    }
};

int main() {
    Stack s;

    cout << "-- push 1,2,3,4 --\n";
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.print(); // [bottom -> top]: [1, 2, 3, 4]

    cout << "-- top --\n";
    cout << "top = " << s.top() << "\n"; // 4

    cout << "-- pop --\n";
    s.pop();
    s.print(); // [1, 2, 3]

    cout << "-- push 99 --\n";
    s.push(99);
    s.print(); // [1, 2, 3, 99]

    cout << "-- size / empty --\n";
    cout << "size = " << s.size() << ", empty = " << (s.empty() ? "true" : "false") << "\n";

    while (!s.empty()) s.pop();
    cout << "-- popped everything --\n";
    cout << "empty = " << (s.empty() ? "true" : "false") << "\n";

    return 0;
}

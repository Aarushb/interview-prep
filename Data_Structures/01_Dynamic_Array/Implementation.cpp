/*
PROBLEM: Dynamic Array — Custom Implementation
DESCRIPTION: Implement a resizable array class from scratch (like a simplified std::vector),
supporting push_back, pop_back, operator[], size(), capacity(), insert(index, val), erase(index),
without relying on the STL's built-in std::vector.
CONSTRAINTS: General-purpose implementation; operations should be correct for arbitrary sequences of calls.
EXAMPLE INPUT/OUTPUT: See main() below for a runnable usage demo.
*/

/*
APPROACH:
The class holds a raw pointer `data` to a heap-allocated buffer, an integer `_size` (number of
elements actually in use) and `_capacity` (number of allocated slots). When `push_back` is called
and `_size == _capacity`, we `grow()`: allocate a new buffer of double the capacity (or 1 if
capacity was 0), copy over the existing elements, delete the old buffer, and swap pointers. This
gives push_back an amortized O(1) cost, since the total copying work across n pushes sums to O(n)
(geometric series), even though any single push that triggers a resize costs O(n).

insert(index, val) and erase(index) both need O(n) element shifting because the array must stay
contiguous: insert shifts everything from `index` onward one slot right (after growing if needed),
erase shifts everything after `index` one slot left.

The Rule of Three (copy constructor, copy assignment, destructor) is implemented since the class
manages raw memory manually.
*/

#include <bits/stdc++.h>
using namespace std;

class DynamicArray {
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
    DynamicArray() : data(nullptr), _size(0), _capacity(0) {}

    // Rule of three: manual memory needs a copy ctor / copy assignment / destructor.
    DynamicArray(const DynamicArray& other) : data(nullptr), _size(0), _capacity(0) {
        if (other._capacity > 0) {
            data = new int[other._capacity];
            _capacity = other._capacity;
        }
        _size = other._size;
        for (int i = 0; i < _size; i++) data[i] = other.data[i];
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        delete[] data;
        data = nullptr;
        _size = 0;
        _capacity = 0;
        if (other._capacity > 0) {
            data = new int[other._capacity];
            _capacity = other._capacity;
        }
        _size = other._size;
        for (int i = 0; i < _size; i++) data[i] = other.data[i];
        return *this;
    }

    ~DynamicArray() {
        delete[] data;
    }

    // Amortized O(1): doubles capacity when full.
    void push_back(int val) {
        if (_size == _capacity) grow();
        data[_size++] = val;
    }

    // O(1): just decrement size; memory is not shrunk.
    void pop_back() {
        if (_size == 0) throw out_of_range("pop_back on empty array");
        _size--;
    }

    // O(1) random access.
    int& operator[](int index) {
        if (index < 0 || index >= _size) throw out_of_range("index out of range");
        return data[index];
    }

    const int& operator[](int index) const {
        if (index < 0 || index >= _size) throw out_of_range("index out of range");
        return data[index];
    }

    int size() const { return _size; }
    int capacity() const { return _capacity; }
    bool empty() const { return _size == 0; }

    // O(n): shift elements at [index, size) one slot to the right.
    void insert(int index, int val) {
        if (index < 0 || index > _size) throw out_of_range("insert index out of range");
        if (_size == _capacity) grow();
        for (int i = _size; i > index; i--) data[i] = data[i - 1];
        data[index] = val;
        _size++;
    }

    // O(n): shift elements at (index, size) one slot to the left.
    void erase(int index) {
        if (index < 0 || index >= _size) throw out_of_range("erase index out of range");
        for (int i = index; i < _size - 1; i++) data[i] = data[i + 1];
        _size--;
    }

    void print() const {
        cout << "[";
        for (int i = 0; i < _size; i++) {
            cout << data[i];
            if (i + 1 < _size) cout << ", ";
        }
        cout << "] (size=" << _size << ", capacity=" << _capacity << ")\n";
    }
};

int main() {
    DynamicArray arr;

    cout << "-- push_back --\n";
    for (int i = 1; i <= 5; i++) arr.push_back(i * 10);
    arr.print(); // [10, 20, 30, 40, 50] (size=5, capacity=8)

    cout << "-- operator[] read/write --\n";
    cout << "arr[2] = " << arr[2] << "\n"; // 30
    arr[2] = 99;
    arr.print(); // [10, 20, 99, 40, 50]

    cout << "-- insert(1, 777) --\n";
    arr.insert(1, 777);
    arr.print(); // [10, 777, 20, 99, 40, 50]

    cout << "-- erase(3) --\n";
    arr.erase(3);
    arr.print(); // [10, 777, 20, 40, 50]

    cout << "-- pop_back --\n";
    arr.pop_back();
    arr.print(); // [10, 777, 20, 40]

    cout << "-- size/capacity --\n";
    cout << "size=" << arr.size() << " capacity=" << arr.capacity() << "\n";

    cout << "-- copy semantics --\n";
    DynamicArray copy = arr;
    copy.push_back(999);
    cout << "original: "; arr.print();
    cout << "copy:     "; copy.print();

    return 0;
}

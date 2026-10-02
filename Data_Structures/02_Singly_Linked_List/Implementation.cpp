/*
PROBLEM: Singly Linked List — Custom Implementation
DESCRIPTION: Implement a singly linked list class from scratch (Node struct with val + next),
supporting push_front, push_back, pop_front, insert_at(index, val), erase_at(index), find(val),
and traversal/print, without relying on the STL's std::forward_list or std::list.
CONSTRAINTS: General-purpose implementation; operations should be correct for arbitrary sequences of calls.
EXAMPLE INPUT/OUTPUT: See main() below for a runnable usage demo.
*/

/*
APPROACH:
Each Node is a heap-allocated struct holding an int `val` and a `Node*` pointer `next`. The list
class keeps a `head` pointer, a `tail` pointer (so push_back is O(1) instead of O(n)), and a `_size`
counter. push_front/pop_front only touch head and are O(1). insert_at/erase_at must walk from head
to the node just before the target index, which costs O(n), then perform an O(1) pointer relink.
The destructor walks the whole list freeing each node to avoid memory leaks (Rule of Three applies
since raw pointers are owned manually; copy ctor/assignment are disabled here via deletion since
deep-copy semantics aren't required for this exercise, only manual node ownership).
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(nullptr) {}
};

class SinglyLinkedList {
    Node* head;
    Node* tail;
    int _size;

public:
    SinglyLinkedList() : head(nullptr), tail(nullptr), _size(0) {}

    // Disable copying: this class owns raw node pointers manually and no deep-copy is needed here.
    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    ~SinglyLinkedList() {
        Node* cur = head;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    int size() const { return _size; }
    bool empty() const { return _size == 0; }

    // O(1): new node becomes head.
    void push_front(int val) {
        Node* n = new Node(val);
        n->next = head;
        head = n;
        if (!tail) tail = n; // list was empty
        _size++;
    }

    // O(1) thanks to tail pointer.
    void push_back(int val) {
        Node* n = new Node(val);
        if (!head) {
            head = tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
        _size++;
    }

    // O(1): remove head, advance to next node.
    void pop_front() {
        if (!head) throw out_of_range("pop_front on empty list");
        Node* old = head;
        head = head->next;
        if (!head) tail = nullptr; // list became empty
        delete old;
        _size--;
    }

    // O(n): walk to (index - 1), splice a new node in.
    void insert_at(int index, int val) {
        if (index < 0 || index > _size) throw out_of_range("insert_at index out of range");
        if (index == 0) { push_front(val); return; }
        if (index == _size) { push_back(val); return; }
        Node* prev = head;
        for (int i = 0; i < index - 1; i++) prev = prev->next;
        Node* n = new Node(val);
        n->next = prev->next;
        prev->next = n;
        _size++;
    }

    // O(n): walk to (index - 1), unlink the target node.
    void erase_at(int index) {
        if (index < 0 || index >= _size) throw out_of_range("erase_at index out of range");
        if (index == 0) { pop_front(); return; }
        Node* prev = head;
        for (int i = 0; i < index - 1; i++) prev = prev->next;
        Node* target = prev->next;
        prev->next = target->next;
        if (target == tail) tail = prev;
        delete target;
        _size--;
    }

    // O(n): linear search, returns index or -1.
    int find(int val) const {
        Node* cur = head;
        int idx = 0;
        while (cur) {
            if (cur->val == val) return idx;
            cur = cur->next;
            idx++;
        }
        return -1;
    }

    void print() const {
        Node* cur = head;
        cout << "[";
        while (cur) {
            cout << cur->val;
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
        cout << "] (size=" << _size << ")\n";
    }
};

int main() {
    SinglyLinkedList list;

    cout << "-- push_back 1,2,3 --\n";
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.print(); // [1 -> 2 -> 3]

    cout << "-- push_front 0 --\n";
    list.push_front(0);
    list.print(); // [0 -> 1 -> 2 -> 3]

    cout << "-- insert_at(2, 99) --\n";
    list.insert_at(2, 99);
    list.print(); // [0 -> 1 -> 99 -> 2 -> 3]

    cout << "-- find(99) --\n";
    cout << "index = " << list.find(99) << "\n"; // 2

    cout << "-- find(1000) --\n";
    cout << "index = " << list.find(1000) << "\n"; // -1

    cout << "-- erase_at(2) --\n";
    list.erase_at(2);
    list.print(); // [0 -> 1 -> 2 -> 3]

    cout << "-- pop_front --\n";
    list.pop_front();
    list.print(); // [1 -> 2 -> 3]

    cout << "size = " << list.size() << "\n";

    return 0;
}

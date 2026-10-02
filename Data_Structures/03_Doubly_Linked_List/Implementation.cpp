/*
PROBLEM: Doubly Linked List — Custom Implementation
DESCRIPTION: Implement a doubly linked list class from scratch (Node with val + prev + next),
supporting push_front, push_back, pop_front, pop_back, insert_at(index, val), erase_at(index), and
forward/backward traversal, without relying on the STL's std::list.
CONSTRAINTS: General-purpose implementation; operations should be correct for arbitrary sequences of calls.
EXAMPLE INPUT/OUTPUT: See main() below for a runnable usage demo.
*/

/*
APPROACH:
Each Node holds `val`, `prev`, and `next` pointers. The list keeps `head` and `tail` pointers plus a
`_size` counter, giving O(1) push/pop at both ends (unlike a singly linked list, pop_back is O(1)
here because tail->prev is directly available, no need to walk from head). insert_at/erase_at at an
arbitrary index still require an O(n) walk to locate the position, but once located, splicing is
O(1) pointer relinking that must correctly update both `next` and `prev` on the neighboring nodes.
The destructor walks and frees every node. Copying is disabled since this is an ownership-based
educational implementation.
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* prev;
    Node* next;
    Node(int v) : val(v), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
    Node* head;
    Node* tail;
    int _size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), _size(0) {}

    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    ~DoublyLinkedList() {
        Node* cur = head;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    int size() const { return _size; }
    bool empty() const { return _size == 0; }

    // O(1): link new node before head.
    void push_front(int val) {
        Node* n = new Node(val);
        n->next = head;
        if (head) head->prev = n;
        head = n;
        if (!tail) tail = n;
        _size++;
    }

    // O(1): link new node after tail.
    void push_back(int val) {
        Node* n = new Node(val);
        n->prev = tail;
        if (tail) tail->next = n;
        tail = n;
        if (!head) head = n;
        _size++;
    }

    // O(1): unlink head.
    void pop_front() {
        if (!head) throw out_of_range("pop_front on empty list");
        Node* old = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete old;
        _size--;
    }

    // O(1): unlink tail (this is the key advantage over a singly linked list).
    void pop_back() {
        if (!tail) throw out_of_range("pop_back on empty list");
        Node* old = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete old;
        _size--;
    }

    // O(n) to find the position, O(1) to splice in.
    void insert_at(int index, int val) {
        if (index < 0 || index > _size) throw out_of_range("insert_at index out of range");
        if (index == 0) { push_front(val); return; }
        if (index == _size) { push_back(val); return; }
        Node* cur = head;
        for (int i = 0; i < index; i++) cur = cur->next;
        // insert new node before `cur`
        Node* n = new Node(val);
        Node* p = cur->prev;
        n->prev = p;
        n->next = cur;
        p->next = n;
        cur->prev = n;
        _size++;
    }

    // O(n) to find the node, O(1) to unlink.
    void erase_at(int index) {
        if (index < 0 || index >= _size) throw out_of_range("erase_at index out of range");
        if (index == 0) { pop_front(); return; }
        if (index == _size - 1) { pop_back(); return; }
        Node* cur = head;
        for (int i = 0; i < index; i++) cur = cur->next;
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        delete cur;
        _size--;
    }

    void printForward() const {
        Node* cur = head;
        cout << "[";
        while (cur) {
            cout << cur->val;
            if (cur->next) cout << " <-> ";
            cur = cur->next;
        }
        cout << "] (size=" << _size << ")\n";
    }

    void printBackward() const {
        Node* cur = tail;
        cout << "[";
        while (cur) {
            cout << cur->val;
            if (cur->prev) cout << " <-> ";
            cur = cur->prev;
        }
        cout << "] (size=" << _size << ")\n";
    }
};

int main() {
    DoublyLinkedList list;

    cout << "-- push_back 1,2,3 --\n";
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.printForward(); // [1 <-> 2 <-> 3]

    cout << "-- push_front 0 --\n";
    list.push_front(0);
    list.printForward(); // [0 <-> 1 <-> 2 <-> 3]

    cout << "-- print backward --\n";
    list.printBackward(); // [3 <-> 2 <-> 1 <-> 0]

    cout << "-- insert_at(2, 99) --\n";
    list.insert_at(2, 99);
    list.printForward(); // [0 <-> 1 <-> 99 <-> 2 <-> 3]

    cout << "-- erase_at(2) --\n";
    list.erase_at(2);
    list.printForward(); // [0 <-> 1 <-> 2 <-> 3]

    cout << "-- pop_front --\n";
    list.pop_front();
    list.printForward(); // [1 <-> 2 <-> 3]

    cout << "-- pop_back --\n";
    list.pop_back();
    list.printForward(); // [1 <-> 2]

    cout << "size = " << list.size() << "\n";

    return 0;
}

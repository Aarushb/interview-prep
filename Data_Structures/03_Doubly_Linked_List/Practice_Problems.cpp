/*
PROBLEM: LRU Cache (LeetCode 146)
DESCRIPTION: Design a data structure that follows the constraints of a Least Recently Used (LRU)
cache. Implement get(key) and put(key, value) both in O(1) average time. When the cache reaches its
capacity, evict the least recently used entry before inserting a new one.
CONSTRAINTS: Positive capacity. get/put must run in O(1) average time.
EXAMPLE INPUT/OUTPUT: capacity=2; put(1,1); put(2,2); get(1)->1; put(3,3) evicts key 2; get(2)->-1.
*/

/*
APPROACH:
Combine a hand-rolled doubly linked list (nodes store key+value so we can evict by key from the
map too) with a hash map from key -> Node*. The DLL is kept in most-recently-used -> least-recently-
used order: head = MRU, tail = LRU. On get/put touching an existing key, unlink the node from its
current position (O(1), since we have the pointer) and re-insert it at the head. On put with a new
key, insert at head; if over capacity, evict the tail node (O(1)) and erase its key from the map.
The hash map gives O(1) key lookup so we never need to scan the list, and the DLL gives O(1)
unlink/relink given a node pointer — exactly the property a singly linked list lacks.
*/

#include <bits/stdc++.h>
using namespace std;

class LRUCache {
    struct Node {
        int key, value;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    Node* head; // most recently used
    Node* tail; // least recently used
    unordered_map<int, Node*> map;

    void unlink(Node* n) {
        if (n->prev) n->prev->next = n->next;
        if (n->next) n->next->prev = n->prev;
        if (n == head) head = n->next;
        if (n == tail) tail = n->prev;
        n->prev = n->next = nullptr;
    }

    void insertAtHead(Node* n) {
        n->next = head;
        n->prev = nullptr;
        if (head) head->prev = n;
        head = n;
        if (!tail) tail = n;
    }

public:
    LRUCache(int cap) : capacity(cap), head(nullptr), tail(nullptr) {}

    ~LRUCache() {
        Node* cur = head;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    int get(int key) {
        auto it = map.find(key);
        if (it == map.end()) return -1;
        Node* n = it->second;
        unlink(n);
        insertAtHead(n);
        return n->value;
    }

    void put(int key, int value) {
        auto it = map.find(key);
        if (it != map.end()) {
            Node* n = it->second;
            n->value = value;
            unlink(n);
            insertAtHead(n);
            return;
        }
        if ((int)map.size() == capacity) {
            // evict least recently used (tail)
            Node* lru = tail;
            unlink(lru);
            map.erase(lru->key);
            delete lru;
        }
        Node* n = new Node(key, value);
        insertAtHead(n);
        map[key] = n;
    }
};

/*
PROBLEM: Design Browser History (LeetCode 1472)
DESCRIPTION: Implement a browser history object with a homepage. Support visit(url) (which clears
all forward history), back(steps), and forward(steps), returning the current url after each move.
CONSTRAINTS: back/forward clamp to the available history bounds rather than going out of range.
EXAMPLE INPUT/OUTPUT: history("leetcode.com"); visit("google.com"); visit("facebook.com");
back(1) -> "google.com"; forward(1) -> "facebook.com".
*/

/*
APPROACH:
A doubly linked list is a natural fit: each visited page is a node, `prev` goes back in time,
`next` goes forward. We keep a `current` pointer. visit(url) creates a new node after `current`,
links it in, and discards any existing forward chain (the old `next` subtree becomes unreachable
and is freed) — this matches "visiting clears forward history". back(steps) walks `current` toward
`prev` up to `steps` times or until there is no more history. forward(steps) walks toward `next`
similarly. All operations are O(steps) with O(1) extra space beyond the list itself.
*/

class BrowserHistory {
    struct Node {
        string url;
        Node* prev;
        Node* next;
        Node(const string& u) : url(u), prev(nullptr), next(nullptr) {}
    };

    Node* current;

public:
    BrowserHistory(const string& homepage) {
        current = new Node(homepage);
    }

    ~BrowserHistory() {
        // free everything reachable from the earliest node
        Node* start = current;
        while (start->prev) start = start->prev;
        while (start) {
            Node* next = start->next;
            delete start;
            start = next;
        }
    }

    void visit(const string& url) {
        // discard any forward history after current
        Node* toDelete = current->next;
        while (toDelete) {
            Node* next = toDelete->next;
            delete toDelete;
            toDelete = next;
        }
        Node* n = new Node(url);
        n->prev = current;
        current->next = n;
        current = n;
    }

    string back(int steps) {
        while (steps-- > 0 && current->prev) current = current->prev;
        return current->url;
    }

    string forward(int steps) {
        while (steps-- > 0 && current->next) current = current->next;
        return current->url;
    }
};

int main() {
    cout << "-- LRU Cache --\n";
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << "get(1) = " << cache.get(1) << "\n";      // 1
    cache.put(3, 3);                                   // evicts key 2
    cout << "get(2) = " << cache.get(2) << "\n";      // -1
    cache.put(4, 4);                                   // evicts key 1
    cout << "get(1) = " << cache.get(1) << "\n";      // -1
    cout << "get(3) = " << cache.get(3) << "\n";      // 3
    cout << "get(4) = " << cache.get(4) << "\n\n";    // 4

    cout << "-- Design Browser History --\n";
    BrowserHistory history("leetcode.com");
    history.visit("google.com");
    history.visit("facebook.com");
    history.visit("youtube.com");
    cout << "back(1) = " << history.back(1) << "\n";       // facebook.com
    cout << "back(1) = " << history.back(1) << "\n";       // google.com
    cout << "forward(1) = " << history.forward(1) << "\n"; // facebook.com
    history.visit("linkedin.com"); // clears forward history (youtube.com is discarded)
    cout << "forward(2) = " << history.forward(2) << "\n"; // linkedin.com (no further forward)
    cout << "back(2) = " << history.back(2) << "\n";       // google.com

    return 0;
}

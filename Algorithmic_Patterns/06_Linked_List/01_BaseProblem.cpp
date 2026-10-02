/*
PROBLEM: Reverse Linked List
DESCRIPTION: Given the head of a singly linked list, reverse the list and return the new head.
CONSTRAINTS:
- The number of nodes in the list is the range [0, 5000].
- -5000 <= Node.val <= 5000
EXAMPLE INPUT/OUTPUT:
Input: 1 -> 2 -> 3 -> 4 -> 5 -> null
Output: 5 -> 4 -> 3 -> 2 -> 1 -> null
*/

#include <bits/stdc++.h>
using namespace std;

/*
APPROACH:
This is the canonical iterative reverse using three pointers: prev, curr, and next. I walk
the list once, and at each node I save curr->next before overwriting it, then point
curr->next back at prev, then shift prev and curr forward by one. Saving next first is the
key trick — without it, rewiring curr->next would lose the rest of the list. When curr
becomes null, prev is sitting on the last node visited, which is the new head. This runs in
O(n) time with O(1) extra space since I only reverse pointers in place.
*/

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* nextNode = curr->next; // store next before rewiring
            curr->next = prev;               // reverse pointer
            prev = curr;                     // advance prev
            curr = nextNode;                 // advance curr
        }
        return prev; // prev is new head
    }
};

// Helper to build and print lists for quick testing
ListNode* buildList(const vector<int>& vals) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << " -> null" << endl;
}

int main() {
    Solution sol;
    ListNode* head = buildList({1,2,3,4,5});
    cout << "Original: ";
    printList(head);
    ListNode* rev = sol.reverseList(head);
    cout << "Reversed: ";
    printList(rev);

    // Edge cases
    ListNode* single = buildList({42});
    cout << "Single: ";
    printList(sol.reverseList(single));

    ListNode* empty = nullptr;
    cout << "Empty: ";
    printList(sol.reverseList(empty));
    return 0;
}

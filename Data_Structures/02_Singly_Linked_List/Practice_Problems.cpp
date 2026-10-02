/*
PROBLEM: Middle of the Linked List (LeetCode 876)
DESCRIPTION: Given the head of a singly linked list, return the middle node. If there are two
middle nodes, return the second middle node.
CONSTRAINTS: List has at least one node.
EXAMPLE INPUT/OUTPUT: [1,2,3,4,5] -> node with val 3. [1,2,3,4,5,6] -> node with val 4.
*/

/*
APPROACH:
Floyd's slow/fast pointer technique. `slow` advances one node per step, `fast` advances two nodes
per step. When `fast` reaches the end (or its next is null), `slow` is exactly at the middle. For an
even-length list, fast will land exactly on nullptr after slow has passed the "true" midpoint,
landing slow on the second middle node as required — no need to know the length in advance, single
pass, O(1) extra space.
*/

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

/*
PROBLEM: Palindrome Linked List (LeetCode 234)
DESCRIPTION: Given the head of a singly linked list, determine if it is a palindrome.
CONSTRAINTS: Should ideally run in O(n) time and O(1) extra space.
EXAMPLE INPUT/OUTPUT: [1,2,2,1] -> true. [1,2] -> false.
*/

/*
APPROACH:
1) Find the middle using slow/fast pointers (same trick as above).
2) Reverse the second half of the list in-place (standard iterative linked-list reversal).
3) Compare the first half and the reversed second half node-by-node.
4) (Optionally) reverse the second half back to restore the original list structure.
This achieves O(n) time and O(1) extra space, avoiding an O(n) array copy.
*/

ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* cur = head;
    while (cur) {
        ListNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

bool isPalindrome(ListNode* head) {
    if (!head || !head->next) return true;

    // Find middle (slow ends at the start of the second half for even/odd handled by loop below).
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Reverse second half starting at slow.
    ListNode* secondHalfStart = reverseList(slow);

    // Compare first half with reversed second half.
    ListNode* p1 = head;
    ListNode* p2 = secondHalfStart;
    bool result = true;
    while (p2) { // second half is <= first half in length
        if (p1->val != p2->val) { result = false; break; }
        p1 = p1->next;
        p2 = p2->next;
    }

    // Restore the list (not required by LeetCode but good practice).
    reverseList(secondHalfStart);

    return result;
}

// Helpers for building/printing lists in the demo.
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
    cout << "\n";
}

int main() {
    cout << "-- Middle of the Linked List --\n";
    ListNode* l1 = buildList({1, 2, 3, 4, 5});
    cout << "list: "; printList(l1);
    cout << "middle: " << middleNode(l1)->val << "\n\n"; // 3

    ListNode* l2 = buildList({1, 2, 3, 4, 5, 6});
    cout << "list: "; printList(l2);
    cout << "middle: " << middleNode(l2)->val << "\n\n"; // 4

    cout << "-- Palindrome Linked List --\n";
    ListNode* p1 = buildList({1, 2, 2, 1});
    cout << "list: "; printList(p1);
    cout << "isPalindrome: " << (isPalindrome(p1) ? "true" : "false") << "\n"; // true
    cout << "list after check (restored): "; printList(p1);

    ListNode* p2 = buildList({1, 2});
    cout << "list: "; printList(p2);
    cout << "isPalindrome: " << (isPalindrome(p2) ? "true" : "false") << "\n"; // false

    return 0;
}

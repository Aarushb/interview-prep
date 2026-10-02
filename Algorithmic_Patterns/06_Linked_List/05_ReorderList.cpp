/*
PROBLEM: Reorder List
DESCRIPTION: Given head of a singly linked list, reorder it to L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → … in-place.
CONSTRAINTS:
- The number of nodes in the list is in the range [1, 5 * 10^4].
- 1 <= Node.val <= 1000
EXAMPLE INPUT/OUTPUT:
Input: 1 -> 2 -> 3 -> 4 -> 5 -> null
Output: 1 -> 5 -> 2 -> 4 -> 3 -> null
*/

#include <bits/stdc++.h>
using namespace std;

/*
APPROACH:
Three steps, all O(n) time and O(1) space:
1) Find middle with fast/slow (slow ends at mid).
2) Reverse second half.
3) Merge first half and reversed second half alternately.

TRICK: Disconnect first half (slow->next = nullptr) before merging.
*/

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;

        // 1) Find middle
        ListNode* slow = head; ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 2) Reverse second half
        ListNode* prev = nullptr;
        ListNode* curr = slow->next;
        while (curr) {
            ListNode* nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
        }
        slow->next = nullptr; // break list

        // 3) Merge two halves
        ListNode* first = head;
        ListNode* second = prev;
        while (second) {
            ListNode* t1 = first->next;
            ListNode* t2 = second->next;
            first->next = second;
            second->next = t1;
            first = t1;
            second = t2;
        }
    }
};

ListNode* buildList(const vector<int>& vals) {
    ListNode dummy(0); ListNode* t = &dummy;
    for (int v : vals) { t->next = new ListNode(v); t = t->next; }
    return dummy.next;
}

void printList(ListNode* head) {
    while (head) { cout << head->val; if (head->next) cout << " -> "; head = head->next; }
    cout << " -> null" << endl;
}

int main() {
    Solution sol;
    ListNode* h1 = buildList({1,2,3,4,5});
    cout << "Original: "; printList(h1);
    sol.reorderList(h1);
    cout << "Reordered: "; printList(h1);

    ListNode* h2 = buildList({1,2,3,4});
    sol.reorderList(h2);
    cout << "Even length: "; printList(h2);

    ListNode* h3 = buildList({1});
    sol.reorderList(h3);
    cout << "Single: "; printList(h3);
    return 0;
}

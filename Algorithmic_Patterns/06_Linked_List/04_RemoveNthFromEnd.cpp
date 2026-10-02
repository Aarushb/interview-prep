/*
PROBLEM: Remove Nth Node From End of List
DESCRIPTION: Given head of a linked list, remove the nth node from the end and return the head.
CONSTRAINTS:
- The number of nodes in the list is sz, where 1 <= sz <= 30.
- 0 <= Node.val <= 100
- 1 <= n <= sz
EXAMPLE INPUT/OUTPUT:
Input: head = [1,2,3,4,5], n = 2  -> Output: [1,2,3,5]
Input: head = [1], n = 1 -> Output: []
*/

#include <bits/stdc++.h>
using namespace std;

/*
APPROACH:
One-pass two-pointer with a dummy node:
1) Advance fast by n steps.
2) Move fast and slow together until fast hits null.
3) Slow is just before the node to delete; relink to skip it.

TIME: O(n)
SPACE: O(1)
*/

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        for (int i = 0; i < n && fast; i++) fast = fast->next;
        while (fast && fast->next) {
            fast = fast->next;
            slow = slow->next;
        }

        if (slow && slow->next) {
            slow->next = slow->next->next;
        }
        return dummy.next;
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
    h1 = sol.removeNthFromEnd(h1, 2);
    cout << "Remove 2nd from end: "; printList(h1);

    ListNode* h2 = buildList({1});
    h2 = sol.removeNthFromEnd(h2, 1);
    cout << "Single removed: "; printList(h2);

    ListNode* h3 = buildList({1,2});
    h3 = sol.removeNthFromEnd(h3, 1);
    cout << "Remove tail: "; printList(h3);
    return 0;
}

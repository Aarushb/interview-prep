/*
PROBLEM: Merge Two Sorted Lists
DESCRIPTION: Given heads of two sorted linked lists list1 and list2, merge them into one sorted list and return its head.
CONSTRAINTS:
- 0 <= len(list1), len(list2) <= 50
- -100 <= node.val <= 100
EXAMPLE INPUT/OUTPUT:
Input: list1 = [1,2,4], list2 = [1,3,4]
Output: [1,1,2,3,4,4]

Input: list1 = [], list2 = [] -> Output: []
Input: list1 = [], list2 = [0] -> Output: [0]
*/

/*
APPROACH:
This is a two-pointer merge, the same idea as the merge step in merge sort. I keep a dummy
head and a tail pointer, and at each step I compare the current nodes of l1 and l2, append
whichever is smaller to tail, and advance that list's pointer. Once one list runs out, the
other list is already sorted, so I just attach its remaining nodes directly to tail rather
than looping through them one at a time. Because I'm relinking existing nodes instead of
allocating new ones, this runs in O(m+n) time with O(1) extra space.
*/

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2; // append remainder
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
    ListNode* l1 = buildList({1,2,4});
    ListNode* l2 = buildList({1,3,4});
    cout << "Merged: ";
    printList(sol.mergeTwoLists(l1, l2));

    // Edge cases
    ListNode* e1 = nullptr; ListNode* e2 = nullptr;
    cout << "Both empty: "; printList(sol.mergeTwoLists(e1, e2));

    ListNode* e3 = nullptr; ListNode* e4 = buildList({0});
    cout << "Second single: "; printList(sol.mergeTwoLists(e3, e4));
    return 0;
}

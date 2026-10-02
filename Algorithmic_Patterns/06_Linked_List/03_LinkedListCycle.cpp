/*
PROBLEM: Linked List Cycle
DESCRIPTION: Given head, determine if the linked list has a cycle. A cycle exists if a node’s next pointer points to a previous node.
CONSTRAINTS:
- The number of nodes in the list is in the range [0, 10^4].
- -10^5 <= Node.val <= 10^5
EXAMPLE INPUT/OUTPUT:
Input: head = [3,2,0,-4], pos = 1  (pos indicates tail connects to node index 1)
Output: true

Input: head = [1,2], pos = 0 -> Output: true
Input: head = [1], pos = -1 -> Output: false
*/

/*
APPROACH:
Use Floyd's Tortoise and Hare (fast/slow pointers). I advance slow by one node and fast by
two nodes each step. If there's no cycle, fast (or fast->next) will hit null and I can
return false. If there is a cycle, fast keeps looping around inside it and, because it gains
one extra step on slow every iteration, it's guaranteed to eventually lap slow and land on
the same node — at which point I return true. This needs no extra memory beyond the two
pointers, so it's O(n) time and O(1) space, better than a hash-set-of-visited-nodes approach.
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
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) return true;
        }
        return false;
    }
};

ListNode* buildCyclic(const vector<int>& vals, int pos) {
    ListNode dummy(0); ListNode* tail = &dummy; ListNode* cycleNode = nullptr;
    for (int i = 0; i < (int)vals.size(); i++) {
        tail->next = new ListNode(vals[i]);
        tail = tail->next;
        if (i == pos) cycleNode = tail;
    }
    if (tail && cycleNode) tail->next = cycleNode;
    return dummy.next;
}

int main() {
    Solution sol;
    ListNode* c1 = buildCyclic({3,2,0,-4}, 1);
    cout << "Test 1: " << (sol.hasCycle(c1) ? "true" : "false") << endl; // true

    ListNode* c2 = buildCyclic({1,2}, 0);
    cout << "Test 2: " << (sol.hasCycle(c2) ? "true" : "false") << endl; // true

    ListNode* c3 = buildCyclic({1}, -1);
    cout << "Test 3: " << (sol.hasCycle(c3) ? "true" : "false") << endl; // false

    ListNode* empty = nullptr;
    cout << "Empty: " << (sol.hasCycle(empty) ? "true" : "false") << endl; // false
    return 0;
}

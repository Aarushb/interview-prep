# Linked List Pattern

## Pattern Overview
Linked list questions center on pointer manipulation: reversing, merging, detecting cycles, removing nodes without full traversal, and reordering. The key is disciplined pointer movement (prev, curr, next) and, when needed, fast/slow pointers for cycle and middle detection.

## When to Use This Pattern

- Need to reverse all or part of a list (full reverse, reverse in k-groups)
- Need to detect or locate cycles (Floyd’s tortoise and hare)
- Need to merge sorted lists in O(1) extra space
- Need to delete nth from end in one pass
- Need to reorder nodes without extra arrays
- Need a middle node quickly (fast/slow pointers)

## Complexity

- Traversal-based operations: **O(n)** time, **O(1)** space
- Merging two lists: **O(m+n)** time, **O(1)** space
- Cycle detection: **O(n)** time, **O(1)** space

## Common Templates

### Reverse a Linked List (Iterative)
```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr) {
        ListNode* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    return prev;
}
```

### Merge Two Sorted Lists
```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) { tail->next = l1; l1 = l1->next; }
        else { tail->next = l2; l2 = l2->next; }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}
```

### Fast/Slow to Find Middle (and Cycle)
```cpp
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    return slow;
}

bool hasCycle(ListNode* head) {
    ListNode *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next; fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}
```

### Remove Nth From End (One Pass)
```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0); dummy.next = head;
    ListNode *fast = &dummy, *slow = &dummy;
    for (int i = 0; i < n; i++) fast = fast->next;
    while (fast->next) { fast = fast->next; slow = slow->next; }
    slow->next = slow->next->next;
    return dummy.next;
}
```

### Reorder List (L0→Ln→L1→Ln-1…)
1) Find middle; 2) Reverse second half; 3) Merge alternating.

## Tricks and Edge Cases
- Always store `next` before rewiring pointers.
- Use a dummy node to simplify head changes.
- For cycle detection, if `fast` catches `slow`, there is a cycle; to find entry, reset one pointer to head and move both one step.
- For even vs odd lengths, fast/slow stops differ—be explicit about which middle you need.
- Watch for single-node and two-node lists.

## Interview Checklist
- State time/space trade-offs and why you avoid extra arrays.
- Draw pointer movement for clarity.
- Mention dummy nodes for cleaner edge handling.
- Verify with edge cases: empty, one node, two nodes, all same values, presence/absence of cycle.

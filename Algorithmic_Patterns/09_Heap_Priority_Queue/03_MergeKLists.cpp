/*
PROBLEM: Merge k Sorted Lists
DESCRIPTION: You are given an array of k linked-lists lists, each linked-list is sorted in
ascending order. Merge all the linked-lists into one sorted linked list and return it.
CONSTRAINTS: k == lists.length; 0 <= k <= 10^4; 0 <= lists[i].length <= 500;
-10^4 <= lists[i][j] <= 10^4; lists[i] is sorted in ascending order; the sum of lists[i].length
will not exceed 10^4.
EXAMPLE INPUT/OUTPUT: lists = [[1,4,5],[1,3,4],[2,6]] -> [1,1,2,3,4,4,5,6].
*/

/*
APPROACH:
Push the head node of each of the k lists into a min-heap ordered by node value. Repeatedly pop the
smallest node, append it to the result list, and if that node has a next pointer, push it back into
the heap. This is the classic k-way merge: instead of comparing all k current heads linearly at
every step (O(k) per node), the heap gives us the minimum in O(log k), for O(N log k) total where
N is the total number of nodes across all lists.
*/

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val; ListNode* next;
    ListNode(int v): val(v), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode* a, ListNode* b){ return a->val > b->val; };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
        for(auto* node: lists) if(node) pq.push(node);
        ListNode dummy(0), *tail=&dummy;
        while(!pq.empty()){
            auto* node = pq.top(); pq.pop();
            tail->next = node; tail = tail->next;
            if(node->next) pq.push(node->next);
        }
        return dummy.next;
    }
};

static ListNode* build(const vector<int>& v){
    ListNode dummy(0); auto* cur=&dummy;
    for(int x: v){ cur->next = new ListNode(x); cur = cur->next; }
    return dummy.next;
}

static void print(ListNode* n){
    while(n){ cout<<n->val; if(n->next) cout<<" "; n=n->next; }
    cout<<"\n";
}

int main(){
    vector<ListNode*> lists;
    lists.push_back(build({1,4,5}));
    lists.push_back(build({1,3,4}));
    lists.push_back(build({2,6}));
    Solution sol;
    auto* merged = sol.mergeKLists(lists);
    print(merged); // expect 1 1 2 3 4 4 5 6
    return 0;
}

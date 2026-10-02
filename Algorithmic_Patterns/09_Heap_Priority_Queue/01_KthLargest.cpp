/*
PROBLEM: Kth Largest Element in a Stream
DESCRIPTION: Design a class KthLargest that maintains the kth largest element in a stream of
integers. The constructor takes an integer k and an initial array of integers nums. The add(val)
method appends val to the stream and returns the element representing the kth largest element in
the stream after insertion.
CONSTRAINTS: 1 <= k <= 10^4; 0 <= nums.length <= 10^4; -10^4 <= nums[i] <= 10^4; -10^4 <= val <= 10^4;
at most 10^4 calls to add; it is guaranteed there will be at least k elements in the array when
you search for the kth element.
EXAMPLE INPUT/OUTPUT: KthLargest(3, [4,5,8,2]); add(3) -> 4; add(5) -> 5; add(10) -> 5; add(9) -> 8;
add(4) -> 8.
*/

/*
APPROACH:
Maintain a min-heap capped at size k containing the k largest values seen so far. Every time a value
arrives (from the constructor or from add), push it onto the heap, and if the heap grows past size k,
pop the smallest element off — this guarantees the heap always holds exactly the k largest elements
seen so far. The kth largest element is then simply the root of the min-heap (the smallest of the
top-k, i.e. the kth largest overall), giving O(log k) per operation instead of re-sorting on every call.
*/

#include <bits/stdc++.h>
using namespace std;

class KthLargest {
public:
    KthLargest(int k, vector<int>& nums): k(k) {
        for(int x: nums){
            pq.push(x);
            if((int)pq.size()>k) pq.pop();
        }
    }
    int add(int val){
        pq.push(val);
        if((int)pq.size()>k) pq.pop();
        return pq.top();
    }
private:
    int k;
    priority_queue<int, vector<int>, greater<int>> pq;
};

int main(){
    vector<int> nums = {4,5,8,2};
    KthLargest kth(3, nums);
    cout << kth.add(3) << "\n";  // 4
    cout << kth.add(5) << "\n";  // 5
    cout << kth.add(10) << "\n"; // 5
    cout << kth.add(9) << "\n";  // 8
    cout << kth.add(4) << "\n";  // 8
    return 0;
}

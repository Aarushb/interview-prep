/*
PROBLEM: Top K Frequent Elements
DESCRIPTION: Given an integer array nums and an integer k, return the k most frequent elements.
The answer may be returned in any order.
CONSTRAINTS: 1 <= nums.length <= 10^5; -10^4 <= nums[i] <= 10^4; k is guaranteed to be in the
range [1, number of distinct elements in nums]; the answer is guaranteed to be unique.
EXAMPLE INPUT/OUTPUT: nums = [1,1,1,2,2,3], k = 2 -> [1,2]; nums = [4,1,-1,2,-1,2,3], k = 2 -> [-1,2].
*/

/*
APPROACH:
First count how often each value occurs using a hash map. Then, instead of sorting all distinct
values by frequency (O(n log n)), push each (frequency, value) pair into a min-heap ordered by
frequency and cap the heap at size k, popping the smallest whenever it overflows — this is the
same bounded top-k heap trick as Kth Largest, giving O(n log k) overall. Whatever remains in the
heap at the end are the k most frequent elements.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> freq;
        for(int x: nums) freq[x]++;
        using P = pair<int,int>; // freq, value
        priority_queue<P, vector<P>, greater<P>> pq;
        for(auto& [val, f]: freq){
            pq.push({f, val});
            if((int)pq.size()>k) pq.pop();
        }
        vector<int> res;
        while(!pq.empty()){ res.push_back(pq.top().second); pq.pop(); }
        return res;
    }
};

int main(){
    Solution sol;
    vector<int> nums = {1,1,1,2,2,3};
    auto r1 = sol.topKFrequent(nums, 2);
    sort(r1.begin(), r1.end());
    for(int x: r1) cout << x << " "; // expect 1 2
    cout << "\n";
    vector<int> nums2 = {4,1,-1,2,-1,2,3};
    auto r2 = sol.topKFrequent(nums2, 2);
    sort(r2.begin(), r2.end());
    for(int x: r2) cout << x << " "; // expect -1 2
    cout << "\n";
    return 0;
}

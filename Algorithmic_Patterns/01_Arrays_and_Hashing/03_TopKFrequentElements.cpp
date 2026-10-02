/*
PROBLEM: Top K Frequent Elements
DESCRIPTION: Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.
CONSTRAINTS:
- 1 <= nums.length <= 10^5
- -10^4 <= nums[i] <= 10^4
- k is in the range [1, the number of unique elements in the array]
- It is guaranteed that the answer is unique.
EXAMPLE INPUT/OUTPUT:
Input: nums = [1,1,1,2,2,3], k = 2
Output: [1,2]

Input: nums = [1], k = 1
Output: [1]
*/

/*
APPROACH:
First I count how often each number appears using a hash map, since frequency is what determines
the answer, not the values themselves. Instead of sorting all frequencies (O(n log n)), I use
bucket sort: create n+1 buckets indexed by frequency and drop each number into the bucket matching
its count. Walking the buckets from highest frequency down and collecting numbers until I have k
gives the answer in O(n) time, exploiting the fact that frequency is bounded by array length.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

This problem combines frequency counting with finding top K elements.

STEP 1: Count Frequencies
- Use unordered_map to count how many times each number appears
- Time: O(n)

STEP 2: Find Top K
We have multiple approaches:

APPROACH 1: Sorting (Simple but not optimal)
- Put all (frequency, number) pairs in vector
- Sort by frequency descending
- Take first k elements
- Time: O(n log n), Space: O(n)

APPROACH 2: Min Heap (Optimal for small k)
- Use min heap of size k
- Keep only k largest frequencies
- Time: O(n log k), Space: O(n + k)

APPROACH 3: Bucket Sort (Most Optimal - O(n))
- Maximum frequency can be n (all elements same)
- Create n+1 buckets, bucket[i] contains all numbers with frequency i
- Traverse buckets from right to left (high to low frequency)
- Collect first k elements
- Time: O(n), Space: O(n)

TRICK (Bucket Sort):
Instead of sorting, we use the constraint that frequency ≤ n.
Create array of vectors where index = frequency.
bucket[3] = all numbers that appear exactly 3 times
Then traverse from bucket[n] down to bucket[1] collecting elements.
*/

class Solution {
public:
    // Approach 1: Using Sorting
    vector<int> topKFrequentSort(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        
        // Count frequencies
        for (int num : nums) {
            freq[num]++;
        }
        
        // Create pairs of (frequency, number)
        vector<pair<int, int>> freqPairs;
        for (auto& [num, count] : freq) {
            freqPairs.push_back({count, num});
        }
        
        // Sort by frequency descending
        sort(freqPairs.begin(), freqPairs.end(), greater<pair<int,int>>());
        
        // Take top k
        vector<int> result;
        for (int i = 0; i < k; i++) {
            result.push_back(freqPairs[i].second);
        }
        
        return result;
    }
    
    // Approach 2: Using Min Heap
    vector<int> topKFrequentHeap(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        
        for (int num : nums) {
            freq[num]++;
        }
        
        // Min heap: (frequency, number)
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;
        
        for (auto& [num, count] : freq) {
            minHeap.push({count, num});
            
            // Keep only k elements
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        
        // Extract from heap
        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        
        return result;
    }
    
    // Approach 3: Bucket Sort - MOST OPTIMAL O(n)
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        
        // Count frequencies
        for (int num : nums) {
            freq[num]++;
        }
        
        // Create buckets: bucket[i] = numbers with frequency i
        // Max frequency can be nums.size()
        vector<vector<int>> buckets(nums.size() + 1);
        
        for (auto& [num, count] : freq) {
            buckets[count].push_back(num);
        }
        
        // Collect from highest frequency to lowest
        vector<int> result;
        for (int i = buckets.size() - 1; i >= 0 && result.size() < k; i--) {
            for (int num : buckets[i]) {
                result.push_back(num);
                if (result.size() == k) {
                    return result;
                }
            }
        }
        
        return result;
    }
};

void printVector(vector<int>& v) {
    cout << "[";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i < v.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> nums1 = {1, 1, 1, 2, 2, 3};
    int k1 = 2;
    vector<int> result1 = sol.topKFrequent(nums1, k1);
    cout << "Test 1 (Bucket Sort): ";
    printVector(result1);
    // Expected: [1,2]
    
    // Test Case 2
    vector<int> nums2 = {1};
    int k2 = 1;
    vector<int> result2 = sol.topKFrequent(nums2, k2);
    cout << "Test 2: ";
    printVector(result2);
    // Expected: [1]
    
    // Test Case 3
    vector<int> nums3 = {4, 4, 4, 5, 5, 6};
    int k3 = 2;
    vector<int> result3 = sol.topKFrequent(nums3, k3);
    cout << "Test 3: ";
    printVector(result3);
    // Expected: [4,5]
    
    // Test Case 4 - Using Heap approach
    cout << "\n=== Using Min Heap ===" << endl;
    vector<int> nums4 = {1, 1, 1, 2, 2, 3};
    int k4 = 2;
    vector<int> result4 = sol.topKFrequentHeap(nums4, k4);
    cout << "Test 4 (Heap): ";
    printVector(result4);
    
    // Test Case 5 - Using Sort approach
    cout << "\n=== Using Sort ===" << endl;
    vector<int> nums5 = {1, 1, 1, 2, 2, 3};
    int k5 = 2;
    vector<int> result5 = sol.topKFrequentSort(nums5, k5);
    cout << "Test 5 (Sort): ";
    printVector(result5);
    
    return 0;
}

# Arrays and Hashing

## Pattern Overview
Arrays and Hashing is the foundation of most interview problems. This pattern involves using hash tables (unordered_map, unordered_set) to achieve O(1) lookups and arrays for sequential data storage.

## When to Use This Pattern

### Problem Statement Signals:
- "Find duplicates"
- "Check if array contains..."
- "Count frequency of elements"
- "Find pairs/triplets with sum X"
- "Group anagrams"
- "Find missing/extra elements"
- "Check if one array is subset of another"
- "Find first unique/non-repeating element"
- Any problem requiring **fast lookups** or **frequency counting**

### Key Indicators:
1. Need to track seen elements → use `unordered_set`
2. Need to count occurrences → use `unordered_map<element, count>`
3. Need to map elements to indices → use `unordered_map<element, index>`
4. Need to group related items → use `unordered_map<key, vector<items>>`

## Complexity Analysis

### Time Complexity:
- Hash table insert/lookup/delete: **O(1)** average case
- Iterating through array: **O(n)**
- Most problems: **O(n)** or **O(n log n)** if sorting involved

### Space Complexity:
- Hash table storage: **O(n)** in worst case
- Can be optimized to **O(k)** where k is unique elements

## Generic Template

```cpp
#include <bits/stdc++.h>
using namespace std;

// TEMPLATE 1: Frequency Counter Pattern
vector<int> frequencyPattern(vector<int>& arr) {
    unordered_map<int, int> freq;
    
    // Count frequencies
    for (int num : arr) {
        freq[num]++;
    }
    
    // Process based on frequency
    vector<int> result;
    for (auto& [num, count] : freq) {
        if (count > 1) {  // Modify condition as needed
            result.push_back(num);
        }
    }
    
    return result;
}

// TEMPLATE 2: Two Sum Pattern (Element to Index Mapping)
vector<int> twoSumPattern(vector<int>& arr, int target) {
    unordered_map<int, int> seen;
    
    for (int i = 0; i < arr.size(); i++) {
        int complement = target - arr[i];
        
        if (seen.count(complement)) {
            return {seen[complement], i};
        }
        
        seen[arr[i]] = i;
    }
    
    return {};
}

// TEMPLATE 3: Grouping Pattern
unordered_map<string, vector<string>> groupingPattern(vector<string>& items) {
    unordered_map<string, vector<string>> groups;
    
    for (string& item : items) {
        // Generate key (could be sorted string, hash, etc.)
        string key = item;
        sort(key.begin(), key.end());
        
        groups[key].push_back(item);
    }
    
    return groups;
}

// TEMPLATE 4: Sliding Window with Hash Set
int slidingWindowPattern(vector<int>& arr) {
    unordered_set<int> window;
    int left = 0, result = 0;
    
    for (int right = 0; right < arr.size(); right++) {
        // Shrink window if duplicate found
        while (window.count(arr[right])) {
            window.erase(arr[left]);
            left++;
        }
        
        window.insert(arr[right]);
        result = max(result, right - left + 1);
    }
    
    return result;
}
```

## Common Tricks and Optimizations

1. **Use unordered_map instead of map** when order doesn't matter (O(1) vs O(log n))
2. **Check before insert**: `if (map.count(key))` to avoid creating default entries
3. **Iterate with structured bindings**: `for (auto& [key, value] : map)`
4. **Use emplace instead of insert** for better performance
5. **Reserve space**: `map.reserve(n)` if size is known
6. **Custom hash functions** for pairs/tuples:
```cpp
struct PairHash {
    size_t operator()(const pair<int,int>& p) const {
        return hash<int>()(p.first) ^ hash<int>()(p.second);
    }
};
unordered_set<pair<int,int>, PairHash> pairSet;
```

## Step-by-Step Problem Solving Approach

1. **Identify what needs to be tracked**: Frequencies? Indices? Groups?
2. **Choose data structure**: 
   - Set for presence check
   - Map for counting/mapping
3. **Single pass or multiple passes?**: Often can be solved in one iteration
4. **Handle edge cases**: Empty array, single element, all duplicates
5. **Optimize space**: Do we need to store all elements or just specific ones?

## Interview Tips

- Always mention trade-off: "I'm using extra O(n) space for O(1) lookups"
- Start with brute force O(n²), then optimize with hashing
- Ask: "Can I assume all elements fit in memory?"
- Clarify: "Are there negative numbers? Can values be very large?"

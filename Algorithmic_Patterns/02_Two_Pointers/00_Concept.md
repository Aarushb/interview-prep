# Two Pointers

## Pattern Overview
Two Pointers is a technique where we use two pointers (indices) to traverse a data structure, typically an array or linked list. The pointers can move toward each other, away from each other, or in the same direction at different speeds.

## When to Use This Pattern

### Problem Statement Signals:
- "Pair with target sum"
- "Remove duplicates in-place"
- "Reverse array/string"
- "Find triplets/quadruplets"
- "Container with most water"
- "Trapping rain water"
- "Palindrome verification"
- "Merge sorted arrays"
- **Requires O(1) extra space** (in-place modification)
- **Sorted array** or **need to process from both ends**

### Key Indicators:
1. **Sorted array** → Use two pointers from opposite ends
2. **Partition problem** → One pointer for read, one for write
3. **Sliding window variant** → Both pointers move in same direction
4. **Palindrome check** → Pointers from both ends moving inward
5. **In-place operation** → Can't use extra space

## Complexity Analysis

### Time Complexity:
- Single pass with two pointers: **O(n)**
- With outer loop (3Sum/4Sum): **O(n²)** or **O(n³)**

### Space Complexity:
- Typically **O(1)** - this is the main advantage
- May be **O(k)** for storing result

## Generic Templates

```cpp
#include <bits/stdc++.h>
using namespace std;

// TEMPLATE 1: Opposite Direction Pointers
// Use for: Sorted array pair finding, palindrome check, reverse
int oppositeDirectionPattern(vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left < right) {
        int sum = arr[left] + arr[right];
        
        if (sum == target) {
            return left;  // Or whatever result needed
        } else if (sum < target) {
            left++;   // Need larger sum
        } else {
            right--;  // Need smaller sum
        }
    }
    
    return -1;
}

// TEMPLATE 2: Same Direction Pointers (Fast-Slow)
// Use for: Remove duplicates, partition, in-place modification
int sameDirectionPattern(vector<int>& arr) {
    int slow = 0;  // Position to write next valid element
    
    for (int fast = 0; fast < arr.size(); fast++) {
        if (/* element at fast is valid */) {
            arr[slow] = arr[fast];
            slow++;
        }
    }
    
    return slow;  // New length
}

// TEMPLATE 3: Sliding Window with Two Pointers
// Use for: Longest/shortest subarray problems
int slidingWindowPattern(vector<int>& arr) {
    int left = 0, right = 0;
    int result = 0;
    
    while (right < arr.size()) {
        // Expand window
        // Add arr[right] to current window
        
        while (/* window invalid */) {
            // Shrink window
            // Remove arr[left] from window
            left++;
        }
        
        result = max(result, right - left + 1);
        right++;
    }
    
    return result;
}

// TEMPLATE 4: Three Pointers (for 3Sum variants)
vector<vector<int>> threeSumPattern(vector<int>& arr) {
    sort(arr.begin(), arr.end());  // Must sort first
    vector<vector<int>> result;
    
    for (int i = 0; i < arr.size() - 2; i++) {
        // Skip duplicates for first element
        if (i > 0 && arr[i] == arr[i-1]) continue;
        
        int left = i + 1;
        int right = arr.size() - 1;
        
        while (left < right) {
            int sum = arr[i] + arr[left] + arr[right];
            
            if (sum == 0) {
                result.push_back({arr[i], arr[left], arr[right]});
                
                // Skip duplicates
                while (left < right && arr[left] == arr[left+1]) left++;
                while (left < right && arr[right] == arr[right-1]) right--;
                
                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    return result;
}
```

## Common Patterns and Tricks

### 1. **Opposite Direction (Converging)**
```cpp
left = 0, right = n-1
while (left < right) {
    // Process
    if (condition) left++
    else right--
}
```
**Use for**: Pair sum in sorted array, palindrome check, reverse

### 2. **Same Direction (Slow-Fast)**
```cpp
slow = 0
for (fast = 0; fast < n; fast++) {
    if (valid(arr[fast])) {
        arr[slow++] = arr[fast]
    }
}
```
**Use for**: Remove duplicates, partition, in-place filtering

### 3. **Cycle Detection (Floyd's Tortoise and Hare)**
```cpp
slow = head, fast = head
while (fast && fast->next) {
    slow = slow->next
    fast = fast->next->next
    if (slow == fast) return true  // Cycle found
}
```
**Use for**: Linked list cycle, finding middle

### 4. **Partition (Quicksort style)**
```cpp
int i = -1;  // Boundary
for (int j = 0; j < n; j++) {
    if (arr[j] < pivot) {
        i++;
        swap(arr[i], arr[j]);
    }
}
```
**Use for**: Partition around pivot, Dutch National Flag

## Step-by-Step Problem Solving

1. **Identify if sorted**: If not, check if sorting helps
2. **Determine pointer direction**: 
   - Opposite for pair finding
   - Same for in-place modification
3. **Define movement condition**: When to move left? Right? Both?
4. **Handle duplicates**: Skip them to avoid redundant work
5. **Edge cases**: Empty, single element, all same elements

## Common Mistakes to Avoid

1. **Forgetting to sort** when using opposite direction pointers
2. **Off-by-one errors**: `left < right` vs `left <= right`
3. **Not skipping duplicates** in 3Sum/4Sum type problems
4. **Modifying array** while iterating (use separate write pointer)
5. **Infinite loops**: Ensure pointers always move

## Interview Tips

- Start with brute force, then optimize with two pointers
- Mention space optimization: "This uses O(1) space vs O(n) with hash map"
- For sorted arrays, always consider two pointers first
- Draw diagram showing pointer movement
- Test edge cases: empty, one element, all duplicates

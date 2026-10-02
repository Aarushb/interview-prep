# Binary Search

## Pattern Overview
Binary Search is a divide-and-conquer algorithm that efficiently searches sorted arrays or finds answers in monotonic search spaces. It repeatedly divides the search space in half until the target is found or the space is exhausted.

## When to Use This Pattern

### Problem Statement Signals:
- "Find element in **sorted** array"
- "First/last occurrence of element"
- "Search in rotated sorted array"
- "Find minimum/maximum in sorted structure"
- "Search in 2D matrix"
- "Find peak element"
- "Search answer in range [low, high]"
- "Minimize maximum" or "Maximize minimum"
- Problem has **monotonic** property

### Key Indicators:
1. **Sorted data structure**: Array, matrix, search space
2. **Decision problem**: Can answer "is X valid?" for any X
3. **Monotonic function**: If f(x) is true, then f(x+1) is also true (or vice versa)
4. **Optimization**: Find minimum/maximum value satisfying condition
5. **Time constraint**: O(n) too slow, need O(log n)

## Complexity Analysis

### Time Complexity:
- Binary Search: **O(log n)**
- Binary Search on Answer: **O(log(max-min) × O(check))**
- 2D Matrix: **O(log(m×n))** or **O(m + log n)**

### Space Complexity:
- Iterative: **O(1)**
- Recursive: **O(log n)** for call stack

## Generic Templates

```cpp
#include <bits/stdc++.h>
using namespace std;

// TEMPLATE 1: Classic Binary Search (Find Exact Match)
int binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;  // Found
        } else if (arr[mid] < target) {
            left = mid + 1;  // Search right half
        } else {
            right = mid - 1;  // Search left half
        }
    }
    
    return -1;  // Not found
}

// TEMPLATE 2: Find First Occurrence (Left Boundary)
int findFirst(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;  // Continue searching left
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// TEMPLATE 3: Find Last Occurrence (Right Boundary)
int findLast(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1;  // Continue searching right
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// TEMPLATE 4: Binary Search on Answer Space
// Use for: "Minimize maximum" or "Maximize minimum" problems
bool isValid(int mid, /* problem parameters */) {
    // Check if 'mid' is a valid answer
    return true/false;
}

int binarySearchAnswer(int low, int high) {
    int result = high;  // Or low, depending on problem
    
    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (isValid(mid)) {
            result = mid;
            high = mid - 1;  // Try to minimize (or low = mid+1 to maximize)
        } else {
            low = mid + 1;  // (or high = mid-1)
        }
    }
    
    return result;
}

// TEMPLATE 5: Search Insert Position
int searchInsert(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return left;  // Insertion position
}
```

## Common Patterns & Variations

### 1. Classic Binary Search
- Find element in sorted array
- **Condition**: arr[mid] == target

### 2. Find Boundaries
- First/last occurrence
- **Trick**: Don't return immediately when found, continue searching

### 3. Rotated Sorted Array
- One half is always sorted
- **Strategy**: Determine which half is sorted, then search accordingly

### 4. Binary Search on Answer
- Search space is answer range, not array
- **Use for**: Minimize maximum, maximize minimum
- **Examples**: Capacity to ship packages, split array largest sum

### 5. Peak Element
- Find local maximum
- **Strategy**: Move toward higher side

### 6. 2D Matrix Search
- Sorted rows and columns
- **Strategy**: Start from corner or use binary search

## Key Tricks & Tips

### 1. Avoid Integer Overflow
```cpp
// WRONG
int mid = (left + right) / 2;  // May overflow if left+right > INT_MAX

// CORRECT
int mid = left + (right - left) / 2;
```

### 2. Loop Condition: <= vs <
```cpp
// Use left <= right for most cases (searching for element)
while (left <= right) { ... }

// Use left < right for certain boundary problems
while (left < right) { 
    int mid = left + (right - left) / 2;
    if (condition) right = mid;  // Not mid-1
    else left = mid + 1;
}
```

### 3. Boundary Updates
```cpp
// When found but want first occurrence
if (arr[mid] == target) {
    result = mid;
    right = mid - 1;  // Keep searching left
}

// When found but want last occurrence
if (arr[mid] == target) {
    result = mid;
    left = mid + 1;  // Keep searching right
}
```

### 4. Return Value
```cpp
// Not found: return left (insert position)
return left;

// Not found: return -1
return -1;

// Boundary search: return result variable
return result;
```

## Common Mistakes to Avoid

1. **Integer overflow in mid calculation**: Use `left + (right-left)/2`
2. **Infinite loop**: Check loop condition and boundary updates
3. **Off-by-one errors**: Be careful with `<=` vs `<`, `mid+1` vs `mid`
4. **Not considering edge cases**: Empty array, single element, all same
5. **Wrong initialization**: result = -1 vs result = low/high

## Binary Search on Answer - When to Use

### Pattern Recognition:
- Problem asks to **minimize maximum** or **maximize minimum**
- Answer lies in range [low, high]
- Can verify if answer X is valid in O(f(n))
- Monotonic property: if X works, all values >= X work (or vice versa)

### Examples:
- Split Array Largest Sum: Minimize largest sum
- Koko Eating Bananas: Minimize eating speed
- Capacity To Ship Packages: Minimize ship capacity
- Magnetic Force Between Balls: Maximize minimum distance

## Pattern Recognition Checklist

Use Binary Search when:
- ✅ Sorted array or search space
- ✅ Need O(log n) time
- ✅ Find first/last occurrence
- ✅ Minimize maximum or maximize minimum
- ✅ Monotonic property exists
- ❌ Unsorted array (must sort first or use different approach)
- ❌ Need to find all occurrences (may need linear scan)

## Example Problems by Difficulty

### Easy:
- Binary Search ⭐
- Search Insert Position
- First Bad Version
- Sqrt(x)

### Medium:
- Find First and Last Position of Element ⭐
- Search in Rotated Sorted Array ⭐
- Find Peak Element
- Time Based Key-Value Store
- Koko Eating Bananas
- Minimum Number of Days to Make m Bouquets

### Hard:
- Median of Two Sorted Arrays ⭐⭐
- Split Array Largest Sum
- Capacity To Ship Packages Within D Days
- Aggressive Cows (Binary Search on Answer)

## Interview Tips

1. **Clarify if sorted**: Always ask if array is sorted
2. **Ask about duplicates**: Affects boundary search
3. **Confirm what to return**: Index, value, -1, insert position?
4. **Consider edge cases**: Empty, single element, not found
5. **Explain why binary search works**: Monotonic property, sorted data
6. **Draw search space**: Helps visualize boundary updates

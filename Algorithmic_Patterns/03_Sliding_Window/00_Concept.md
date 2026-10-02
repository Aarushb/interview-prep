# Sliding Window

## Pattern Overview
Sliding Window is a technique for solving problems involving subarrays or substrings. It uses two pointers to create a "window" that slides through the data structure, expanding and contracting to find optimal solutions.

## When to Use This Pattern

### Problem Statement Signals:
- "Longest substring with..."
- "Maximum/minimum subarray of size K"
- "Find all subarrays that..."
- "Smallest substring containing..."
- "Permutation/anagram in string"
- "Maximum sum subarray of size K"
- Problems involving **contiguous** sequences
- Need to find **optimal** contiguous subarray/substring

### Key Indicators:
1. **Contiguous sequence** required (subarray/substring, not subsequence)
2. Ask for **longest/shortest/maximum/minimum**
3. Have **constraints** on window (size, sum, character frequency)
4. **Linear time** solution possible
5. Brute force would require O(n²) or O(n³)

## Complexity Analysis

### Time Complexity:
- Fixed window size: **O(n)**
- Variable window size: **O(n)** (each element visited at most twice)

### Space Complexity:
- Usually **O(1)** or **O(k)** where k is alphabet size
- May need hash map for character/element counting

## Generic Templates

```cpp
#include <bits/stdc++.h>
using namespace std;

// TEMPLATE 1: Fixed Size Window
// Use for: "Subarray of size K with maximum sum"
int fixedSizeWindow(vector<int>& arr, int k) {
    int windowSum = 0;
    int maxSum = INT_MIN;
    
    // Build first window
    for (int i = 0; i < k; i++) {
        windowSum += arr[i];
    }
    maxSum = windowSum;
    
    // Slide the window
    for (int i = k; i < arr.size(); i++) {
        windowSum += arr[i] - arr[i - k];  // Add new, remove old
        maxSum = max(maxSum, windowSum);
    }
    
    return maxSum;
}

// TEMPLATE 2: Variable Size Window (Maximum)
// Use for: "Longest substring with at most K distinct characters"
int variableSizeWindowMax(string s, int k) {
    unordered_map<char, int> freq;
    int left = 0;
    int maxLength = 0;
    
    for (int right = 0; right < s.length(); right++) {
        // Expand window
        freq[s[right]]++;
        
        // Shrink window if constraint violated
        while (freq.size() > k) {
            freq[s[left]]--;
            if (freq[s[left]] == 0) {
                freq.erase(s[left]);
            }
            left++;
        }
        
        // Update result
        maxLength = max(maxLength, right - left + 1);
    }
    
    return maxLength;
}

// TEMPLATE 3: Variable Size Window (Minimum)
// Use for: "Smallest substring containing all characters"
int variableSizeWindowMin(string s, string t) {
    unordered_map<char, int> required, window;
    for (char c : t) required[c]++;
    
    int left = 0, matched = 0;
    int minLength = INT_MAX;
    
    for (int right = 0; right < s.length(); right++) {
        // Expand window
        char c = s[right];
        if (required.count(c)) {
            window[c]++;
            if (window[c] == required[c]) {
                matched++;
            }
        }
        
        // Shrink window while valid
        while (matched == required.size()) {
            minLength = min(minLength, right - left + 1);
            
            char leftChar = s[left];
            if (required.count(leftChar)) {
                if (window[leftChar] == required[leftChar]) {
                    matched--;
                }
                window[leftChar]--;
            }
            left++;
        }
    }
    
    return minLength == INT_MAX ? 0 : minLength;
}
```

## Common Patterns & Variations

### 1. Fixed Size Window
- **Pattern**: Window size is given (K)
- **Strategy**: Build first window, then slide by adding right element and removing leftmost
- **Problems**: Maximum sum subarray of size K, average of subarrays

### 2. Variable Size - Find Maximum
- **Pattern**: Find longest/maximum window satisfying constraint
- **Strategy**: Expand right, shrink left when constraint violated, track maximum
- **Problems**: Longest substring with K distinct chars, max consecutive ones

### 3. Variable Size - Find Minimum
- **Pattern**: Find shortest/minimum window satisfying constraint
- **Strategy**: Expand right until valid, then shrink left while maintaining validity
- **Problems**: Minimum window substring, smallest subarray with sum >= K

### 4. Two Counters Pattern
- **Pattern**: Track frequency of elements in window
- **Strategy**: Use hash map to maintain element counts
- **Problems**: Permutation in string, find all anagrams

## Key Tricks & Tips

### 1. Window Validity Check
```cpp
// For character-based problems
bool isValid = (uniqueChars <= K);
bool isValid = (window == required);  // For anagram/permutation

// For sum-based problems
bool isValid = (windowSum >= target);
bool isValid = (windowSum == K);
```

### 2. Shrinking the Window
```cpp
// Shrink until constraint is satisfied
while (constraint_violated) {
    // Remove left element from window
    // Move left pointer right
    left++;
}

// Shrink while constraint is satisfied (for minimum problems)
while (constraint_satisfied) {
    // Update minimum result
    // Remove left element and move left++
}
```

### 3. Updating Result
```cpp
// For maximum problems: Update after shrinking
maxLength = max(maxLength, right - left + 1);

// For minimum problems: Update during shrinking
minLength = min(minLength, right - left + 1);
```

### 4. Hash Map for Character Frequency
```cpp
unordered_map<char, int> freq;

// Add to window
freq[s[right]]++;

// Remove from window
freq[s[left]]--;
if (freq[s[left]] == 0) {
    freq.erase(s[left]);  // Keep map clean
}

// Check if valid
bool valid = (freq.size() <= K);
```

## Common Mistakes to Avoid

1. **Forgetting to remove left element** when shrinking window
2. **Not initializing the first window** properly for fixed-size problems
3. **Wrong position for updating result** (before vs after shrinking)
4. **Off-by-one errors** in window size calculation: Use `right - left + 1`
5. **Not handling edge cases**: empty strings, K > array size
6. **Using nested loops** when single pass is sufficient

## Time Complexity Analysis

Despite nested loops, sliding window is **O(n)**:
- Each element is visited by `right` pointer exactly once
- Each element is visited by `left` pointer at most once
- Total operations: 2n = O(n)

## Pattern Recognition Checklist

Use Sliding Window when you see:
- ✅ Contiguous subarray/substring
- ✅ Optimization problem (min/max/longest/shortest)
- ✅ Constraint on window (size, sum, character count)
- ✅ Array/string iteration
- ❌ Subsequence (non-contiguous) → Use DP instead
- ❌ Need all permutations → Use backtracking
- ❌ Multiple separate subarrays → Different technique

## Example Problems by Difficulty

### Easy:
- Maximum sum subarray of size K
- Contains Duplicate II
- Average of subarrays of size K

### Medium:
- Longest substring without repeating characters ⭐
- Longest repeating character replacement
- Permutation in string
- Maximum average subarray
- Fruit into baskets

### Hard:
- Minimum window substring ⭐⭐
- Sliding window maximum (with deque)
- Longest substring with at most K distinct characters
- Subarrays with K different integers

## Related Patterns

1. **Two Pointers**: Sliding window is a special case of two pointers
2. **Monotonic Queue/Deque**: For tracking min/max in window
3. **Hash Map**: Often used with sliding window for counting
4. **Prefix Sum**: Alternative for some sum-based problems

## Interview Tips

1. **Clarify constraints**: Window size fixed or variable?
2. **Ask about characters**: Lowercase only? ASCII? Unicode?
3. **Edge cases**: Empty input, K > length, all same elements
4. **Start with brute force**: Show you understand the problem
5. **Optimize to sliding window**: Explain why it works (avoid redundant work)
6. **Explain the invariant**: What property does your window maintain?

/*
PROBLEM: Longest Substring Without Repeating Characters
DESCRIPTION: Given a string s, find the length of the longest substring without repeating characters.
CONSTRAINTS:
- 0 <= s.length <= 5 * 10^4
- s consists of English letters, digits, symbols and spaces.
EXAMPLE INPUT/OUTPUT:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Input: s = "bbbbb"
Output: 1

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
*/

/*
APPROACH:
This screams sliding window because we need a contiguous run of the string satisfying a constraint
(no repeats), and we want the longest one. I keep a left and right pointer and a hash structure tracking
what's currently in the window. I expand right one character at a time; if the new character already
exists in the window, I shrink from the left until the duplicate is gone. At every step I record the
window size if it's a new max. The key optimization is using a map of last-seen index per character so
when I hit a duplicate I can jump left directly instead of removing one character at a time, keeping it
O(n) overall.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

Classic VARIABLE SIZE SLIDING WINDOW with hash set/map.

BRUTE FORCE:
- Check all substrings for uniqueness
- Time: O(n³) or O(n²) with set

OPTIMAL (Sliding Window):
- Use two pointers and a set/map to track characters in current window
- Expand right: Add character to window
- If duplicate found: Shrink left until duplicate removed
- Track maximum window size
- Time: O(n), Space: O(min(n, m)) where m is charset size

ALGORITHM:
1. Use hash set to track characters in current window
2. Expand right pointer:
   - If s[right] not in set: Add it, update max length
   - If s[right] in set: Shrink from left until s[right] removed
3. Return max length

OPTIMIZATION using HashMap:
Instead of shrinking left one by one, jump left directly to position after last occurrence.

TRICK:
Use unordered_map to store character → index mapping.
When duplicate found, jump left pointer to max(left, lastIndex[char] + 1).
*/

class Solution {
public:
    // Approach 1: Using set, shrink one by one
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> window;
        int left = 0;
        int maxLength = 0;
        
        for (int right = 0; right < s.length(); right++) {
            // Shrink window until no duplicate
            while (window.count(s[right])) {
                window.erase(s[left]);
                left++;
            }
            
            // Add current character
            window.insert(s[right]);
            
            // Update max length
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
    
    // Approach 2: Using map, jump left pointer (more optimal)
    int lengthOfLongestSubstringOptimized(string s) {
        unordered_map<char, int> lastIndex;
        int left = 0;
        int maxLength = 0;
        
        for (int right = 0; right < s.length(); right++) {
            char c = s[right];
            
            // If character seen before and is in current window
            if (lastIndex.count(c) && lastIndex[c] >= left) {
                // Jump left pointer to right after last occurrence
                left = lastIndex[c] + 1;
            }
            
            // Update last index of current character
            lastIndex[c] = right;
            
            // Update max length
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    cout << "Test 1: " << sol.lengthOfLongestSubstring("abcabcbb") << endl;
    // Expected: 3 ("abc")
    
    // Test Case 2
    cout << "Test 2: " << sol.lengthOfLongestSubstring("bbbbb") << endl;
    // Expected: 1 ("b")
    
    // Test Case 3
    cout << "Test 3: " << sol.lengthOfLongestSubstring("pwwkew") << endl;
    // Expected: 3 ("wke")
    
    // Test Case 4 - Empty string
    cout << "Test 4: " << sol.lengthOfLongestSubstring("") << endl;
    // Expected: 0
    
    // Test Case 5 - All unique
    cout << "Test 5: " << sol.lengthOfLongestSubstring("abcdef") << endl;
    // Expected: 6
    
    // Test Case 6 - Special characters
    cout << "Test 6: " << sol.lengthOfLongestSubstring("a b c a b c") << endl;
    // Expected: 3 (" ab" or "a b")
    
    return 0;
}

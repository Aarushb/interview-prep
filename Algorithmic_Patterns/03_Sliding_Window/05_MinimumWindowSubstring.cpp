/*
PROBLEM: Minimum Window Substring
DESCRIPTION: Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".
CONSTRAINTS:
- m == s.length
- n == t.length
- 1 <= m, n <= 10^5
- s and t consist of uppercase and lowercase English letters.
EXAMPLE INPUT/OUTPUT:
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Input: s = "a", t = "a"
Output: "a"

Input: s = "a", t = "aa"
Output: ""
*/

/*
APPROACH:
This is a variable-size window problem but inverted from the usual "longest valid window" — here I want
the shortest window that's still valid. I build a required-character frequency map from t, then expand
right across s, adding characters to a window map and incrementing a "matched" counter whenever a
character's count in the window reaches exactly what's required. Once matched equals the number of
distinct required characters, the window is valid, so I greedily shrink from the left as far as possible
while staying valid, recording the minimum window length each time. This two-phase expand-then-shrink
dance ensures every position of left and right only moves forward, giving O(m+n) overall instead of
recomputing validity from scratch each time.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

HARDEST sliding window problem - VARIABLE SIZE MINIMUM window.

KEY INSIGHT:
Find SHORTEST substring containing ALL characters of t (with duplicates).

STRATEGY:
1. Expand window until all required characters are included
2. Once valid, shrink window while maintaining validity
3. Track minimum window during shrinking phase

ALGORITHM:
1. Build frequency map for t (required characters)
2. Use two pointers and window frequency map
3. Track "matched" count (how many unique chars have required frequency)
4. Expand right:
   - Add character to window
   - If frequency matches required, increment matched
5. When matched == required.size() (all chars satisfied):
   - Try shrinking left while maintaining validity
   - Update minimum window
6. Return minimum window

TIME: O(m + n) where m = s.length, n = t.length
SPACE: O(n)

TRICKS:
1. Use "matched" counter to quickly check if window is valid
2. matched == required.size() means ALL unique characters have sufficient frequency
3. Only update minWindow during shrinking phase (when window is valid)
4. Store result as indices (start, length) to avoid string copying during search
*/

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty()) return "";
        
        // Build frequency map for t
        unordered_map<char, int> required, window;
        for (char c : t) {
            required[c]++;
        }
        
        int left = 0, matched = 0;
        int minLength = INT_MAX, minStart = 0;
        
        for (int right = 0; right < s.length(); right++) {
            char rightChar = s[right];
            
            // Add right character to window
            if (required.count(rightChar)) {
                window[rightChar]++;
                
                // If this character's requirement is met
                if (window[rightChar] == required[rightChar]) {
                    matched++;
                }
            }
            
            // Try shrinking window while all requirements are met
            while (matched == required.size()) {
                // Update minimum window
                int currentLength = right - left + 1;
                if (currentLength < minLength) {
                    minLength = currentLength;
                    minStart = left;
                }
                
                // Remove left character
                char leftChar = s[left];
                if (required.count(leftChar)) {
                    if (window[leftChar] == required[leftChar]) {
                        matched--;  // No longer meeting requirement
                    }
                    window[leftChar]--;
                }
                
                left++;
            }
        }
        
        return minLength == INT_MAX ? "" : s.substr(minStart, minLength);
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    cout << "Test 1: " << sol.minWindow("ADOBECODEBANC", "ABC") << endl;
    // Expected: "BANC"
    
    // Test Case 2
    cout << "Test 2: " << sol.minWindow("a", "a") << endl;
    // Expected: "a"
    
    // Test Case 3
    cout << "Test 3: " << sol.minWindow("a", "aa") << endl;
    // Expected: ""
    
    // Test Case 4
    cout << "Test 4: " << sol.minWindow("ab", "b") << endl;
    // Expected: "b"
    
    // Test Case 5 - Multiple occurrences
    cout << "Test 5: " << sol.minWindow("aaaaaaaaaaaabbbbbcdd", "abcdd") << endl;
    // Expected: "abbbbbcdd"
    
    // Test Case 6
    cout << "Test 6: " << sol.minWindow("abc", "cba") << endl;
    // Expected: "abc"
    
    return 0;
}

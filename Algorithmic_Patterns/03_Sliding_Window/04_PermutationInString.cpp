/*
PROBLEM: Permutation in String
DESCRIPTION: Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
In other words, return true if one of s1's permutations is the substring of s2.
CONSTRAINTS:
- 1 <= s1.length, s2.length <= 10^4
- s1 and s2 consist of lowercase English letters.
EXAMPLE INPUT/OUTPUT:
Input: s1 = "ab", s2 = "eidbaooo"
Output: true
Explanation: s2 contains one permutation of s1 ("ba").

Input: s1 = "ab", s2 = "eidboaoo"
Output: false
*/

/*
APPROACH:
A permutation of s1 appearing in s2 just means some substring of s2 has exactly the same character
frequency counts as s1, so this is a fixed-size sliding window problem where the window size is
s1.length(). I build a frequency array for s1, then slide a same-size window across s2, maintaining a
frequency array for the window by adding the new right character and removing the character that falls
off the left as the window shifts. At each position I compare the two frequency arrays; if they match I've
found a permutation. To avoid an O(26) comparison at every step, I track a running "matched" counter that
increments/decrements as individual character counts become equal or unequal, so I can check equality in
O(1) and keep the whole thing O(n).
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

FIXED SIZE SLIDING WINDOW with frequency matching.

KEY INSIGHT:
A permutation of s1 in s2 means:
- A substring of s2 with same length as s1
- Same character frequencies as s1

APPROACH:
1. Create frequency map for s1
2. Use fixed-size sliding window of length s1.length() on s2
3. For each window, check if frequency matches s1
4. If match found, return true

OPTIMIZATION:
Instead of comparing entire frequency maps at each step:
- Track number of matched characters
- When adding/removing character, update matched count
- If matched == 26 (all letters matched), we found permutation

TIME: O(n), SPACE: O(1) (26 letters)

ALGORITHM:
1. Build frequency map for s1
2. Build frequency map for first window in s2
3. Check if they match
4. Slide window:
   - Remove leftmost character
   - Add new rightmost character
   - Check if frequencies match
5. Return true if match found, false otherwise

TRICK:
Use a counter variable to track how many character frequencies match.
This avoids comparing entire arrays at each step.
*/

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) return false;
        
        vector<int> s1Freq(26, 0), windowFreq(26, 0);
        
        // Build frequency map for s1
        for (char c : s1) {
            s1Freq[c - 'a']++;
        }
        
        // Build frequency map for first window
        int windowSize = s1.length();
        for (int i = 0; i < windowSize; i++) {
            windowFreq[s2[i] - 'a']++;
        }
        
        // Check first window
        if (s1Freq == windowFreq) return true;
        
        // Slide window
        for (int i = windowSize; i < s2.length(); i++) {
            // Add new character
            windowFreq[s2[i] - 'a']++;
            
            // Remove old character
            windowFreq[s2[i - windowSize] - 'a']--;
            
            // Check if frequencies match
            if (s1Freq == windowFreq) return true;
        }
        
        return false;
    }
    
    // Optimized: Track matched count
    bool checkInclusionOptimized(string s1, string s2) {
        if (s1.length() > s2.length()) return false;
        
        vector<int> s1Freq(26, 0), windowFreq(26, 0);
        
        for (char c : s1) {
            s1Freq[c - 'a']++;
        }
        
        int matched = 0;  // Number of characters with matching frequency
        
        // Build first window and count matches
        for (int i = 0; i < s1.length(); i++) {
            int idx = s2[i] - 'a';
            windowFreq[idx]++;
            if (windowFreq[idx] == s1Freq[idx]) {
                matched++;
            } else if (windowFreq[idx] == s1Freq[idx] + 1) {
                matched--;  // Was matched, now exceeded
            }
        }
        
        if (matched == 26) return true;
        
        // Slide window
        for (int i = s1.length(); i < s2.length(); i++) {
            // Add right character
            int rightIdx = s2[i] - 'a';
            windowFreq[rightIdx]++;
            if (windowFreq[rightIdx] == s1Freq[rightIdx]) {
                matched++;
            } else if (windowFreq[rightIdx] == s1Freq[rightIdx] + 1) {
                matched--;
            }
            
            // Remove left character
            int leftIdx = s2[i - s1.length()] - 'a';
            windowFreq[leftIdx]--;
            if (windowFreq[leftIdx] == s1Freq[leftIdx]) {
                matched++;
            } else if (windowFreq[leftIdx] == s1Freq[leftIdx] - 1) {
                matched--;
            }
            
            if (matched == 26) return true;
        }
        
        return false;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    cout << "Test 1: " << (sol.checkInclusion("ab", "eidbaooo") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 2
    cout << "Test 2: " << (sol.checkInclusion("ab", "eidboaoo") ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 3 - Exact match
    cout << "Test 3: " << (sol.checkInclusion("abc", "abc") ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 4 - s1 longer than s2
    cout << "Test 4: " << (sol.checkInclusion("abcd", "abc") ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 5
    cout << "Test 5: " << (sol.checkInclusion("adc", "dcda") ? "true" : "false") << endl;
    // Expected: true ("cda" is permutation of "adc")
    
    return 0;
}

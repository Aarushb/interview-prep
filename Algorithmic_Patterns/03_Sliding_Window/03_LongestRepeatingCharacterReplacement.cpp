/*
PROBLEM: Longest Repeating Character Replacement
DESCRIPTION: You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.
Return the length of the longest substring containing the same letter you can get after performing the above operations.
CONSTRAINTS:
- 1 <= s.length <= 10^5
- s consists of only uppercase English letters.
- 0 <= k <= s.length
EXAMPLE INPUT/OUTPUT:
Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with 'B's or vice versa.

Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace one 'A' in the middle with 'B', resulting in "AABBBBA". Substring "BBBB" has length 4.
*/

/*
APPROACH:
The trick here is reframing "at most k replacements" as a window validity condition: a window of length L
is achievable if L minus the count of its most frequent character is at most k, since that's exactly how
many characters we'd need to flip to make the whole window one letter. So I slide a window right, tracking
character frequencies and the max frequency seen in the window, and whenever the window becomes invalid
(replacements needed exceeds k) I shrink from the left by one. The clever bit is I never bother
decrementing maxFreq on shrink — since we only care about the best length ever seen, a stale maxFreq can't
cause a wrong answer, it just means the window won't grow further than it already has, which is fine and
keeps it O(n).
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

Advanced SLIDING WINDOW with frequency tracking.

KEY INSIGHT:
For a window to be valid:
- We can change at most k characters
- Window length - max frequency character count <= k
- This means we change all non-max-frequency characters

FORMULA:
windowLength - maxFrequencyInWindow <= k

ALGORITHM:
1. Use hash map to track frequency of characters in window
2. Track max frequency seen in window
3. Expand right:
   - Add character to window
   - Update max frequency
4. If window invalid (length - maxFreq > k):
   - Shrink from left
5. Track maximum valid window size

TIME: O(n), SPACE: O(26) = O(1)

OPTIMIZATION TRICK:
We don't need to decrease maxFreq when shrinking!
Why? We only care about finding MAXIMUM length.
If maxFreq decreases, the window length won't exceed previous max anyway.
This allows us to avoid recalculating max frequency.

PROOF:
- If current maxFreq is outdated (too high), window will keep shrinking
- But maxLength won't update because window is smaller
- When we find a better window, maxFreq will be updated correctly
*/

class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_map<char, int> freq;
        int left = 0;
        int maxFreq = 0;
        int maxLength = 0;
        
        for (int right = 0; right < s.length(); right++) {
            // Add right character to window
            freq[s[right]]++;
            
            // Update max frequency in current window
            maxFreq = max(maxFreq, freq[s[right]]);
            
            // Calculate number of replacements needed
            int windowLength = right - left + 1;
            int replacements = windowLength - maxFreq;
            
            // If we need more than k replacements, shrink window
            if (replacements > k) {
                freq[s[left]]--;
                left++;
            }
            
            // Update max length
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
    
    // Alternative: More explicit validation
    int characterReplacementVerbose(string s, int k) {
        vector<int> freq(26, 0);
        int left = 0;
        int maxFreq = 0;
        int maxLength = 0;
        
        for (int right = 0; right < s.length(); right++) {
            freq[s[right] - 'A']++;
            maxFreq = max(maxFreq, freq[s[right] - 'A']);
            
            while (right - left + 1 - maxFreq > k) {
                freq[s[left] - 'A']--;
                left++;
                // Note: Not updating maxFreq here (optimization)
            }
            
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    cout << "Test 1: " << sol.characterReplacement("ABAB", 2) << endl;
    // Expected: 4
    
    // Test Case 2
    cout << "Test 2: " << sol.characterReplacement("AABABBA", 1) << endl;
    // Expected: 4
    
    // Test Case 3 - All same characters
    cout << "Test 3: " << sol.characterReplacement("AAAA", 2) << endl;
    // Expected: 4
    
    // Test Case 4 - k = 0
    cout << "Test 4: " << sol.characterReplacement("ABCD", 0) << endl;
    // Expected: 1
    
    // Test Case 5 - Large k
    cout << "Test 5: " << sol.characterReplacement("ABCDE", 10) << endl;
    // Expected: 5
    
    // Test Case 6
    cout << "Test 6: " << sol.characterReplacement("ABABC", 2) << endl;
    // Expected: 5
    
    return 0;
}

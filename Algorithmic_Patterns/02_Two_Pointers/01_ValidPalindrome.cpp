/*
PROBLEM: Valid Palindrome
DESCRIPTION: A phrase is a palindrome if, after converting all uppercase letters into lowercase letters and removing all non-alphanumeric characters, it reads the same forward and backward. Alphanumeric characters include letters and numbers.
Given a string s, return true if it is a palindrome, or false otherwise.
CONSTRAINTS:
- 1 <= s.length <= 2 * 10^5
- s consists only of printable ASCII characters.
EXAMPLE INPUT/OUTPUT:
Input: s = "A man, a plan, a canal: Panama"
Output: true
Explanation: "amanaplanacanalpanama" is a palindrome.

Input: s = "race a car"
Output: false
Explanation: "raceacar" is not a palindrome.

Input: s = " "
Output: true
Explanation: After removing non-alphanumeric, s becomes empty "", which is a palindrome.
*/

/*
APPROACH:
Since checking a palindrome compares characters from both ends moving inward, this is a natural fit
for two pointers starting at the front and back of the string. At each step I skip non-alphanumeric
characters on either side, then compare the two characters case-insensitively; any mismatch means
it's not a palindrome. Doing this in place avoids building a cleaned copy of the string, giving O(n)
time and O(1) extra space.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

This is the simplest example of the Two Pointers pattern with opposite direction movement.

NAIVE APPROACH:
- Create a new string with only alphanumeric characters (all lowercase)
- Compare new string with its reverse
- Time: O(n), Space: O(n)

OPTIMAL APPROACH (Two Pointers):
- Use two pointers: one at start, one at end
- Skip non-alphanumeric characters on both sides
- Compare characters (case-insensitive)
- Move pointers toward center
- Time: O(n), Space: O(1)

ALGORITHM:
1. Initialize left = 0, right = s.length() - 1
2. While left < right:
   a. Skip non-alphanumeric from left
   b. Skip non-alphanumeric from right
   c. Convert both to lowercase and compare
   d. If different → not palindrome
   e. Move both pointers: left++, right--
3. If all characters match → palindrome

TRICK:
- Use isalnum() to check alphanumeric
- Use tolower() for case-insensitive comparison
- We don't need to create a new string - check in-place!
*/

class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0;
        int right = s.length() - 1;
        
        while (left < right) {
            // Skip non-alphanumeric characters from left
            while (left < right && !isalnum(s[left])) {
                left++;
            }
            
            // Skip non-alphanumeric characters from right
            while (left < right && !isalnum(s[right])) {
                right--;
            }
            
            // Compare characters (case-insensitive)
            if (tolower(s[left]) != tolower(s[right])) {
                return false;
            }
            
            left++;
            right--;
        }
        
        return true;
    }
    
    // Alternative: Using helper function
    bool isPalindromeClean(string s) {
        int left = 0, right = s.length() - 1;
        
        while (left < right) {
            if (!isAlphaNum(s[left])) {
                left++;
            } else if (!isAlphaNum(s[right])) {
                right--;
            } else if (toLowerCustom(s[left]) != toLowerCustom(s[right])) {
                return false;
            } else {
                left++;
                right--;
            }
        }
        
        return true;
    }
    
private:
    bool isAlphaNum(char c) {
        return (c >= 'a' && c <= 'z') || 
               (c >= 'A' && c <= 'Z') || 
               (c >= '0' && c <= '9');
    }
    
    char toLowerCustom(char c) {
        if (c >= 'A' && c <= 'Z') {
            return c + ('a' - 'A');
        }
        return c;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    string s1 = "A man, a plan, a canal: Panama";
    cout << "Test 1: " << (sol.isPalindrome(s1) ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 2
    string s2 = "race a car";
    cout << "Test 2: " << (sol.isPalindrome(s2) ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 3
    string s3 = " ";
    cout << "Test 3: " << (sol.isPalindrome(s3) ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 4 - Single character
    string s4 = "a";
    cout << "Test 4: " << (sol.isPalindrome(s4) ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 5 - Only special characters
    string s5 = ".,;!@#$%";
    cout << "Test 5: " << (sol.isPalindrome(s5) ? "true" : "false") << endl;
    // Expected: true (empty after removing special chars)
    
    // Test Case 6 - Numbers
    string s6 = "0P";
    cout << "Test 6: " << (sol.isPalindrome(s6) ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 7
    string s7 = "Madam";
    cout << "Test 7: " << (sol.isPalindrome(s7) ? "true" : "false") << endl;
    // Expected: true
    
    cout << "\n=== Using Clean Version ===" << endl;
    cout << "Test 8: " << (sol.isPalindromeClean(s1) ? "true" : "false") << endl;
    // Expected: true
    
    return 0;
}

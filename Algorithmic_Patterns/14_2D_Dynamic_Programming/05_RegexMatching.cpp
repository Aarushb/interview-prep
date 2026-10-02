/*
PROBLEM: Regular Expression Matching
DESCRIPTION: Given an input string s and a pattern p, implement regular expression matching with
support for '.' and '*' where '.' matches any single character and '*' matches zero or more of
the preceding element. The matching should cover the entire input string (not partial).
CONSTRAINTS: 1 <= s.length <= 20. 1 <= p.length <= 30. s contains only lowercase English letters.
p contains only lowercase English letters, '.', and '*'. It is guaranteed for each appearance of
the character '*', there will be a previous valid character to match.
EXAMPLE INPUT/OUTPUT:
  Input: s = "aa", p = "a"     -> Output: false
  Input: s = "aa", p = "a*"    -> Output: true
  Input: s = "ab", p = ".*"    -> Output: true
  Input: s = "aab", p = "c*a*b" -> Output: true
  Input: s = "mississippi", p = "mis*is*p*." -> Output: false
*/

/*
APPROACH:
The trickiest 2D DP in this set because the pattern dimension has a wildcard operator, not just
literal characters. Let dp[i][j] = true if s[0..i) matches p[0..j). If p[j-1] is a plain char or
'.', it must match s[i-1], so dp[i][j] = dp[i-1][j-1] && (p[j-1]=='.' || p[j-1]==s[i-1]). If
p[j-1] is '*', it refers to p[j-2], and we have two choices: treat "x*" as matching zero
occurrences (dp[i][j] = dp[i][j-2], skip the pair entirely), or, if p[j-2] matches s[i-1], treat
it as matching one more occurrence and stay on the same pattern position (dp[i][j] |= dp[i-1][j]).
Base case dp[0][0] = true (empty matches empty), and dp[0][j] handles patterns like "a*b*c*" that
can match an empty string by chaining zero-occurrence stars.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<char>> dp(m + 1, vector<char>(n + 1, false));
        dp[0][0] = true;

        // Empty string vs pattern: only possible if pattern is a chain of "x*" pairs.
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == '*' && j >= 2) {
                dp[0][j] = dp[0][j - 2];
            }
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[j - 1] == '*') {
                    // '*' must have a preceding element (guaranteed by constraints), j >= 2.
                    bool zeroOccurrence = dp[i][j - 2];
                    bool oneMoreOccurrence = false;
                    char prevPatChar = p[j - 2];
                    if (prevPatChar == '.' || prevPatChar == s[i - 1]) {
                        oneMoreOccurrence = dp[i - 1][j];
                    }
                    dp[i][j] = zeroOccurrence || oneMoreOccurrence;
                } else if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = false;
                }
            }
        }
        return dp[m][n];
    }
};

int main() {
    Solution sol;

    cout << boolalpha;
    cout << sol.isMatch("aa", "a") << endl;                   // expected false
    cout << sol.isMatch("aa", "a*") << endl;                  // expected true
    cout << sol.isMatch("ab", ".*") << endl;                  // expected true
    cout << sol.isMatch("aab", "c*a*b") << endl;               // expected true
    cout << sol.isMatch("mississippi", "mis*is*p*.") << endl; // expected false

    return 0;
}

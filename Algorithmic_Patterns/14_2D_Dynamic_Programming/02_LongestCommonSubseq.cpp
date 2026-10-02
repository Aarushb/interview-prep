/*
PROBLEM: Longest Common Subsequence
DESCRIPTION: Given two strings text1 and text2, return the length of their longest common
subsequence. If there is no common subsequence, return 0. A subsequence of a string is a new
string generated from the original string with some characters (can be none) deleted without
changing the relative order of the remaining characters. A common subsequence of two strings is
a subsequence that is common to both strings.
CONSTRAINTS: 1 <= text1.length, text2.length <= 1000. text1 and text2 consist of only lowercase
English characters.
EXAMPLE INPUT/OUTPUT:
  Input: text1 = "abcde", text2 = "ace" -> Output: 3 ("ace")
  Input: text1 = "abc", text2 = "abc"   -> Output: 3
  Input: text1 = "abc", text2 = "def"   -> Output: 0
*/

/*
APPROACH:
Classic two-string prefix DP: let dp[i][j] be the LCS length between the first i characters of
text1 and the first j characters of text2. If text1[i-1] == text2[j-1], that matching character
must be part of some optimal LCS, so dp[i][j] = dp[i-1][j-1] + 1. Otherwise the LCS either skips
the current character of text1 or of text2, so dp[i][j] = max(dp[i-1][j], dp[i][j-1]). Base
cases dp[i][0] = dp[0][j] = 0 (an empty string has no common subsequence with anything). Filled
row by row in O(m*n) time and space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};

int main() {
    Solution sol;

    cout << sol.longestCommonSubsequence("abcde", "ace") << endl; // expected 3
    cout << sol.longestCommonSubsequence("abc", "abc") << endl;   // expected 3
    cout << sol.longestCommonSubsequence("abc", "def") << endl;   // expected 0
    cout << sol.longestCommonSubsequence("bsbininm", "jmjkbkjkv") << endl; // expected 1

    return 0;
}

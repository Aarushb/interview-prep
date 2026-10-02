/*
PROBLEM: Edit Distance
DESCRIPTION: Given two strings word1 and word2, return the minimum number of operations required
to convert word1 to word2. You have the following three operations permitted on a word: insert a
character, delete a character, or replace a character.
CONSTRAINTS: 0 <= word1.length, word2.length <= 500. word1 and word2 consist of lowercase English
letters.
EXAMPLE INPUT/OUTPUT:
  Input: word1 = "horse", word2 = "ros"     -> Output: 3
  Input: word1 = "intention", word2 = "execution" -> Output: 5
*/

/*
APPROACH:
Two-string prefix DP again, but this time the recurrence considers three possible operations
instead of two. Let dp[i][j] be the minimum number of edits to turn the first i characters of
word1 into the first j characters of word2. If the last characters match, no operation is needed
there: dp[i][j] = dp[i-1][j-1]. Otherwise we take the best of three choices: delete from word1
(dp[i-1][j] + 1), insert into word1 to match word2's next char (dp[i][j-1] + 1), or replace
word1's char (dp[i-1][j-1] + 1). Base cases dp[i][0] = i and dp[0][j] = j represent converting to/
from an empty string purely with inserts/deletes.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 0; i <= m; i++) dp[i][0] = i; // delete all i chars of word1
        for (int j = 0; j <= n; j++) dp[0][j] = j; // insert all j chars of word2

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1 + min({dp[i - 1][j],     // delete
                                         dp[i][j - 1],     // insert
                                         dp[i - 1][j - 1]}); // replace
                }
            }
        }
        return dp[m][n];
    }
};

int main() {
    Solution sol;

    cout << sol.minDistance("horse", "ros") << endl;             // expected 3
    cout << sol.minDistance("intention", "execution") << endl;   // expected 5
    cout << sol.minDistance("", "abc") << endl;                  // expected 3
    cout << sol.minDistance("abc", "abc") << endl;                // expected 0

    return 0;
}

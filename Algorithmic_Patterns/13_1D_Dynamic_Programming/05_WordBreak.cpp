/*
PROBLEM: Word Break (LeetCode 139)
DESCRIPTION: Given a string s and a dictionary of strings wordDict, return true if s can be
segmented into a space-separated sequence of one or more dictionary words. The same word in the
dictionary may be reused multiple times in the segmentation.
CONSTRAINTS: 1 <= s.length <= 300, 1 <= wordDict.length <= 1000, 1 <= wordDict[i].length <= 20,
s and wordDict[i] consist of only lowercase English letters, all strings in wordDict are unique.
EXAMPLE INPUT/OUTPUT:
  s = "leetcode", wordDict = ["leet","code"] -> Output: true  ("leet" + "code")
  s = "catsandog", wordDict = ["cats","dog","sand","and","cat"] -> Output: false
*/

/*
APPROACH:
Let dp[i] = true if the prefix s[0..i) (the first i characters) can be fully segmented into
dictionary words, with dp[0] = true as the base case (the empty prefix trivially "breaks" into
zero words). For each position i, we look back at every valid split point j < i where dp[j] is
already true, and check whether the substring s[j..i) is itself a dictionary word; if so,
dp[i] = true. To make dictionary lookups O(1) average instead of O(dict size), the word list is
loaded into an unordered_set first. The answer is dp[n]. This is O(n^2) time (n positions times
up to n split points, with O(1) average substring lookup via hashing) and O(n) space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        int n = s.size();

        vector<bool> dp(n + 1, false);
        dp[0] = true; // empty prefix is trivially segmentable

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && dict.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break; // no need to check other split points once dp[i] is true
                }
            }
        }

        return dp[n];
    }
};

int main() {
    Solution sol;

    vector<string> dict1 = {"leet", "code"};
    cout << "Test 1: " << boolalpha << sol.wordBreak("leetcode", dict1) << " (expected true)" << endl;

    vector<string> dict2 = {"apple", "pen"};
    cout << "Test 2: " << sol.wordBreak("applepenapple", dict2) << " (expected true)" << endl;

    vector<string> dict3 = {"cats", "dog", "sand", "and", "cat"};
    cout << "Test 3: " << sol.wordBreak("catsandog", dict3) << " (expected false)" << endl;

    vector<string> dict4 = {"a", "aa", "aaa", "aaaa"};
    cout << "Test 4: " << sol.wordBreak("aaaaaaa", dict4) << " (expected true)" << endl;

    return 0;
}

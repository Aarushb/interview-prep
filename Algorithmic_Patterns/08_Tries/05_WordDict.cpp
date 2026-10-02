/*
PROBLEM: Word Break (Word Dictionary)
DESCRIPTION: Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of dictionary words.
CONSTRAINTS: 1 <= s.length <= 300; 1 <= word.length <= 20; dictionary size <= 1000
EXAMPLE: s="leetcode", dict=["leet","code"] -> true; s="catsandog", dict=["cats","dog","sand","and","cat"] -> false
*/

/*
APPROACH:
Word Break isn't literally a trie problem but shares the same "does this prefix exist"
mindset: at each index, check whether some prefix of the remaining suffix is a dictionary
word, and if so, recurse on the rest of the string. It's solved with memoized recursion
(top-down DP) -- canBreak(idx) tries every prefix starting at idx, and caches whether the
suffix starting at idx is breakable to avoid exponential recomputation. A hash set gives
O(1) dictionary lookups here; a trie would also work and scale better when dictionary words
share a lot of overlapping prefixes.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict){
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        vector<int> memo(s.size(), -1);
        return canBreak(0, s, dict, memo);
    }
private:
    bool canBreak(int idx, const string& s, const unordered_set<string>& dict, vector<int>& memo){
        if(idx == (int)s.size()) return true;
        if(memo[idx] != -1) return memo[idx];
        string cur;
        for(int i=idx;i<(int)s.size();++i){
            cur.push_back(s[i]);
            if(dict.count(cur) && canBreak(i+1, s, dict, memo)){
                memo[idx]=1; return true;
            }
        }
        memo[idx]=0; return false;
    }
};

int main(){
    Solution sol;
    vector<string> d1 = {"leet","code"};
    vector<string> d2 = {"cats","dog","sand","and","cat"};
    vector<string> d3 = {"apple","pen"};
    cout << boolalpha;
    cout << sol.wordBreak("leetcode", d1) << "\n";    // true
    cout << sol.wordBreak("catsandog", d2) << "\n";   // false
    cout << sol.wordBreak("applepenapple", d3) << "\n"; // true
    return 0;
}

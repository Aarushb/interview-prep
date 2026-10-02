/*
PROBLEM: Longest Common Prefix
DESCRIPTION: Given an array of strings, find the longest common prefix among them. Return an empty string if none.
CONSTRAINTS: 1 <= strs.length <= 200; 0 <= strs[i].length <= 200; strs[i] consists of lowercase English letters (if non-empty).
EXAMPLE: ["flower","flow","flight"] -> "fl"
*/

/*
APPROACH:
Rather than building an actual trie, this reduces to simple pairwise string comparison: the
common prefix of the whole array is found by shrinking a running candidate prefix as each
subsequent string is compared against it. This is O(n * m) in the worst case (n strings,
m = length of the shortest one) and conceptually mirrors what a trie built from all the
words would give you -- the path from the root to the first branching (fork) node.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs){
        if(strs.empty()) return "";
        string prefix = strs[0];
        for(size_t i=1;i<strs.size() && !prefix.empty();++i){
            prefix = common(prefix, strs[i]);
        }
        return prefix;
    }
private:
    string common(const string& a, const string& b){
        size_t len = min(a.size(), b.size());
        size_t i=0;
        while(i<len && a[i]==b[i]) ++i;
        return a.substr(0, i);
    }
};

int main(){
    Solution sol;
    vector<string> s1 = {"flower","flow","flight"};
    vector<string> s2 = {"dog","racecar","car"};
    vector<string> s3 = {"interview","intermediate","internal","internet"};

    cout << sol.longestCommonPrefix(s1) << "\n"; // fl
    cout << sol.longestCommonPrefix(s2) << "\n"; // empty
    cout << sol.longestCommonPrefix(s3) << "\n"; // inter
    return 0;
}

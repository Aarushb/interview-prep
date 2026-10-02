/*
PROBLEM: Palindrome Partitioning
DESCRIPTION: Given a string s, partition s such that every substring of the partition is a
palindrome. Return all possible palindrome partitioning of s.
CONSTRAINTS: 1 <= s.length <= 16; s consists of only lowercase English letters.
EXAMPLE INPUT/OUTPUT: s = "aab" -> [["a","a","b"],["aa","b"]]; s = "a" -> [["a"]].
*/

/*
APPROACH:
Backtrack over the starting index idx of the unprocessed suffix of the string. At each step, try
every possible end position for the next cut, and only recurse into it if the substring
s[idx..end] is itself a palindrome — this is the pruning step, since we never bother exploring a
non-palindromic prefix further. When idx reaches the end of the string, the current path of
palindromic pieces is a valid full partition and gets recorded; the substring is then popped
before trying the next end position, standard choose/explore/un-choose.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s){
        vector<vector<string>> res; vector<string> cur;
        dfs(0, s, cur, res);
        return res;
    }
private:
    bool isPal(const string& s, int l, int r){
        while(l<r) if(s[l++]!=s[r--]) return false; return true;
    }
    void dfs(int idx, const string& s, vector<string>& cur, vector<vector<string>>& res){
        if(idx==(int)s.size()){ res.push_back(cur); return; }
        for(int end=idx; end<(int)s.size(); ++end){
            if(isPal(s, idx, end)){
                cur.push_back(s.substr(idx, end-idx+1));
                dfs(end+1, s, cur, res);
                cur.pop_back();
            }
        }
    }
};

int main(){
    Solution sol;
    auto res = sol.partition("aab");
    for(auto& v: res){
        cout << "[";
        for(size_t i=0;i<v.size();++i){ cout<<v[i]; if(i+1<v.size()) cout<<","; }
        cout << "] ";
    }
    cout << "\n"; // expect [a,a,b] [aa,b]
    return 0;
}

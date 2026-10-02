/*
PROBLEM: Word Search II (find all words on board)
DESCRIPTION: Given an m x n board of letters and a list of words, return all words that can be formed by letters connected horizontally or vertically. Each cell may be used once per word.
CONSTRAINTS:
- 1 <= m,n <= 12, board letters lowercase
- 1 <= words.length <= 3e4, word length <= 10
EXAMPLE INPUT/OUTPUT:
Board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"] -> Output: ["oath","eat"]
*/

/*
APPROACH:
This combines a trie (to prune the search by prefixes shared across many target words) with
backtracking DFS over the grid. Build a trie of all target words first, then DFS from every
board cell, following trie edges as long as the current path is still a valid prefix -- if
no matching trie child exists, that branch is abandoned immediately instead of exploring
further. Marking a found word's node with end = false right after recording it avoids
duplicate results without needing a separate visited-words set.
*/

#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    bool end = false;
    string word;
    array<TrieNode*,26> next{};
    TrieNode(){ next.fill(nullptr); }
};

class Trie {
public:
    Trie(): root(new TrieNode()) {}
    TrieNode* getRoot(){ return root; }
    void insert(const string& w){
        auto* cur = root;
        for(char c: w){
            int i=c-'a';
            if(!cur->next[i]) cur->next[i]=new TrieNode();
            cur=cur->next[i];
        }
        cur->end=true; cur->word=w;
    }
private:
    TrieNode* root;
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie trie; for (auto& w: words) trie.insert(w);
        TrieNode* root = trie.getRoot();
        int m = board.size(), n = board[0].size();
        vector<string> res;
        vector<vector<bool>> vis(m, vector<bool>(n,false));
        for(int i=0;i<m;i++) for(int j=0;j<n;j++) dfs(board, i, j, root, vis, res);
        return res;
    }
private:
    void dfs(vector<vector<char>>& b,int r,int c,TrieNode* node,vector<vector<bool>>& vis,vector<string>& res){
        int m=b.size(), n=b[0].size();
        if(r<0||c<0||r>=m||c>=n||vis[r][c]) return;
        char ch=b[r][c];
        TrieNode* nxt=node->next[ch-'a'];
        if(!nxt) return;
        vis[r][c]=true;
        if(nxt->end){ res.push_back(nxt->word); nxt->end=false; } // avoid dup
        static int dirs[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
        for(auto& d:dirs) dfs(b,r+d[0],c+d[1],nxt,vis,res);
        vis[r][c]=false;
    }
};

int main(){
    vector<vector<char>> board={{'o','a','a','n'},{'e','t','a','e'},{'i','h','k','r'},{'i','f','l','v'}};
    vector<string> words={"oath","pea","eat","rain"};
    Solution sol;
    auto res = sol.findWords(board, words);
    sort(res.begin(), res.end());
    for(auto&s:res) cout<<s<<" ";
    cout<<"\n"; // expect eat oath
    return 0;
}

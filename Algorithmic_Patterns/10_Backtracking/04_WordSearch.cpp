/*
PROBLEM: Word Search
DESCRIPTION: Given an m x n grid of characters board and a string word, return true if word
exists in the grid. The word can be constructed from letters of sequentially adjacent cells,
where adjacent cells are horizontally or vertically neighboring. The same cell may not be used
more than once within one word's path.
CONSTRAINTS: m == board.length; n == board[i].length; 1 <= m, n <= 6; 1 <= word.length <= 15;
board and word consist of only lowercase and uppercase English letters.
EXAMPLE INPUT/OUTPUT: board = [[A,B,C,E],[S,F,C,S],[A,D,E,E]], word = "ABCCED" -> true;
word = "SEE" -> true; word = "ABCB" -> false.
*/

/*
APPROACH:
Try every cell in the grid as a potential starting point for the word, and from each, run a DFS
that tries to match the word character by character against the four neighboring directions.
Mark a cell visited before recursing into its neighbors and unmark it immediately after (whether
the recursive call succeeded or failed) so the same cell can be reused by a different candidate
path — this is the standard grid-backtracking visited/unvisited toggle. The recursion succeeds
as soon as the full word length is matched, and fails fast whenever a cell is out of bounds,
already visited, or doesn't match the expected character.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word){
        int m=board.size(), n=board[0].size();
        vector<vector<bool>> vis(m, vector<bool>(n,false));
        for(int i=0;i<m;i++) for(int j=0;j<n;j++)
            if(dfs(board, word, 0, i, j, vis)) return true;
        return false;
    }
private:
    bool dfs(vector<vector<char>>& b, const string& w, int k, int r, int c, vector<vector<bool>>& vis){
        if(k==(int)w.size()) return true;
        int m=b.size(), n=b[0].size();
        if(r<0||c<0||r>=m||c>=n||vis[r][c]||b[r][c]!=w[k]) return false;
        vis[r][c]=true;
        static int d[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
        for(auto& x:d){ if(dfs(b,w,k+1,r+x[0],c+x[1],vis)) { vis[r][c]=false; return true; } }
        vis[r][c]=false; return false;
    }
};

int main(){
    vector<vector<char>> board={{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    Solution sol;
    cout << boolalpha << sol.exist(board, "ABCCED") << "\n"; // true
    cout << sol.exist(board, "SEE") << "\n"; // true
    cout << sol.exist(board, "ABCB") << "\n"; // false
    return 0;
}

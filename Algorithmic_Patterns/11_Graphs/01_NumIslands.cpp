/*
PROBLEM: Number of Islands
DESCRIPTION: Given an m x n 2D binary grid which represents a map of '1's (land) and '0's
(water), return the number of islands. An island is surrounded by water and is formed by
connecting adjacent lands horizontally or vertically.
CONSTRAINTS: m == grid.length; n == grid[i].length; 1 <= m, n <= 300; grid[i][j] is '0' or '1'.
EXAMPLE INPUT/OUTPUT: grid = [[1,1,0,0,0],[1,1,0,0,0],[0,0,1,0,0],[0,0,0,1,1]] -> 3.
*/

/*
APPROACH:
Scan every cell in the grid; whenever an unvisited land cell ('1') is found, it's the start of a
new island, so increment the count and run a BFS flood fill from it to mark every reachable land
cell (up/down/left/right) as visited so it's never counted again. This is a standard connected-
components-in-a-grid pattern: each BFS call consumes one entire island, and since every cell is
visited at most once overall, the total work stays linear in the grid size.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid){
        int m=grid.size(), n=grid[0].size(), cnt=0;
        vector<vector<bool>> vis(m, vector<bool>(n,false));
        for(int i=0;i<m;i++) for(int j=0;j<n;j++) if(grid[i][j]=='1' && !vis[i][j]){
            bfs(i,j,grid,vis); cnt++; }
        return cnt;
    }
private:
    void bfs(int r,int c, vector<vector<char>>& g, vector<vector<bool>>& vis){
        int m=g.size(), n=g[0].size();
        queue<pair<int,int>> q; q.push({r,c}); vis[r][c]=true;
        static int d[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
        while(!q.empty()){
            auto [x,y]=q.front(); q.pop();
            for(auto& dir:d){
                int nx=x+dir[0], ny=y+dir[1];
                if(nx>=0 && ny>=0 && nx<m && ny<n && g[nx][ny]=='1' && !vis[nx][ny]){
                    vis[nx][ny]=true; q.push({nx,ny});
                }
            }
        }
    }
};

int main(){
    vector<vector<char>> g={{'1','1','0','0','0'},{'1','1','0','0','0'},{'0','0','1','0','0'},{'0','0','0','1','1'}};
    Solution sol;
    cout << sol.numIslands(g) << "\n"; // 3
    return 0;
}

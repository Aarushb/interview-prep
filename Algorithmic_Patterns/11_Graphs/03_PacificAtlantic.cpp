/*
PROBLEM: Pacific Atlantic Water Flow
DESCRIPTION: There is an m x n rectangular island that borders both the Pacific Ocean (top and
left edges) and the Atlantic Ocean (bottom and right edges). heights[r][c] represents the height
above sea level of the cell at (r, c). Water can flow from a cell to an adjacent cell (north,
south, east, west) with height less than or equal to the current cell's height. Return a list of
grid coordinates where water can flow to both the Pacific and Atlantic oceans.
CONSTRAINTS: m == heights.length; n == heights[r].length; 1 <= m, n <= 200;
0 <= heights[r][c] <= 10^5.
EXAMPLE INPUT/OUTPUT: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
-> [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]].
*/

/*
APPROACH:
Forward simulation (checking, for every cell, whether water from it can reach both oceans) is
expensive because it requires a full search per cell. Instead, reverse the problem: run a BFS
from every Pacific-border cell simultaneously, flowing "uphill" (to a neighbor whose height is
>= the current cell's height, which is the reverse of water flowing downhill), to mark every
cell that *could* drain into the Pacific. Do the same independently from the Atlantic-border
cells. A cell that got marked by both searches is exactly a cell whose water can reach both
oceans, so the answer is the intersection of the two reachability sets.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& h){
        int m=h.size(), n=h[0].size();
        vector<vector<bool>> pac(m, vector<bool>(n,false)), atl(m, vector<bool>(n,false));
        queue<pair<int,int>> qp, qa;
        for(int i=0;i<m;i++){ qp.push({i,0}); qa.push({i,n-1}); }
        for(int j=0;j<n;j++){ qp.push({0,j}); qa.push({m-1,j}); }
        bfs(h, qp, pac); bfs(h, qa, atl);
        vector<vector<int>> res;
        for(int i=0;i<m;i++) for(int j=0;j<n;j++) if(pac[i][j] && atl[i][j]) res.push_back({i,j});
        return res;
    }
private:
    void bfs(vector<vector<int>>& h, queue<pair<int,int>> q, vector<vector<bool>>& vis){
        int m=h.size(), n=h[0].size();
        static int d[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
        while(!q.empty()){
            auto [r,c]=q.front(); q.pop();
            if(vis[r][c]) continue; vis[r][c]=true;
            for(auto& x:d){
                int nr=r+x[0], nc=c+x[1];
                if(nr>=0&&nc>=0&&nr<m&&nc<n && !vis[nr][nc] && h[nr][nc]>=h[r][c])
                    q.push({nr,nc});
            }
        }
    }
};

int main(){
    vector<vector<int>> grid={{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}};
    Solution sol;
    auto res = sol.pacificAtlantic(grid);
    sort(res.begin(), res.end());
    for(auto& v: res){ cout<<"("<<v[0]<<","<<v[1]<<") "; }
    cout << "\n";
    return 0;
}

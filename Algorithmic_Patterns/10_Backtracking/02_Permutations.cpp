/*
PROBLEM: Permutations
DESCRIPTION: Given an array nums of distinct integers, return all the possible permutations.
You can return the answer in any order.
CONSTRAINTS: 1 <= nums.length <= 6; -10 <= nums[i] <= 10; all integers of nums are unique.
EXAMPLE INPUT/OUTPUT: nums = [1,2,3] -> [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]].
*/

/*
APPROACH:
At each level of the recursion, try every element that hasn't been used yet in the current path,
tracked with a boolean used[] array. Mark the chosen element used, append it to the path, recurse
to fill the remaining positions, then undo (unmark and pop) before trying the next candidate at
that level. When the path length equals nums.size(), a full permutation has been built and is
recorded. This explores exactly n! leaves since each level has one fewer available choice than
the last.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums){
        vector<vector<int>> res; vector<int> cur; vector<int> used(nums.size(),0);
        dfs(nums, used, cur, res);
        return res;
    }
private:
    void dfs(const vector<int>& nums, vector<int>& used, vector<int>& cur, vector<vector<int>>& res){
        if(cur.size()==nums.size()){ res.push_back(cur); return; }
        for(size_t i=0;i<nums.size();++i){
            if(used[i]) continue;
            used[i]=1; cur.push_back(nums[i]);
            dfs(nums, used, cur, res);
            cur.pop_back(); used[i]=0;
        }
    }
};

int main(){
    Solution sol; vector<int> v={1,2,3};
    auto res = sol.permute(v);
    sort(res.begin(), res.end());
    for(auto& r: res){
        for(size_t i=0;i<r.size();++i){ cout<<r[i]; if(i+1<r.size()) cout<<","; }
        cout << " | ";
    }
    cout << "\n";
    return 0;
}

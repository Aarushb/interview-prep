/*
PROBLEM: Subsets (Power Set)
DESCRIPTION: Given an integer array nums of unique elements, return all possible subsets
(the power set). The solution set must not contain duplicate subsets.
CONSTRAINTS: 1 <= nums.length <= 10; -10 <= nums[i] <= 10; all elements of nums are unique.
EXAMPLE INPUT/OUTPUT: nums = [1,2,3] -> [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]].
*/

/*
APPROACH:
Walk through the array index by index and, at each index, branch into two choices: skip the
current element, or include it in the running path. This decision tree has exactly 2^n leaves
(one per subset), and recording the path at every leaf (i.e. after processing all indices)
enumerates every subset exactly once without needing explicit duplicate checks, since elements
are unique. The include branch pushes the element before recursing and pops it after (the
backtrack step) so the same path vector can be reused across all branches.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums){
        vector<vector<int>> res; vector<int> cur;
        dfs(0, nums, cur, res);
        return res;
    }
private:
    void dfs(int i, const vector<int>& nums, vector<int>& cur, vector<vector<int>>& res){
        if(i==(int)nums.size()){ res.push_back(cur); return; }
        dfs(i+1, nums, cur, res); // skip
        cur.push_back(nums[i]);
        dfs(i+1, nums, cur, res); // take
        cur.pop_back();
    }
};

int main(){
    Solution sol; vector<int> v={1,2,3};
    auto res = sol.subsets(v);
    sort(res.begin(), res.end());
    for(auto& r: res){
        cout << "{";
        for(size_t i=0;i<r.size();++i){ cout<<r[i]; if(i+1<r.size()) cout<<","; }
        cout << "}" << " ";
    }
    cout << "\n";
    return 0;
}

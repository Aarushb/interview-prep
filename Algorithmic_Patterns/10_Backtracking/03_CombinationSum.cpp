/*
PROBLEM: Combination Sum
DESCRIPTION: Given an array of distinct positive integers candidates and a target integer target,
return a list of all unique combinations of candidates where the chosen numbers sum to target.
The same number may be chosen from candidates an unlimited number of times. Two combinations are
unique if the frequency of at least one of the chosen numbers is different.
CONSTRAINTS: 1 <= candidates.length <= 30; 2 <= candidates[i] <= 40; all elements of candidates
are distinct; 1 <= target <= 40.
EXAMPLE INPUT/OUTPUT: candidates = [2,3,6,7], target = 7 -> [[2,2,3],[7]];
candidates = [2,3,5], target = 8 -> [[2,2,2,2],[2,3,3],[3,5]].
*/

/*
APPROACH:
Sort the candidates first so that the search can prune as early as possible and so combinations
are built in non-decreasing order (which avoids generating the same combination in a different
order). Backtrack over the sorted array starting from index idx, and at each step either add
candidates[idx] again (passing idx, not idx+1, to allow reuse) or move to the next distinct
candidate. Because the array is sorted, as soon as a candidate would push the running sum over
target, every later candidate would too, so the loop can break immediately instead of just
continuing — a key pruning trick for sorted-input backtracking.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target){
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res; vector<int> cur;
        dfs(0, target, candidates, cur, res);
        return res;
    }
private:
    void dfs(int idx, int rem, const vector<int>& cand, vector<int>& cur, vector<vector<int>>& res){
        if(rem==0){ res.push_back(cur); return; }
        for(int i=idx;i<(int)cand.size();++i){
            if(cand[i]>rem) break;
            cur.push_back(cand[i]);
            dfs(i, rem-cand[i], cand, cur, res);
            cur.pop_back();
        }
    }
};

int main(){
    Solution sol; vector<int> c={2,3,6,7};
    auto r1 = sol.combinationSum(c, 7);
    for(auto& v: r1){ for(size_t i=0;i<v.size();++i){ cout<<v[i]<<(i+1<v.size()?" ":""); } cout<<" | "; }
    cout << "\n"; // expect 2 2 3 | 7 |
    vector<int> c2={2,3,5};
    auto r2 = sol.combinationSum(c2, 8);
    for(auto& v: r2){ for(size_t i=0;i<v.size();++i){ cout<<v[i]<<(i+1<v.size()?" ":""); } cout<<" | "; }
    cout << "\n"; // expect 2 2 2 2 | 2 3 3 | 3 5 |
    return 0;
}

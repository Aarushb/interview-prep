/*
PROBLEM: Jump Game
DESCRIPTION: You are given an integer array nums. You are initially positioned at the array's
first index, and each element in the array represents your maximum jump length at that position.
Return true if you can reach the last index, or false otherwise.
CONSTRAINTS: 1 <= nums.length <= 10^4. 0 <= nums[i] <= 10^5.
EXAMPLE INPUT/OUTPUT:
  Input: nums = [2,3,1,1,4] -> Output: true
  Input: nums = [3,2,1,0,4] -> Output: false
*/

/*
APPROACH:
Greedy single pass tracking "farthest index reachable so far". At each index i, if i is beyond
the farthest reachable point, we can never get here, so we fail immediately. Otherwise we update
farthest = max(farthest, i + nums[i]). The exchange argument: we never need to consider *which*
specific jump length to use at a position, only the single best (farthest) outcome any jump from
positions reachable so far can produce, because a smaller jump from the same or an earlier
position can never reach further than the greedy running maximum. If farthest ever reaches or
exceeds the last index, we can stop early and return true.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int farthest = 0;

        for (int i = 0; i < n; i++) {
            if (i > farthest) return false; // this index is unreachable
            farthest = max(farthest, i + nums[i]);
            if (farthest >= n - 1) return true; // early exit
        }
        return true;
    }
};

int main() {
    Solution sol;

    vector<int> n1 = {2, 3, 1, 1, 4};
    cout << boolalpha << sol.canJump(n1) << endl; // expected true

    vector<int> n2 = {3, 2, 1, 0, 4};
    cout << boolalpha << sol.canJump(n2) << endl; // expected false

    vector<int> n3 = {0};
    cout << boolalpha << sol.canJump(n3) << endl; // expected true (already at last index)

    vector<int> n4 = {2, 0, 0};
    cout << boolalpha << sol.canJump(n4) << endl; // expected true

    return 0;
}

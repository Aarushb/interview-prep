/*
PROBLEM: Jump Game II
DESCRIPTION: You are given a 0-indexed array of integers nums of length n. You are initially
positioned at index 0. Each element nums[i] represents the maximum length of a forward jump from
index i. In other words, if you are at index i, you can jump to any index (i + j) where 0 <= j <=
nums[i] and i + j < n. Return the minimum number of jumps to reach index n - 1. You can assume
that you can always reach index n - 1.
CONSTRAINTS: 1 <= nums.length <= 10^4. 0 <= nums[i] <= 1000. It's guaranteed that you can reach
index n - 1.
EXAMPLE INPUT/OUTPUT:
  Input: nums = [2,3,1,1,4] -> Output: 2 (jump 1 step from index 0 to 1, then 3 steps to last)
  Input: nums = [2,3,0,1,4] -> Output: 2
*/

/*
APPROACH:
This is the "implicit BFS by levels" greedy: think of each jump as expanding a reachable window
[curEnd] to a new farthest boundary. We scan indices and, for each index within the current jump's
window, greedily track the farthest we could reach with one more jump. When we reach the end of
the current window (i == curEnd), that means we've exhausted every position reachable in `jumps`
jumps, so we must commit to one more jump and set the window's new end to farthest. This greedily
delays counting a jump for as long as possible, which is safe because farthest is the best
possible outcome of any jump taken from within the current window — no smarter choice within the
window could ever reach further. Runs in O(n) with O(1) extra space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int jumps = 0, curEnd = 0, farthest = 0;

        for (int i = 0; i < n - 1; i++) {
            farthest = max(farthest, i + nums[i]);
            if (i == curEnd) {
                jumps++;
                curEnd = farthest;
            }
        }
        return jumps;
    }
};

int main() {
    Solution sol;

    vector<int> n1 = {2, 3, 1, 1, 4};
    cout << sol.jump(n1) << endl; // expected 2

    vector<int> n2 = {2, 3, 0, 1, 4};
    cout << sol.jump(n2) << endl; // expected 2

    vector<int> n3 = {1, 1, 1, 1};
    cout << sol.jump(n3) << endl; // expected 3

    vector<int> n4 = {1};
    cout << sol.jump(n4) << endl; // expected 0 (already at last index)

    return 0;
}

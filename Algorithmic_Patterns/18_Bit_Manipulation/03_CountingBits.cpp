/*
PROBLEM: Counting Bits
DESCRIPTION: Given an integer n, return an array ans of length n + 1 such that for each i
(0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
CONSTRAINTS:
- 0 <= n <= 10^5
EXAMPLE INPUT/OUTPUT:
Input: n = 2 -> Output: [0,1,1]
Input: n = 5 -> Output: [0,1,1,2,1,2]
*/

/*
APPROACH:
This is bit manipulation combined with dynamic programming. The key recurrence is:
bits[i] = bits[i >> 1] + (i & 1). Right-shifting i by 1 removes its last bit (equivalent to
i / 2), and (i & 1) tells us whether that removed last bit was a 1. So the popcount of i is
just the popcount of i with its last bit chopped off, plus that last bit. This builds the
whole answer array in O(n) time using previously computed results, instead of doing an O(log i)
Kernighan's-trick count for every single i (which would be O(n log n) overall).
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> ans(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            ans[i] = ans[i >> 1] + (i & 1);
        }
        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> res1 = sol.countBits(2);
    cout << "Input: n=2 -> Output: [";
    for (size_t i = 0; i < res1.size(); i++) cout << res1[i] << (i + 1 < res1.size() ? "," : "");
    cout << "] (Expected: [0,1,1])" << endl;

    vector<int> res2 = sol.countBits(5);
    cout << "Input: n=5 -> Output: [";
    for (size_t i = 0; i < res2.size(); i++) cout << res2[i] << (i + 1 < res2.size() ? "," : "");
    cout << "] (Expected: [0,1,1,2,1,2])" << endl;

    return 0;
}

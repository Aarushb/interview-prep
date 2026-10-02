/*
PROBLEM: Next Greater Element II
DESCRIPTION: Given a circular integer array nums (the next element of the last element is the
first element of the array), return the next greater number for every element in nums. The
next greater number of a number x is the first greater number to its traversing-order next in
the array, which means you could search circularly to find its next greater number. If it
doesn't exist, return -1 for this number.
CONSTRAINTS:
- 1 <= nums.length <= 10^4
- -10^9 <= nums[i] <= 10^9
EXAMPLE INPUT/OUTPUT:
Input: nums = [1,2,1] -> Output: [2,-1,2]
Input: nums = [1,2,3,4,3] -> Output: [2,3,4,-1,4]
*/

/*
APPROACH:
Same decreasing monotonic stack idea as the linear "Next Greater Element" problem, but to
handle circularity without physically duplicating the array, iterate index i from 0 to 2*n-1
and always look up the actual value at nums[i % n]. This lets each element "see" up to one
full extra lap around the array so it can find a next-greater that lies before it in the
array but after it circularly. We only write into the answer array during the first lap's
indices (i < n) since we just need each element's answer once; the stack still gets built and
popped using values from the second lap.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n, -1);
        stack<int> st; // stores indices (0..n-1), decreasing stack of values

        for (int i = 0; i < 2 * n; i++) {
            int val = nums[i % n];
            while (!st.empty() && nums[st.top()] < val) {
                ans[st.top()] = val;
                st.pop();
            }
            if (i < n) {
                st.push(i);
            }
        }
        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums1 = {1, 2, 1};
    vector<int> res1 = sol.nextGreaterElements(nums1);
    cout << "Input: [1,2,1] -> Output: [";
    for (size_t i = 0; i < res1.size(); i++) cout << res1[i] << (i + 1 < res1.size() ? "," : "");
    cout << "] (Expected: [2,-1,2])" << endl;

    vector<int> nums2 = {1, 2, 3, 4, 3};
    vector<int> res2 = sol.nextGreaterElements(nums2);
    cout << "Input: [1,2,3,4,3] -> Output: [";
    for (size_t i = 0; i < res2.size(); i++) cout << res2[i] << (i + 1 < res2.size() ? "," : "");
    cout << "] (Expected: [2,3,4,-1,4])" << endl;

    return 0;
}

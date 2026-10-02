/*
PROBLEM: Next Greater Element I
DESCRIPTION: You are given two distinct 0-indexed integer arrays nums1 and nums2, where nums1
is a subset of nums2. For each 0 <= i < nums1.length, find the index j such that
nums1[i] == nums2[j] and determine the next greater element of nums2[j] in nums2. The next
greater element of some element x in an array is the first greater element that is to the
right of x in the same array. If it does not exist, return -1 for this element. Return an
array ans of length nums1.length such that ans[i] is the next greater element as described.
CONSTRAINTS:
- 1 <= nums1.length <= nums2.length <= 1000
- 0 <= nums1[i], nums2[i] <= 10^4
- All integers in nums1 and nums2 are unique.
- All the integers of nums1 also appear in nums2.
EXAMPLE INPUT/OUTPUT:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2] -> Output: [-1,3,-1]
Input: nums1 = [2,4], nums2 = [1,2,3,4] -> Output: [3,-1]
*/

/*
APPROACH:
First compute the "next greater element" for every value in nums2 using a decreasing monotonic
stack: iterate nums2 left to right, and whenever the current value is greater than the value at
the top of the stack, that current value IS the next greater element for whatever's on the
stack — pop and record it in a hashmap. Anything left on the stack at the end has no next
greater element (map to -1 implicitly, or just skip and default to -1 in nums1). Then answer
nums1 via O(1) hashmap lookups. This turns an O(n*m) brute force into O(n + m).
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> nextGreater;
        stack<int> st; // decreasing stack of values

        for (int num : nums2) {
            while (!st.empty() && st.top() < num) {
                nextGreater[st.top()] = num;
                st.pop();
            }
            st.push(num);
        }

        vector<int> ans;
        ans.reserve(nums1.size());
        for (int num : nums1) {
            ans.push_back(nextGreater.count(num) ? nextGreater[num] : -1);
        }
        return ans;
    }
};

int main() {
    Solution sol;

    vector<int> nums1a = {4, 1, 2};
    vector<int> nums2a = {1, 3, 4, 2};
    vector<int> res1 = sol.nextGreaterElement(nums1a, nums2a);
    cout << "Input: nums1=[4,1,2], nums2=[1,3,4,2] -> Output: [";
    for (size_t i = 0; i < res1.size(); i++) cout << res1[i] << (i + 1 < res1.size() ? "," : "");
    cout << "] (Expected: [-1,3,-1])" << endl;

    vector<int> nums1b = {2, 4};
    vector<int> nums2b = {1, 2, 3, 4};
    vector<int> res2 = sol.nextGreaterElement(nums1b, nums2b);
    cout << "Input: nums1=[2,4], nums2=[1,2,3,4] -> Output: [";
    for (size_t i = 0; i < res2.size(); i++) cout << res2[i] << (i + 1 < res2.size() ? "," : "");
    cout << "] (Expected: [3,-1])" << endl;

    return 0;
}

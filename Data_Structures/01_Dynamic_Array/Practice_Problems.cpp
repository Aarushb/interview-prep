/*
PROBLEM: Remove Duplicates from Sorted Array (LeetCode 26)
DESCRIPTION: Given a sorted array nums, remove the duplicates in-place such that each unique
element appears only once. Return the number of unique elements k. The first k elements of nums
should hold the final result.
CONSTRAINTS: Array is sorted in non-decreasing order. Must be done in-place with O(1) extra space.
EXAMPLE INPUT/OUTPUT: [0,0,1,1,1,2,2,3,3,4] -> k=5, nums[0..4] = [0,1,2,3,4]
*/

/*
APPROACH:
Two-pointer technique. `slow` marks the boundary of the unique-elements-so-far region; `fast` scans
ahead. Whenever nums[fast] differs from nums[slow], it's a new unique value, so we advance slow and
copy it in. Since the array is sorted, all duplicates of a value are adjacent, so a single linear
pass suffices. This directly exercises dynamic-array-style in-place index manipulation.
*/

#include <bits/stdc++.h>
using namespace std;

int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int slow = 0;
    for (int fast = 1; fast < (int)nums.size(); fast++) {
        if (nums[fast] != nums[slow]) {
            slow++;
            nums[slow] = nums[fast];
        }
    }
    return slow + 1;
}

/*
PROBLEM: Merge Sorted Array (LeetCode 88)
DESCRIPTION: nums1 has length m+n, with the first m elements meaningful and the last n slots zeroed
placeholders. nums2 has length n. Merge nums2 into nums1 in-place so nums1 becomes one sorted array.
CONSTRAINTS: nums1 and nums2 are already sorted in non-decreasing order. Must merge in-place.
EXAMPLE INPUT/OUTPUT: nums1=[1,2,3,0,0,0], m=3, nums2=[2,5,6], n=3 -> nums1=[1,2,2,3,5,6]
*/

/*
APPROACH:
Merge from the back. If we merged from the front we'd overwrite not-yet-read elements of nums1.
Instead, use three pointers: i at the end of nums1's real data (m-1), j at the end of nums2 (n-1),
and k at the very end of the nums1 buffer (m+n-1). Repeatedly place the larger of nums1[i], nums2[j]
at position k and move pointers backward. This never overwrites data we still need to compare
because we always write to an index >= max(i, j) + 1.
*/

void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;
    while (j >= 0) {
        if (i >= 0 && nums1[i] > nums2[j]) {
            nums1[k--] = nums1[i--];
        } else {
            nums1[k--] = nums2[j--];
        }
    }
}

int main() {
    cout << "-- Remove Duplicates from Sorted Array --\n";
    vector<int> nums = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int k = removeDuplicates(nums);
    cout << "k = " << k << ", nums[0.." << k - 1 << "] = ";
    for (int i = 0; i < k; i++) cout << nums[i] << " ";
    cout << "\n\n";

    cout << "-- Merge Sorted Array --\n";
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2 = {2, 5, 6};
    merge(nums1, 3, nums2, 3);
    cout << "merged nums1 = ";
    for (int v : nums1) cout << v << " ";
    cout << "\n";

    return 0;
}

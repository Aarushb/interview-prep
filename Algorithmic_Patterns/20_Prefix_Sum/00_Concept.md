# Prefix Sum

## Pattern Overview
A prefix sum array stores the cumulative sum up to each index, letting any range sum be computed in O(1) as `prefix[j] - prefix[i-1]` after O(n) preprocessing. This trades one-time preprocessing for constant-time range queries and underlies subarray-sum-equals-target counting via hashmap-tracked prefix sums.

## When to Use It
- The problem asks for repeated range-sum queries (`sum(i, j)`) over a static (immutable)
  array — you want to avoid recomputing sums from scratch every time.
- You need to count or find subarrays whose sum equals (or is divisible by) a target value.
- The problem mentions "contiguous subarray" combined with a sum, balance, or count condition.
- You're asked for a running/cumulative total, or to compute values "except self" (products,
  sums) using information from both directions (prefix and suffix).
- Brute force would recompute a sum over a subrange in O(n) for every query, giving O(n * q)
  total — prefix sums bring per-query cost down to O(1) after O(n) preprocessing.
- The problem involves equal counts of two categories (e.g., 0s and 1s) in a subarray — this
  often becomes a prefix-sum-difference problem after remapping values (e.g., 0 → -1).

## Core Idea
A prefix sum array `prefix[i]` stores the cumulative sum of all elements from the start of the
array up to index `i`. Once built (in O(n)), the sum of any range `[i, j]` can be computed in
O(1) as `prefix[j] - prefix[i-1]` (with a sentinel `prefix[-1] = 0`, commonly implemented by
making the prefix array length n+1 and shifting indices by one). This trades O(n) one-time
preprocessing for O(1) per-query range sums, which is a massive win when there are many queries
on an unchanging array.

The second, and arguably more powerful, application of prefix sums is combined with a hashmap.
For "does a subarray with sum == k exist / how many are there" problems, the key insight is:
if `prefix[j] - prefix[i] = k`, then the subarray from `i+1` to `j` sums to k. Rearranging,
`prefix[i] = prefix[j] - k`. So as you scan the array computing a running prefix sum, you check
a hashmap for how many times `runningSum - k` has been seen before — each such occurrence marks
a valid subarray ending at the current index. You then record the current running sum in the
map (incrementing its count) before moving on. This turns an O(n²) nested-loop subarray search
into a single O(n) pass.

A third pattern is prefix/suffix product or sum arrays used together — e.g., "Product of Array
Except Self" builds a prefix-product array (product of everything to the left) and a
suffix-product array (product of everything to the right), then multiplies them elementwise,
avoiding division and handling zeros correctly. Finally, for divisibility problems (subarray
sums divisible by k), you use the *remainder* of the prefix sum modulo k as the hashmap key
instead of the raw sum — two prefix sums with the same remainder mean the subarray between them
is divisible by k. Care is needed with negative remainders in C++, where `%` can return a
negative result; normalize with `((rem % k) + k) % k`.

## Complexity
- Time: O(n) to build the prefix sum / prefix-sum-count map, then O(1) per range-sum query or
  O(n) total to answer a single subarray-count question.
- Space: O(n) for the prefix array or hashmap (O(1) extra if you only need a running sum without
  storing the full array, e.g., for prefix/suffix product tricks done in two passes reusing the
  output array).

## C++ Template
```cpp
// Static range-sum queries: build once, answer in O(1)
class NumArray {
public:
    NumArray(vector<int>& nums) {
        prefix.resize(nums.size() + 1, 0);
        for (int i = 0; i < (int)nums.size(); i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }

    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }

private:
    vector<int> prefix;
};

// Subarray-sum-equals-k template using running sum + hashmap of counts
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixCount;
    prefixCount[0] = 1; // empty prefix sums to 0
    int runningSum = 0, count = 0;

    for (int num : nums) {
        runningSum += num;
        if (prefixCount.count(runningSum - k)) {
            count += prefixCount[runningSum - k];
        }
        prefixCount[runningSum]++;
    }
    return count;
}
```

## Common Pitfalls
- Off-by-one errors between the prefix array (usually length n+1 with `prefix[0] = 0`) and the
  original array indices — always double-check `sumRange(i, j) = prefix[j+1] - prefix[i]`.
- Forgetting to seed the hashmap with `{0: 1}` in subarray-sum problems — this accounts for
  subarrays that start at index 0.
- Using raw sums as hashmap keys for divisibility problems instead of the sum modulo k — and
  forgetting to normalize negative remainders in C++ (`((x % k) + k) % k`).
- Integer overflow when array values are large and the array is long — use `long long` for the
  running/prefix sum when constraints allow large magnitudes.
- Confusing "prefix sum for range queries" (static array, no hashmap needed) with "prefix sum
  for subarray counting" (hashmap of running-sum frequencies needed) — they look similar but
  solve different question shapes.

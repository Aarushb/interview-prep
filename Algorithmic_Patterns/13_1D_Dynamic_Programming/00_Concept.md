# 1D Dynamic Programming

## Pattern Overview
1D DP solves problems with overlapping subproblems and optimal substructure by defining `dp[i]` in plain English and deriving a recurrence from the last decision made to reach state `i`. It can be implemented top-down (recursion + memo) or bottom-up (iterative table fill), and often space-optimizes down to O(1)/O(k) using rolling variables.

## When to Use It
- The problem asks for a count, minimum, maximum, or boolean feasibility that depends on some prefix/suffix of a 1D input (array, string, or an integer range like "ways to reach n").
- A brute-force recursive solution has overlapping subproblems — the same smaller instance gets recomputed many times (exponential time without memoization).
- The problem has optimal substructure: the answer for size `n` can be built from answers to smaller sizes (`n-1`, `n-2`, ... or some subset of earlier indices).
- Keywords like "number of ways," "minimum cost to reach," "longest/maximum," "can you partition/break," or "at each step you may choose..." appear.
- A greedy approach fails on a counterexample (you tried greedy and it broke) — DP is often the fallback when greedy doesn't hold.

## Core Idea
The first step is always **identifying the state**: define `dp[i]` in plain English before writing any code (e.g., "dp[i] = the minimum cost to reach step i" or "dp[i] = true if s[0..i) can be segmented into dictionary words"). Once the state is clear, the **transition** (recurrence) describes how to compute `dp[i]` from earlier states — this is usually derived by asking "what's the last decision made to arrive at state i?" (e.g., for Climbing Stairs, the last step was either a 1-step or 2-step hop, so `dp[i] = dp[i-1] + dp[i-2]`). Base cases anchor the recurrence at the smallest indices (`dp[0]`, `dp[1]`) where the answer is trivially known.

There are two equivalent ways to implement this: **top-down memoization**, where you write the natural recursive solution and cache results in a `map`/`vector` keyed by state so repeated calls return instantly, and **bottom-up tabulation**, where you build the `dp` array iteratively from the base cases upward, filling in each `dp[i]` before it's needed. Top-down is often easier to derive directly from the recursive brute force (add a memo, done), while bottom-up avoids recursion-stack overhead and is usually preferred in interviews once the recurrence is clear.

Many 1D DP problems only need the last 1, 2, or k previous states to compute the next one (e.g., House Robber only needs `dp[i-1]` and `dp[i-2]`). In these cases you can **space-optimize** from O(n) array to O(1) or O(k) using a handful of rolling variables instead of a full array — this is a common interview follow-up ("can you do it in O(1) space?") and shows mastery of the pattern.

Some 1D DP problems (like Longest Increasing Subsequence) have a naive O(n^2) transition but admit a smarter O(n log n) reformulation using binary search over an auxiliary "patience sorting" array — worth knowing as an optimization once the O(n^2) DP is established, since interviewers often ask for the follow-up.

## Complexity
- Time: typically O(n) for the standard state + O(1) transition (e.g., Climbing Stairs, House Robber); O(n * k) when the transition scans up to k prior states/choices (e.g., Coin Change over coin list, Word Break over word lengths); O(n log n) for the binary-search-optimized LIS.
- Space: O(n) for a full `dp` array (top-down memo or bottom-up table); reducible to O(1) or O(k) with rolling-variable space optimization when only the last few states are needed.

## C++ Template
```cpp
// Bottom-up tabulation skeleton
int solve(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0; // handle trivial/edge case explicitly

    vector<long long> dp(n + 1, 0); // dp[i] = answer considering first i elements
    dp[0] = /* base case */ 0;
    // dp[1] = ... if a second base case is needed

    for (int i = 1; i <= n; i++) {
        // transition: derive dp[i] from dp[i-1], dp[i-2], ... based on recurrence
        dp[i] = /* combine previous states, e.g. max(dp[i-1], dp[i-2] + nums[i-1]) */ 0;
    }

    return dp[n];
}

// Space-optimized rolling-variable version (when only last 2 states matter)
int solveOptimized(vector<int>& nums) {
    long long prev2 = 0, prev1 = 0; // dp[i-2], dp[i-1]
    for (int num : nums) {
        long long cur = max(prev1, prev2 + num); // example transition
        prev2 = prev1;
        prev1 = cur;
    }
    return (int)prev1;
}
```

## Common Pitfalls
- Off-by-one errors between `dp` indices and array indices (using `dp[n+1]` sized array vs `dp[n]` and forgetting to shift).
- Not handling small edge cases (`n == 0` or `n == 1`) before the main loop, causing out-of-bounds access on `dp[i-2]`.
- Forgetting to initialize unreachable states to infinity (for minimization problems like Coin Change) vs. zero (for counting problems), which silently corrupts the recurrence.
- Confusing "0/1 choice per item" (each element used once, loop order: item outer, capacity inner) with "unbounded/unlimited reuse" (loop order: capacity outer, item inner) — this matters for Coin Change and Word Break style problems.
- Reaching for O(n^2) brute-force DP when an O(n log n) reformulation (like patience sorting for LIS) is expected as a follow-up.

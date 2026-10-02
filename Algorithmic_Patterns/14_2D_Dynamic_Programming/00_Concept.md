# 2D Dynamic Programming

## Pattern Overview
2D DP generalizes 1D DP to a table `dp[i][j]`, typically indexed by prefixes of two sequences, grid coordinates, or a position plus an auxiliary state (holding stock, transactions used). The key work is deriving the recurrence relating `dp[i][j]` to smaller subproblems and filling the table in an order (row-by-row, usually) that respects those dependencies.

## When to Use It

- The problem asks you to compare or combine **two sequences** (two strings, two arrays) — e.g. longest common subsequence, edit distance, interleaving strings.
- The problem involves traversing a **grid** where the answer at a cell depends on neighboring cells (paths, min/max cost, obstacles).
- A single index isn't enough to describe "where you are" — you need a pair of indices, or an index plus an extra piece of state (a boolean flag, a count, a "holding stock" state, a remaining budget).
- You see phrases like "number of ways to...", "minimum cost/operations to transform...", "longest/shortest ... between two strings", or "match a pattern against a string".
- Brute force recursion on two pointers/indices has overlapping subproblems (the same `(i, j)` pair gets recomputed many times) — a strong signal to memoize into a 2D table.
- State machine problems (buy/sell stock variants, "can I be in state A or B on day i") often reduce to a 2D DP where one dimension is the day and the other is the discrete state.

## Core Idea

2D DP generalizes 1D DP by indexing the DP table with **two dimensions**, `dp[i][j]`. Usually `i` and `j` are prefixes of two sequences (`dp[i][j]` = answer using the first `i` characters of string A and the first `j` characters of string B), or `i` and `j` are coordinates on a grid (`dp[i][j]` = answer to reach cell `(i, j)`), or `i` is a position and `j` is an auxiliary state (holding stock, cooldown, number of transactions used, etc.).

The hardest part of 2D DP is writing the **recurrence**: express `dp[i][j]` in terms of strictly smaller subproblems, typically `dp[i-1][j]`, `dp[i][j-1]`, `dp[i-1][j-1]`, or a small number of neighboring states. For string-pair problems the recurrence almost always branches on whether `A[i-1] == B[j-1]`. For grid problems it branches on which directions you're allowed to move from. For state-machine problems it branches on which previous state legally transitions into the current one. Once the recurrence is right, the **filling order** matters: for prefix-based DP you fill row by row (or column by column) so that when you compute `dp[i][j]` every dependency has already been computed; for interval DP you'd fill by increasing length/diagonal instead (not needed for the problems in this folder, but worth knowing it exists).

Base cases live in row 0 and/or column 0 (empty prefix, or the starting cell of a grid) and must be initialized before the main loops run. Off-by-one errors are the single most common bug in 2D DP — a common trick is to make the DP table `(m+1) x (n+1)` so that `dp[i][j]` represents "using the first `i` elements" rather than "using elements up to index `i`", so index 0 cleanly represents "nothing used yet" without special-casing negative indices.

Once the recurrence only looks at the previous row (or previous column), you can **space-optimize** from `O(m*n)` down to `O(min(m,n))` by keeping only a rolling 1D array and overwriting it in place (being careful about the order of updates when a cell depends on a value in the *same* row that hasn't been overwritten yet, e.g. `dp[i][j-1]`).

## Complexity

- Time: `O(m * n)` where `m` and `n` are the two dimensions of the table (lengths of the two strings, or grid dimensions), since each of the `m*n` cells is computed once in `O(1)` (or `O(k)` if the recurrence looks at `k` previous states, as in regex matching's star handling).
- Space: `O(m * n)` for the full table, reducible to `O(min(m, n))` with rolling-array space optimization when the recurrence only depends on the previous row/column.

## C++ Template

```cpp
// Generic prefix-based 2D DP over two sequences A (length m) and B (length n).
// dp[i][j] = answer using A's first i chars and B's first j chars.
int solve(const string& A, const string& B) {
    int m = A.size(), n = B.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Base cases: dp[i][0] and dp[0][j] for empty-prefix scenarios.
    for (int i = 0; i <= m; i++) dp[i][0] = /* base value */ 0;
    for (int j = 0; j <= n; j++) dp[0][j] = /* base value */ 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (A[i - 1] == B[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // characters match
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // or min(...) + cost, depending on problem
            }
        }
    }
    return dp[m][n];
}
```

## Common Pitfalls

- Off-by-one indexing between the DP table (often sized `(m+1) x (n+1)`) and the raw string/array (0-indexed) — always double-check `A[i-1]` vs `A[i]`.
- Forgetting to initialize the base row/column before the main double loop, leaving garbage or wrong default values.
- Space-optimizing to a 1D rolling array before the recurrence is verified correct on the full 2D table — optimize last, not first.
- Mixing up the direction of the recurrence (min vs max, or which neighbor represents "skip" vs "take") when adapting the template to a new problem.
- For state-machine DP, not enumerating *all* legal transitions into a state (e.g. forgetting the cooldown day resets which states are reachable).

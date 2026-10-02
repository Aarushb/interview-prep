# Backtracking

## Pattern Overview
Backtracking is DFS over a decision tree driven by choose/explore/un-choose: pick a candidate, recurse deeper, then undo the choice before trying the next option. This lets you reuse a single mutable path/state across the whole search (O(depth) memory) and is the standard approach for generating all subsets, permutations, combinations, or valid paths, with pruning used to cut off invalid branches early.

## When to Use It
- The problem asks to generate **all** subsets, permutations, combinations, or partitions satisfying some condition.
- The phrase "return all possible ways to..." or "find all valid arrangements of..." appears.
- You need to search a decision tree where each step has multiple choices, and some paths are invalid or need to be abandoned early (pruned).
- The problem is on a grid or graph and asks whether a specific path/word/pattern exists, requiring you to explore, mark visited, and un-mark if the path fails (e.g., word search, N-Queens, Sudoku).
- Brute-force enumeration is required but the search space can be pruned significantly using constraints (sum limits, used-element tracking, remaining characters, etc).

## Core Idea
Backtracking is depth-first search over a decision tree, driven by a simple three-step loop at every node: **choose** a candidate, **explore** deeper by recursing, then **un-choose** (undo the candidate) before trying the next option. This "undo" step is what distinguishes backtracking from plain DFS — it lets you reuse a single mutable state (like a `vector<int> path` or a `visited` grid) across the whole search instead of copying it at every level, which keeps memory usage down to O(depth) instead of O(number of paths).

Every backtracking problem can be framed as building a path incrementally and deciding, at each recursive call, which subset of remaining choices are legal right now. The base case fires when the path is "complete" (reached target length, consumed the whole string, filled the whole board), at which point you record a copy of the current path into the results. Pruning — checking a constraint before recursing rather than after — is what makes backtracking fast in practice: e.g., in Combination Sum, skip a candidate the moment it would push the running sum over the target, cutting off entire subtrees instead of exploring them and failing later.

Three common shapes to recognize: (1) **subset-style** recursion that branches into "include this element" vs. "skip it," walking through indices once, used for subsets and combination sums; (2) **permutation-style** recursion that loops over all not-yet-used elements at every level, tracked via a `used[]` array or by swapping, used when order matters; (3) **grid/graph-style** recursion that explores neighbors from a starting cell, marking cells visited on entry and unmarking them on exit, used for word search and maze-style problems.

Backtracking's cost is inherently exponential (or factorial) because it explores a tree of choices, but well-placed pruning (sorting inputs first, breaking early when a candidate can't possibly work, skipping duplicate branches) can cut the *practical* runtime by orders of magnitude even though the worst-case bound stays the same.

## Complexity
- Time: Exponential in general — O(2^n) for subset-style problems, O(n!) for permutation-style problems, O(m·n·4^L) for grid search of a length-L word over an m×n grid. Pruning reduces the constant factor and average case, not the asymptotic worst case.
- Space: O(depth of recursion) for the call stack plus the current path, typically O(n) or O(L); result storage is additional and proportional to the number of valid outputs times their length.

## C++ Template
```cpp
#include <bits/stdc++.h>
using namespace std;

// Generic backtracking template: choose / explore / un-choose.
void backtrack(int start, vector<int>& path, vector<int>& candidates,
                vector<vector<int>>& result /*, other state like a target sum */) {
    // 1. Base case: record a completed path.
    if (/* path satisfies the completion condition, e.g. path.size() == n */ false) {
        result.push_back(path);
        return;
    }

    for (int i = start; i < (int)candidates.size(); ++i) {
        // 2. Prune: skip choices that can't possibly lead to a valid solution.
        if (/* candidates[i] violates a constraint */ false) continue;

        // 3. Choose.
        path.push_back(candidates[i]);

        // 4. Explore. Pass i (allow reuse), i+1 (no reuse, subset-style),
        //    or recurse over "unused" indices (permutation-style) depending on the problem.
        backtrack(i + 1, path, candidates, result);

        // 5. Un-choose (backtrack).
        path.pop_back();
    }
}
```

## Common Pitfalls
- Forgetting to pop/undo the last choice after recursing, which leaves stale state polluting sibling branches.
- Pushing a reference or forgetting to copy the path into results (`result.push_back(path)` copies correctly, but pushing a pointer/reference to a shared mutable vector does not).
- Using the wrong index policy: passing `i` instead of `i + 1` (or vice versa) confuses "allow reuse of the same element" (combination sum) with "each element used once" (subsets/combinations).
- Not pruning early — checking a constraint only at the base case instead of before recursing wastes enormous amounts of time exploring dead branches.
- Mishandling duplicates in the input (e.g., subsets/permutations with repeated values) by not sorting first and skipping adjacent duplicate choices at the same recursion depth, leading to duplicate results.

# Greedy

## Pattern Overview
A greedy algorithm builds a solution incrementally by making the locally best choice at each step, which only yields a global optimum when the problem has optimal substructure and the greedy-choice property (provable via an exchange argument). Common shapes include sort-then-scan (interval scheduling) and tracking a single running aggregate (Kadane's max-so-far, farthest-reachable-index).

## When to Use It

- The problem asks for an optimal value (max/min) and making the **locally best choice at each step** intuitively seems to lead to a globally best answer.
- Sorting the input first, then scanning once, seems to make the problem trivial — a classic greedy signal.
- You can articulate an **exchange argument**: given any optimal solution that differs from the greedy choice, you can swap/modify it to match the greedy choice without making it worse.
- The problem has an "interval" or "scheduling" flavor (meeting rooms, jump reachability, gas stations, merge intervals) where a single pass tracking a running best/farthest/remaining value suffices.
- You've tried DP and noticed the recurrence only ever depends on tracking one or two running quantities (max-so-far, farthest reachable index, running deficit) rather than needing to remember the full history of choices — that's a sign the DP collapses into a greedy.

## Core Idea

A greedy algorithm builds a solution incrementally, at each step making the choice that looks best *right now*, without reconsidering past choices. This only produces a correct global optimum when the problem has two properties: **optimal substructure** (an optimal solution to the whole problem contains optimal solutions to subproblems) and, critically, the **greedy-choice property** (a globally optimal solution can always be reached by making a locally optimal first choice). Proving the greedy-choice property is usually done with an **exchange argument**: assume an optimal solution `S` that does *not* make the greedy choice at some step; show you can modify `S` into `S'` that does make the greedy choice, where `S'` is at least as good as `S`. If this swap never hurts, the greedy choice is safe.

Common greedy patterns: sort by some key and scan once (interval scheduling, gas station's total-sum check), track a single running aggregate that represents "the best I could have done so far" (Kadane's running max-subarray-ending-here, jump game's farthest-reachable-index), or use a priority queue / multiset to always pick the current best candidate among several options (hand of straights' smallest-remaining-card).

The key contrast with DP: DP is needed when the locally best choice can be *wrong* in hindsight and you must consider multiple possibilities, tracking a table of subproblem answers so you can compare them later. Greedy is strictly cheaper (usually `O(n log n)` for a sort + scan, or `O(n)`) but is only valid when you can prove no backtracking is ever needed. A telltale sign greedy will *fail* is when a locally attractive choice can foreclose a better global option (e.g. 0/1 knapsack — greedily taking the highest value/weight item can beat out a combination that fits better; that needs DP, not greedy). When in doubt, try to construct a counterexample to the greedy strategy before committing to it in an interview — if you can't build one after a genuine attempt, you likely have a valid greedy.

## Complexity

- Time: typically `O(n log n)` when sorting is required first, or `O(n)` for a single linear scan when no sort is needed (e.g. Kadane's algorithm, jump game reachability).
- Space: `O(1)` extra space beyond the input for most greedy scans, or `O(n)` if an auxiliary structure (priority queue, hash map/multiset of counts) is needed to pick the next-best candidate efficiently.

## C++ Template

```cpp
// Generic greedy scan: sort by a key, then make one pass tracking a running
// "best so far" quantity, updating the answer as you go.
int solveGreedy(vector<int>& nums) {
    // 1. Sort if the greedy choice depends on relative order (skip if input
    //    order already defines the correct scan order, e.g. Kadane's).
    sort(nums.begin(), nums.end());

    int running = 0;      // running aggregate: farthest reach, current sum, deficit, etc.
    int best = INT_MIN;   // best answer found so far

    for (int i = 0; i < (int)nums.size(); i++) {
        // 2. Make the locally optimal choice using `running` and nums[i].
        running = max(running, nums[i]);      // or running += nums[i]; or running = max(nums[i], running + nums[i]);

        // 3. Update the global answer.
        best = max(best, running);

        // 4. Optionally reset `running` when the greedy choice invalidates
        //    carrying state forward (e.g. Kadane's resets when running < 0).
    }
    return best;
}
```

## Common Pitfalls

- Assuming a greedy strategy works without an exchange-argument-style justification — many near-greedy problems (0/1 knapsack, longest increasing subsequence with arbitrary constraints) actually require DP.
- Choosing the wrong sort key (e.g. sorting by start time vs end time vs a ratio) — the exchange argument only holds for the *correct* key.
- Forgetting to reset a running quantity at the right moment (Kadane's must reset the running sum to 0, not leave it negative, once it drops below zero).
- Off-by-one errors when a greedy scan tracks "farthest index reachable" vs "steps remaining" — these are easy to conflate in jump-game-style problems.
- Not handling ties or edge cases (empty input, single element, all-negative array) that break an otherwise-correct greedy loop.

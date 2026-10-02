# Monotonic Stack

## Pattern Overview
A monotonic stack maintains its elements (usually indices) in strictly increasing or decreasing order, popping violators as new elements arrive — each popped element thereby finds its "next greater/smaller" answer in amortized O(n) total work instead of an O(n^2) nested loop. It's the standard tool for next/previous greater-or-smaller queries and histogram-style maximum-area problems.

## When to Use It
- The problem asks for the "next greater," "next smaller," "previous greater," or "previous
  smaller" element for every element in an array.
- You need to find, for each element, the nearest element to its left/right that satisfies
  some ordering relationship.
- The problem involves a histogram, skyline, or "largest rectangle" shape and asks for a
  maximum area or maximum width.
- You're processing a stream of values and need running/spanning statistics relative to
  previous values (e.g., stock span problems).
- The problem wants you to remove characters/digits to form the smallest or largest possible
  result while preserving relative order (greedy stack removal).
- Brute force would be O(n²) (comparing every pair), and you suspect an O(n) or O(n log n)
  solution exists — monotonic stack is a common way to eliminate the nested loop.

## Core Idea
A monotonic stack is a stack that maintains its elements (or their indices) in strictly
increasing or strictly decreasing order at all times. As you iterate through the array, before
pushing a new element you pop off any elements from the top of the stack that violate the
monotonic property. Each popped element has just found its "answer" — the new element is its
next greater (or smaller) neighbor, because everything between them was smaller (or larger)
and got popped away already.

The reason this is efficient is amortized analysis: although there's a `while` loop popping
elements inside the main `for` loop, every element is pushed onto the stack exactly once and
popped at most once across the entire algorithm. So even though it doesn't look like a simple
single pass, the total work across all iterations is O(n), not O(n²).

Typically you store *indices* on the stack rather than values, because indices let you
recover both the value (via array lookup) and positional information (like distance, for
span-style problems, or left/right boundaries for area-style problems like Largest Rectangle
in Histogram). For "next greater" problems, use a decreasing stack (pop while the current
element is greater than the stack top). For "next smaller," use an increasing stack. Circular
array variants (e.g., Next Greater Element II) are handled by iterating `2 * n` times and
using `i % n` to wrap around, letting elements "see" all others in the circular array without
physically duplicating it.

## Complexity
- Time: O(n) amortized — each element is pushed and popped from the stack at most once, even
  though nested loops appear in the code.
- Space: O(n) for the stack in the worst case (e.g., a strictly increasing/decreasing input
  array where nothing gets popped until the end).

## C++ Template
```cpp
// Next Greater Element template (returns index of next greater element for each position,
// or -1 if none exists)
vector<int> nextGreaterElements(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st; // stores indices; values at these indices form a decreasing stack

    for (int i = 0; i < n; i++) {
        // pop indices whose values are smaller than current — current is their "next greater"
        while (!st.empty() && nums[st.top()] < nums[i]) {
            result[st.top()] = i; // or nums[i], depending on what you need to store
            st.pop();
        }
        st.push(i);
    }
    return result;
}
```

## Common Pitfalls
- Pushing values instead of indices when you actually need positional info (distance, left/right
  boundary) — this loses information you'll need later.
- Getting the stack direction backwards: an increasing stack finds "next smaller," a decreasing
  stack finds "next greater." Mixing these up silently produces wrong answers, not crashes.
- Forgetting to handle leftover elements still on the stack after the main loop — they simply
  have no valid answer (e.g., stays -1), but some problems (like circular arrays) require a
  second pass instead of leaving them unresolved.
- Off-by-one / wraparound bugs in circular-array variants — remember to use `i % n` for value
  lookups while iterating up to `2 * n`.
- Using `<=` instead of `<` (or vice versa) in the pop condition, which changes behavior when
  duplicate values are present — clarify whether the problem wants strictly greater/smaller.

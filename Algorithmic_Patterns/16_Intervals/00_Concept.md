# Intervals

## Pattern Overview
Interval problems almost always start by sorting the `[start, end]` pairs by start time, which turns an unordered set of ranges into a sequence you can sweep left to right comparing only adjacent/active intervals. From there, merging, counting overlaps, and finding peak concurrency (via a min-heap or a chronological +1/-1 sweep) all become single linear or O(n log n) passes.

## When to Use It
- The problem gives a list of `[start, end]` pairs (meetings, bookings, ranges, line segments).
- Keywords like "overlapping", "merge", "insert", "free time", "conflicting schedules", "minimum rooms/resources".
- You're asked whether a set of ranges can coexist without conflict, or how many resources are needed to support them simultaneously.
- You need to combine/consolidate a collection of ranges into the smallest equivalent set.
- The order of the input intervals is not guaranteed to be sorted.

## Core Idea
Almost every interval problem starts the same way: **sort the intervals**, usually by start time (sometimes by end time). Sorting turns an unordered set of ranges into a sequence you can sweep through left to right, comparing each interval only against the most recently processed one (or a small active set), instead of comparing every pair of intervals (which would be O(n^2)).

Once sorted by start time, "merge" and "overlap counting" problems reduce to a single linear pass: keep a "current" interval, and for each next interval check if `next.start <= current.end` (overlap). If it overlaps, extend/merge `current.end = max(current.end, next.end)`; if not, close out `current` and start a new one. This single pattern directly solves Merge Intervals, Insert Interval, and Non-overlapping Intervals (where instead of merging you count/remove the interval that ends latest to keep as many non-overlapping intervals as possible — a greedy interval scheduling argument).

For "how many resources/rooms are needed at once" problems (Meeting Rooms II), sorting by start time alone isn't enough — you need to track how many intervals are simultaneously active. Two classic techniques: (1) a **min-heap** keyed on end time, where you pop rooms that have freed up (`heap.top() <= current.start`) before pushing the new meeting's end time, and the heap's final size is the peak concurrent count; (2) the **chronological sweep** technique — split each interval into a `+1` event at `start` and a `-1` event at `end`, sort all events by time (ties broken so that a room freed by an ending meeting can be reused only after processing ends before starts, or using `end <= start` semantics), and track the running sum's maximum. Both run in O(n log n).

For boolean "can attend all meetings" (Meeting Rooms), you only need to check that after sorting by start time, no interval's start is before the previous interval's end — a single linear scan, no heap needed.

## Complexity
- Time: O(n log n) dominated by the initial sort; the sweep/merge pass itself is O(n) (or O(n log n) if using a heap, since each of n elements can be pushed/popped once).
- Space: O(n) for the output list, the heap, or the event array; O(log n) to O(n) for sort's internal stack/buffer depending on implementation.

## C++ Template
```cpp
#include <bits/stdc++.h>
using namespace std;

// Generic merge / sweep template — covers Merge Intervals, Insert Interval,
// Non-overlapping Intervals, and Meeting Rooms (I).
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    sort(intervals.begin(), intervals.end(),
         [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

    vector<vector<int>> result;
    result.push_back(intervals[0]);

    for (int i = 1; i < (int)intervals.size(); ++i) {
        vector<int>& last = result.back();
        vector<int>& cur = intervals[i];
        if (cur[0] <= last[1]) {          // overlap
            last[1] = max(last[1], cur[1]);
        } else {                          // no overlap, start new group
            result.push_back(cur);
        }
    }
    return result;
}

// Generic min-heap template for "how many resources needed at once" —
// covers Meeting Rooms II.
int minRoomsNeeded(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    sort(intervals.begin(), intervals.end(),
         [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

    priority_queue<int, vector<int>, greater<int>> endTimes; // min-heap of end times
    for (auto& iv : intervals) {
        if (!endTimes.empty() && endTimes.top() <= iv[0]) {
            endTimes.pop();                // reuse a freed room
        }
        endTimes.push(iv[1]);
    }
    return (int)endTimes.size();
}
```

## Common Pitfalls
- Forgetting to sort first (or sorting by the wrong key — start vs. end matters for different subproblems).
- Off-by-one confusion between "touching" intervals (`[1,2]` and `[2,3]`) — decide explicitly whether `end == next.start` counts as overlapping (usually it does NOT for scheduling problems but DOES for merging "closed" ranges depending on the exact problem statement).
- Mutating the input vector's elements by reference while also iterating over it in a way that invalidates iterators.
- For Non-overlapping Intervals, sorting by start time and merging is the wrong greedy — you must sort by **end time** and greedily keep the interval that finishes earliest to maximize the count of kept intervals.
- For Meeting Rooms II, using a max-heap or forgetting to pop already-freed rooms before pushing a new end time, which overcounts rooms.

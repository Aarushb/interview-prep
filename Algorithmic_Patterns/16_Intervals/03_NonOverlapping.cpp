/*
PROBLEM: Non-overlapping Intervals
DESCRIPTION: Given an array of intervals, return the minimum number of intervals you need
to remove to make the rest of the intervals non-overlapping.
CONSTRAINTS:
- 1 <= intervals.length <= 10^5
- intervals[i].length == 2
- -5*10^4 <= start_i < end_i <= 5*10^4
EXAMPLE INPUT/OUTPUT:
- Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
  Output: 1  (remove [1,3], the rest [[1,2],[2,3],[3,4]] is non-overlapping)
- Input: intervals = [[1,2],[1,2],[1,2]]
  Output: 2  (remove two of the three duplicate [1,2] intervals)
- Input: intervals = [[1,2],[2,3]]
  Output: 0  (already non-overlapping, touching endpoints don't count as overlap)
*/

/*
APPROACH:
This is the classic "activity selection" greedy problem in disguise. Sort intervals by
END time (not start time) — this lets us greedily keep the interval that frees up the
earliest, maximizing room for future intervals. Walk through the sorted list keeping track
of the end time of the last KEPT interval; if the next interval's start is >= that end
time, it doesn't overlap so we keep it and update the end time; otherwise it overlaps with
what we've kept, so we must remove it (increment a removal counter) and keep the previous
end time since it's already the smaller/earlier-ending option. The number of removals is
the answer. Sorting by end time (rather than start) is the key insight — it's what makes
the greedy choice provably optimal.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[1] < b[1]; });

        int removals = 0;
        int lastEnd = intervals[0][1];

        for (int i = 1; i < (int)intervals.size(); ++i) {
            if (intervals[i][0] < lastEnd) {
                // overlaps with the last kept interval -> must remove this one
                ++removals;
            } else {
                lastEnd = intervals[i][1];
            }
        }
        return removals;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> intervals1 = {{1,2},{2,3},{3,4},{1,3}};
    cout << "Input: [[1,2],[2,3],[3,4],[1,3]]" << endl;
    cout << "Output: " << sol.eraseOverlapIntervals(intervals1) << endl;
    cout << "Expected: 1" << endl << endl;

    vector<vector<int>> intervals2 = {{1,2},{1,2},{1,2}};
    cout << "Input: [[1,2],[1,2],[1,2]]" << endl;
    cout << "Output: " << sol.eraseOverlapIntervals(intervals2) << endl;
    cout << "Expected: 2" << endl << endl;

    vector<vector<int>> intervals3 = {{1,2},{2,3}};
    cout << "Input: [[1,2],[2,3]]" << endl;
    cout << "Output: " << sol.eraseOverlapIntervals(intervals3) << endl;
    cout << "Expected: 0" << endl;

    return 0;
}

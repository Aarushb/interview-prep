/*
PROBLEM: Merge Intervals
DESCRIPTION: Given an array of intervals where intervals[i] = [start_i, end_i], merge all
overlapping intervals, and return an array of the non-overlapping intervals that cover all
the intervals in the input.
CONSTRAINTS:
- 1 <= intervals.length <= 10^4
- intervals[i].length == 2
- 0 <= start_i <= end_i <= 10^4
EXAMPLE INPUT/OUTPUT:
- Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
  Output: [[1,6],[8,10],[15,18]]  (because [1,3] and [2,6] overlap, merge into [1,6])
- Input: intervals = [[1,4],[4,5]]
  Output: [[1,5]]  (touching intervals [1,4] and [4,5] are considered overlapping)
*/

/*
APPROACH:
Sort the intervals by start time so that any intervals that could overlap end up adjacent
in the sequence. Then do a single linear sweep, keeping a "current merged interval" — for
each next interval, if its start is <= the current interval's end, they overlap, so extend
the current interval's end to the max of the two ends; otherwise the current interval is
finalized and we start a new one. This greedy sweep is correct because after sorting by
start time, an interval can only possibly overlap with the immediately preceding merged
group (any later interval starts even later).
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return {};

        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

        vector<vector<int>> result;
        result.push_back(intervals[0]);

        for (int i = 1; i < (int)intervals.size(); ++i) {
            vector<int>& last = result.back();
            const vector<int>& cur = intervals[i];
            if (cur[0] <= last[1]) {
                last[1] = max(last[1], cur[1]);
            } else {
                result.push_back(cur);
            }
        }
        return result;
    }
};

static void printIntervals(const vector<vector<int>>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << "[" << v[i][0] << "," << v[i][1] << "]";
        if (i + 1 < v.size()) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;

    vector<vector<int>> intervals1 = {{1,3},{2,6},{8,10},{15,18}};
    cout << "Input: [[1,3],[2,6],[8,10],[15,18]]" << endl;
    cout << "Output: ";
    printIntervals(sol.merge(intervals1));
    cout << "Expected: [[1,6],[8,10],[15,18]]" << endl << endl;

    vector<vector<int>> intervals2 = {{1,4},{4,5}};
    cout << "Input: [[1,4],[4,5]]" << endl;
    cout << "Output: ";
    printIntervals(sol.merge(intervals2));
    cout << "Expected: [[1,5]]" << endl;

    return 0;
}

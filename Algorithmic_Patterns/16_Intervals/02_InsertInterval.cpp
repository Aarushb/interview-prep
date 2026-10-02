/*
PROBLEM: Insert Interval
DESCRIPTION: You are given an array of non-overlapping intervals sorted in ascending order
by start time, and a new interval. Insert the new interval into the array so that the array
is still sorted and non-overlapping (merging overlapping intervals as needed), and return
the resulting array.
CONSTRAINTS:
- 0 <= intervals.length <= 10^4
- intervals[i].length == 2
- 0 <= start_i <= end_i <= 10^5
- intervals is sorted by start_i in ascending order and non-overlapping
- newInterval.length == 2
- 0 <= newInterval[0] <= newInterval[1] <= 10^5
EXAMPLE INPUT/OUTPUT:
- Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
  Output: [[1,5],[6,9]]
- Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
  Output: [[1,2],[3,10],[12,16]]
*/

/*
APPROACH:
Since the input is already sorted and non-overlapping, we don't need to sort — we can do
a single linear pass in three phases: (1) copy all intervals that end strictly before the
new interval starts (they come entirely before, no overlap possible), (2) merge all
intervals that overlap the new interval by expanding newInterval's start/end to swallow
them, then push the fully-merged interval once, (3) copy all remaining intervals that start
strictly after the merged interval ends. This is O(n) with no sorting required.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        int i = 0, n = (int)intervals.size();

        // Phase 1: intervals ending before newInterval starts
        while (i < n && intervals[i][1] < newInterval[0]) {
            result.push_back(intervals[i]);
            ++i;
        }

        // Phase 2: merge all overlapping intervals into newInterval
        int start = newInterval[0], end = newInterval[1];
        while (i < n && intervals[i][0] <= end) {
            start = min(start, intervals[i][0]);
            end = max(end, intervals[i][1]);
            ++i;
        }
        result.push_back({start, end});

        // Phase 3: remaining intervals starting after the merged interval
        while (i < n) {
            result.push_back(intervals[i]);
            ++i;
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

    vector<vector<int>> intervals1 = {{1,3},{6,9}};
    vector<int> newInterval1 = {2,5};
    cout << "Input: intervals=[[1,3],[6,9]], newInterval=[2,5]" << endl;
    cout << "Output: ";
    printIntervals(sol.insert(intervals1, newInterval1));
    cout << "Expected: [[1,5],[6,9]]" << endl << endl;

    vector<vector<int>> intervals2 = {{1,2},{3,5},{6,7},{8,10},{12,16}};
    vector<int> newInterval2 = {4,8};
    cout << "Input: intervals=[[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval=[4,8]" << endl;
    cout << "Output: ";
    printIntervals(sol.insert(intervals2, newInterval2));
    cout << "Expected: [[1,2],[3,10],[12,16]]" << endl;

    return 0;
}

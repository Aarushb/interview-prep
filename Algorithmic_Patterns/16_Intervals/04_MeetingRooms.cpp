/*
PROBLEM: Meeting Rooms
DESCRIPTION: Given an array of meeting time intervals where intervals[i] = [start_i, end_i],
determine if a person could attend all meetings (i.e., no two meetings overlap).
CONSTRAINTS:
- 0 <= intervals.length <= 10^4
- intervals[i].length == 2
- 0 <= start_i < end_i <= 10^6
EXAMPLE INPUT/OUTPUT:
- Input: intervals = [[0,30],[5,10],[15,20]]
  Output: false  ([0,30] overlaps with both [5,10] and [15,20])
- Input: intervals = [[7,10],[2,4]]
  Output: true  (no overlap once sorted: [2,4] then [7,10])
*/

/*
APPROACH:
Sort the meetings by start time. Once sorted, a person can attend all meetings if and only
if no meeting starts before the previous meeting has ended — i.e., for every consecutive
pair after sorting, intervals[i].start >= intervals[i-1].end. A single linear scan after
sorting is enough; the moment we find a violation we can return false immediately. This is
the simplest member of the interval family and underlies the more complex Meeting Rooms II.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        if (intervals.size() < 2) return true;

        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

        for (int i = 1; i < (int)intervals.size(); ++i) {
            if (intervals[i][0] < intervals[i - 1][1]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    Solution sol;

    vector<vector<int>> intervals1 = {{0,30},{5,10},{15,20}};
    cout << "Input: [[0,30],[5,10],[15,20]]" << endl;
    cout << "Output: " << (sol.canAttendMeetings(intervals1) ? "true" : "false") << endl;
    cout << "Expected: false" << endl << endl;

    vector<vector<int>> intervals2 = {{7,10},{2,4}};
    cout << "Input: [[7,10],[2,4]]" << endl;
    cout << "Output: " << (sol.canAttendMeetings(intervals2) ? "true" : "false") << endl;
    cout << "Expected: true" << endl;

    return 0;
}

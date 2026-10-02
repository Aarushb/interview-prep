/*
PROBLEM: Meeting Rooms II
DESCRIPTION: Given an array of meeting time intervals intervals[i] = [start_i, end_i],
return the minimum number of conference rooms required to hold all the meetings.
CONSTRAINTS:
- 1 <= intervals.length <= 10^4
- intervals[i].length == 2
- 0 <= start_i < end_i <= 10^6
EXAMPLE INPUT/OUTPUT:
- Input: intervals = [[0,30],[5,10],[15,20]]
  Output: 2  (room 1 holds [0,30]; room 2 holds [5,10] then [15,20])
- Input: intervals = [[7,10],[2,4]]
  Output: 1  (no overlap, one room suffices)
*/

/*
APPROACH:
Sort meetings by start time, then use a min-heap keyed on end time to represent currently
"in use" rooms. For each meeting in start-time order, first check if the room with the
earliest end time (heap top) has already freed up by the time this meeting starts
(heap.top() <= current.start); if so, pop it — we reuse that room instead of allocating a
new one. Then push the current meeting's end time onto the heap regardless (either into the
freed slot conceptually, or as a brand-new room). The heap's size at the end (which equals
its peak size, since we only ever remove when reuse is possible) is the minimum number of
rooms needed. This directly generalizes Meeting Rooms I from a boolean check to a count.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;

        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

        priority_queue<int, vector<int>, greater<int>> endTimes; // min-heap of end times

        for (const auto& meeting : intervals) {
            if (!endTimes.empty() && endTimes.top() <= meeting[0]) {
                endTimes.pop(); // reuse the room that already freed up
            }
            endTimes.push(meeting[1]);
        }

        return (int)endTimes.size();
    }
};

int main() {
    Solution sol;

    vector<vector<int>> intervals1 = {{0,30},{5,10},{15,20}};
    cout << "Input: [[0,30],[5,10],[15,20]]" << endl;
    cout << "Output: " << sol.minMeetingRooms(intervals1) << endl;
    cout << "Expected: 2" << endl << endl;

    vector<vector<int>> intervals2 = {{7,10},{2,4}};
    cout << "Input: [[7,10],[2,4]]" << endl;
    cout << "Output: " << sol.minMeetingRooms(intervals2) << endl;
    cout << "Expected: 1" << endl;

    return 0;
}

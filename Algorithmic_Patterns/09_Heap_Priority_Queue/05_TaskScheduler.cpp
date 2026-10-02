/*
PROBLEM: Task Scheduler
DESCRIPTION: Given a characters array tasks, representing the tasks a CPU needs to do, where
each letter represents a different task, and a non-negative integer n that represents the
cooldown period between two same tasks (must have at least n intervals between two same tasks),
return the least number of units of time the CPU will take to finish all the given tasks.
CONSTRAINTS: 1 <= tasks.length <= 10^4; tasks[i] is an uppercase English letter; 0 <= n <= 100.
EXAMPLE INPUT/OUTPUT: tasks = [A,A,A,B,B,B], n = 2 -> 8; tasks = [A,A,A,B,B,B], n = 0 -> 6;
tasks = [A,A,A,A,B,C,D], n = 2 -> 10.
*/

/*
APPROACH:
Although this is grouped with heap problems (a max-heap by remaining frequency is the classic
simulation approach), the key insight is that the schedule length is bounded below by a closed-form
formula: the most frequent task must be spaced n apart from itself, so it anchors
(maxFreq - 1) * (n + 1) + countMax "slots" (countMax = how many tasks share that max frequency,
since they all need a slot in the final round). If the total number of tasks exceeds that many
slots, idle time isn't needed and the answer is simply tasks.size(); otherwise the formula itself
is the answer, since idle slots fill the gaps.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<int> freq(26,0);
        for(char c: tasks) freq[c-'A']++;
        int maxf = *max_element(freq.begin(), freq.end());
        int countMax = count(freq.begin(), freq.end(), maxf);
        long long part = (long long)(maxf-1)*(n+1) + countMax;
        return (int)max<long long>(tasks.size(), part);
    }
};

int main(){
    Solution sol;
    vector<char> t1 = {'A','A','A','B','B','B'};
    cout << sol.leastInterval(t1, 2) << "\n"; // 8
    vector<char> t2 = {'A','A','A','B','B','B'};
    cout << sol.leastInterval(t2, 0) << "\n"; // 6
    vector<char> t3 = {'A','A','A','A','B','C','D'};
    cout << sol.leastInterval(t3, 2) << "\n"; // 10
    return 0;
}

/*
PROBLEM: Hand of Straights
DESCRIPTION: Alice has some number of cards and she wants to rearrange the cards into groups so
that each group is of size groupSize, and consists of groupSize consecutive cards. Given an
integer array hand where hand[i] is the value written on the i-th card and an integer groupSize,
return true if she can rearrange the cards, or false otherwise.
CONSTRAINTS: 1 <= hand.length <= 10^4. 0 <= hand[i] <= 10^9. 1 <= groupSize <= hand.length.
EXAMPLE INPUT/OUTPUT:
  Input: hand = [1,2,3,6,2,3,4,7,8], groupSize = 3 -> Output: true (groups: [1,2,3],[2,3,4],[6,7,8])
  Input: hand = [1,2,3,4,5], groupSize = 4          -> Output: false
*/

/*
APPROACH:
Greedy with a frequency map: first, if hand.size() isn't divisible by groupSize, it's immediately
impossible. Otherwise, repeatedly take the smallest remaining card value and force it to be the
start of a new consecutive run of length groupSize, consuming one copy each of value, value+1, ...,
value+groupSize-1 from the frequency map. This is greedy-correct by an exchange argument: the
smallest remaining card *must* be the start of whatever group it ends up in, because no smaller
card is available to precede it in a consecutive run — so there's no better choice than starting
a group there immediately. We use an ordered map (sorted by key) to always access the current
smallest value efficiently, and erase entries whose count drops to zero so the "smallest key"
lookup stays correct.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if (groupSize == 1) return true;
        int n = hand.size();
        if (n % groupSize != 0) return false;

        map<int, int> count; // sorted by card value, so begin() is always the smallest remaining
        for (int card : hand) count[card]++;

        while (!count.empty()) {
            int start = count.begin()->first;
            for (int v = start; v < start + groupSize; v++) {
                auto it = count.find(v);
                if (it == count.end()) return false; // missing card to complete the run
                if (--(it->second) == 0) count.erase(it);
            }
        }
        return true;
    }
};

int main() {
    Solution sol;

    vector<int> h1 = {1, 2, 3, 6, 2, 3, 4, 7, 8};
    cout << boolalpha << sol.isNStraightHand(h1, 3) << endl; // expected true

    vector<int> h2 = {1, 2, 3, 4, 5};
    cout << boolalpha << sol.isNStraightHand(h2, 4) << endl; // expected false

    vector<int> h3 = {1, 2, 3, 4, 5, 6};
    cout << boolalpha << sol.isNStraightHand(h3, 2) << endl; // expected true

    return 0;
}

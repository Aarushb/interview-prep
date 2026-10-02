/*
PROBLEM: Remove K Digits
DESCRIPTION: Given string num representing a non-negative integer, and an integer k, return
the smallest possible integer after removing k digits from num. The result should not have
leading zeros (unless the result is "0" itself).
CONSTRAINTS:
- 1 <= k <= num.length <= 10^5
- num consists of only digits.
- num does not have any leading zeros except for the zero itself.
EXAMPLE INPUT/OUTPUT:
Input: num = "1432219", k = 3 -> Output: "1219"
Input: num = "10200", k = 1 -> Output: "200"
Input: num = "10", k = 2 -> Output: "0"
*/

/*
APPROACH:
Greedy with an increasing monotonic stack: to make the smallest number, whenever the current
digit is smaller than the digit at the top of the stack, popping that larger digit (as long as
we still have removals left, k > 0) strictly improves the result, since a smaller digit in a
more significant position always beats a larger one. Push digits onto the stack in order; if
removals remain after processing the whole string, remove them from the end (the largest
remaining suffix). Finally strip leading zeros and handle the empty-result edge case by
returning "0".
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string removeKdigits(string num, int k) {
        string st; // acts as the stack, built as a string for easy final assembly
        for (char digit : num) {
            while (!st.empty() && k > 0 && st.back() > digit) {
                st.pop_back();
                k--;
            }
            st.push_back(digit);
        }

        // if removals remain, they must come off the end (largest suffix)
        while (k > 0 && !st.empty()) {
            st.pop_back();
            k--;
        }

        // strip leading zeros
        int start = 0;
        while (start < static_cast<int>(st.size()) - 1 && st[start] == '0') {
            start++;
        }
        string result = st.substr(start);

        return result.empty() ? "0" : result;
    }
};

int main() {
    Solution sol;

    cout << "Input: num=\"1432219\", k=3 -> Output: \"" << sol.removeKdigits("1432219", 3)
         << "\" (Expected: \"1219\")" << endl;

    cout << "Input: num=\"10200\", k=1 -> Output: \"" << sol.removeKdigits("10200", 1)
         << "\" (Expected: \"200\")" << endl;

    cout << "Input: num=\"10\", k=2 -> Output: \"" << sol.removeKdigits("10", 2)
         << "\" (Expected: \"0\")" << endl;

    return 0;
}

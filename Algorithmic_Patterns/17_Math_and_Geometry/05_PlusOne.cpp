/*
PROBLEM: Plus One
DESCRIPTION: You are given a large integer represented as an array of digits, where each
digits[i] is the ith digit of the integer, ordered from most significant to least
significant (no leading zeros, except the number 0 itself). Increment the large integer by
one and return the resulting array of digits.
CONSTRAINTS:
- 1 <= digits.length <= 100
- 0 <= digits[i] <= 9
- digits does not contain any leading 0's, except the number 0 itself
EXAMPLE INPUT/OUTPUT:
- Input: digits = [1,2,3]
  Output: [1,2,4]
- Input: digits = [4,3,2,1]
  Output: [4,3,2,2]
- Input: digits = [9,9,9]
  Output: [1,0,0,0]
*/

/*
APPROACH:
Walk the digit array from least significant (rightmost) to most significant (leftmost),
simulating elementary-school addition of 1. If the current digit is less than 9, we can just
increment it and return immediately — no carry propagates further. If it's 9, it wraps to 0
and the carry continues to the next digit to the left. If we fall off the front of the array
still carrying (i.e., the original number was all 9's, like 999 -> 1000), we need one extra
leading digit: insert a 1 at the front, since after zeroing all the 9's a new most-significant
digit of 1 is required.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = (int)digits.size();

        for (int i = n - 1; i >= 0; --i) {
            if (digits[i] < 9) {
                digits[i]++;
                return digits;
            }
            digits[i] = 0;
        }

        // All digits were 9 and wrapped to 0; need a new leading 1
        digits.insert(digits.begin(), 1);
        return digits;
    }
};

static void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i + 1 < v.size()) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;

    vector<int> digits1 = {1,2,3};
    cout << "Input: [1,2,3]" << endl;
    cout << "Output: ";
    printVec(sol.plusOne(digits1));
    cout << "Expected: [1,2,4]" << endl << endl;

    vector<int> digits2 = {4,3,2,1};
    cout << "Input: [4,3,2,1]" << endl;
    cout << "Output: ";
    printVec(sol.plusOne(digits2));
    cout << "Expected: [4,3,2,2]" << endl << endl;

    vector<int> digits3 = {9,9,9};
    cout << "Input: [9,9,9]" << endl;
    cout << "Output: ";
    printVec(sol.plusOne(digits3));
    cout << "Expected: [1,0,0,0]" << endl;

    return 0;
}

/*
PROBLEM: Number of 1 Bits
DESCRIPTION: Write a function that takes the binary representation of an unsigned integer
and returns the number of '1' bits it has (also known as the Hamming weight).
CONSTRAINTS:
- The input must be a binary string of length 32.
EXAMPLE INPUT/OUTPUT:
Input: n = 00000000000000000000000000001011 -> Output: 3
Input: n = 00000000000000000000000010000000 -> Output: 1
Input: n = 11111111111111111111111111111101 -> Output: 31
*/

/*
APPROACH:
Use Brian Kernighan's trick: n & (n - 1) clears the lowest set bit of n in a single operation.
Repeating this until n becomes 0 counts exactly the number of set bits, running in O(k) where
k is the number of 1 bits (at most 32 iterations for a 32-bit integer) rather than looping over
all 32 bit positions unconditionally. Using uint32_t avoids sign-extension issues.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        while (n != 0) {
            n &= (n - 1); // clear the lowest set bit
            count++;
        }
        return count;
    }
};

int main() {
    Solution sol;

    cout << "Input: 0b1011 -> Output: " << sol.hammingWeight(0b1011) << " (Expected: 3)" << endl;
    cout << "Input: 0b10000000 -> Output: " << sol.hammingWeight(0b10000000) << " (Expected: 1)" << endl;

    uint32_t n3 = 4294967293u; // 11111111111111111111111111111101
    cout << "Input: 11111111111111111111111111111101 -> Output: " << sol.hammingWeight(n3)
         << " (Expected: 31)" << endl;

    return 0;
}

/*
PROBLEM: Reverse Bits
DESCRIPTION: Reverse the bits of a given 32-bit unsigned integer.
CONSTRAINTS:
- The input must be a binary string of length 32.
EXAMPLE INPUT/OUTPUT:
Input: n = 00000010100101000001111010011100 -> Output: 964176192 (00111001011110000010100101000000)
Input: n = 11111111111111111111111111111101 -> Output: 3221225471 (10111111111111111111111111111111)
*/

/*
APPROACH:
Process the input bit by bit from position 0 (least significant) to position 31 (most
significant). For each bit i in n, extract it with (n >> i) & 1, then place it into the
mirrored position (31 - i) of the result using a left shift and OR. This runs in a fixed
32 iterations, O(1) time and space. Using uint32_t throughout avoids sign-extension issues
that would occur with signed shifts.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t result = 0;
        for (int i = 0; i < 32; i++) {
            uint32_t bit = (n >> i) & 1u;
            result |= (bit << (31 - i));
        }
        return result;
    }
};

int main() {
    Solution sol;

    uint32_t n1 = 0b00000010100101000001111010011100u;
    cout << "Input: 00000010100101000001111010011100 -> Output: " << sol.reverseBits(n1)
         << " (Expected: 964176192)" << endl;

    uint32_t n2 = 4294967293u; // 11111111111111111111111111111101
    cout << "Input: 11111111111111111111111111111101 -> Output: " << sol.reverseBits(n2)
         << " (Expected: 3221225471)" << endl;

    return 0;
}

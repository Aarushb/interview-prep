# Bit Manipulation

## Pattern Overview
Bit manipulation exploits the binary representation of integers to solve problems in O(1) extra space using XOR's self-cancellation property, bit masks, and tricks like `n & (n-1)` to clear the lowest set bit. It's the go-to pattern whenever a problem hints at O(1) space, single/missing numbers among duplicates, or direct bit-level operations.

## When to Use It
- The problem talks about numbers appearing an odd/even number of times, and everything else appears in pairs.
- You're asked to count set bits, find the number of 1 bits, or work with binary representations directly.
- Constraints mention values fit in 32-bit or 64-bit integers, and O(1) extra space is required or strongly hinted.
- The problem involves finding a single missing/duplicate number in a range `[0, n]` without extra memory.
- You see phrases like "without using extra space," "in O(1) space," or "using bitwise operators."
- Subsets/combinations of a set need to be enumerated (bitmask represents inclusion/exclusion).
- You need to toggle, set, clear, or check a specific bit efficiently.

## Core Idea
Bit manipulation problems exploit the low-level binary representation of integers to solve problems in less time or space than array/hashmap-based approaches. The single most useful trick is XOR's self-cancellation property: `a ^ a = 0` and `a ^ 0 = a`. Since XOR is commutative and associative, XOR-ing a whole list of numbers cancels out every value that appears an even number of times, leaving only the value(s) that appear an odd number of times. This underlies "Single Number" and "Missing Number" style problems.

Beyond XOR, the toolkit includes: bit masks (`1 << i` isolates bit `i`), the AND operation for checking/clearing bits (`n & (n-1)` clears the lowest set bit — this is Brian Kernighan's trick, and it's the fastest way to count set bits or check if a number is a power of two), shifting (`>>` and `<<`) to move bits and build/read binary representations, and OR/AND combined with masks to set or clear specific bits. For "reverse bits" style problems, you process one bit at a time from the input and build the result by shifting it into the correct position of the output.

Many bit-DP problems (like Counting Bits) combine a simple recurrence with a bit trick: `bits[i] = bits[i >> 1] + (i & 1)`, which says "the bit count of i equals the bit count of i with its last bit removed, plus that last bit." This turns an O(n log n) brute-force popcount loop into O(n) overall.

A key interview habit: always clarify signed vs unsigned behavior, especially for right shifts (`>>` is arithmetic/sign-extending on signed ints in C++, so use `unsigned` types when you need a logical shift) and for languages other than C++ that don't have true fixed-width unsigned types.

## Complexity
- Time: Typically O(n) or O(n log(max_value)) — one pass over the input, with an O(log(max_value)) inner loop for bit-by-bit processing (e.g., 32 iterations for a 32-bit integer).
- Space: O(1) extra space beyond the output — this is usually the entire point of using bit tricks instead of a hashmap/array.

## C++ Template
```cpp
// XOR-cancellation template (find the unique element)
int findUnique(vector<int>& nums) {
    int result = 0;
    for (int num : nums) {
        result ^= num;
    }
    return result;
}

// Bit-by-bit processing template (count set bits / reverse bits)
int processBits(uint32_t n) {
    int result = 0;
    for (int i = 0; i < 32; i++) {
        int bit = (n >> i) & 1;   // extract bit i
        // do something with `bit`, e.g. accumulate into result
        result |= (bit << (31 - i)); // example: place it in reversed position
    }
    return result;
}

// Brian Kernighan's trick: clear the lowest set bit, O(number of set bits)
int countSetBits(int n) {
    int count = 0;
    while (n != 0) {
        n &= (n - 1); // drops the lowest set bit
        count++;
    }
    return count;
}
```

## Common Pitfalls
- Forgetting that `>>` on a *signed* negative integer in C++ is an arithmetic shift (sign-extends), which corrupts bit-counting logic — cast to `unsigned`/`uint32_t` first.
- Off-by-one errors when looping over 32 bits (`i < 32` vs `i <= 32`) or when reversing bit order (`31 - i` vs `32 - i`).
- Using `1 << 31` on a signed 32-bit `int` causes undefined behavior in C++; prefer `1u << 31` or `unsigned`/`long long` types.
- Assuming XOR-of-all-elements works when more than one element is unpaired (it only isolates a single unique value cleanly, or two if you additionally partition by a differing bit — see LeetCode 260 variants).
- Forgetting that integer overflow can occur with left shifts near the top bit; use `long long` when in doubt.

/*
PROBLEM: Generate Parentheses
DESCRIPTION: Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
CONSTRAINTS:
- 1 <= n <= 8
EXAMPLE INPUT/OUTPUT:
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Input: n = 1
Output: ["()"]
*/

/*
APPROACH:
Although this is solved with backtracking rather than an explicit stack object, the reasoning is the same
stack-based validity check used for bracket matching: at any point in a valid sequence, the number of
close-parens placed so far can never exceed the number of open-parens, which is exactly what a stack of
opens would tell you. So I build the string recursively, tracking an open-count and close-count; I'm
allowed to add '(' whenever open is still less than n, and allowed to add ')' whenever close is less than
open (guaranteeing we never close more than we've opened). When the string reaches length 2n it's a
complete, valid combination, so I add it to the results and backtrack. This prunes invalid states early
instead of generating everything and filtering.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

BACKTRACKING + STACK validation (though we can track without explicit stack).

KEY INSIGHT:
Build parentheses string character by character using backtracking.
Rules:
1. Can add '(' if we haven't used all n open parentheses
2. Can add ')' if it won't make string invalid (more ')' than '(')

ALGORITHM:
1. Use backtracking to build strings
2. Track: open count, close count
3. Base case: both counts == n → add to result
4. Recursive cases:
   - If open < n: try adding '('
   - If close < open: try adding ')' (ensures validity)

TIME: O(4^n / √n) - Catalan number
SPACE: O(n) for recursion stack

WHY close < open?
At any point, number of ')' should not exceed number of '('.
This ensures we never create invalid intermediate states.

ALTERNATIVE: Use explicit stack validation, but tracking counts is cleaner.

TRICK:
We don't need to validate the entire string at each step.
Just ensure: openCount >= closeCount at all times.
*/

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string current;
        backtrack(result, current, 0, 0, n);
        return result;
    }
    
private:
    void backtrack(vector<string>& result, string& current, 
                   int open, int close, int n) {
        // Base case: used all parentheses
        if (current.length() == 2 * n) {
            result.push_back(current);
            return;
        }
        
        // Try adding '(' if we haven't used all
        if (open < n) {
            current.push_back('(');
            backtrack(result, current, open + 1, close, n);
            current.pop_back();  // Backtrack
        }
        
        // Try adding ')' if it's valid
        if (close < open) {
            current.push_back(')');
            backtrack(result, current, open, close + 1, n);
            current.pop_back();  // Backtrack
        }
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<string> result1 = sol.generateParenthesis(3);
    cout << "Test 1 (n=3): ";
    for (const string& s : result1) {
        cout << s << " ";
    }
    cout << endl;
    // Expected: ((())), (()()), (())(), ()(()), ()()()
    
    // Test Case 2
    vector<string> result2 = sol.generateParenthesis(1);
    cout << "Test 2 (n=1): ";
    for (const string& s : result2) {
        cout << s << " ";
    }
    cout << endl;
    // Expected: ()
    
    // Test Case 3
    vector<string> result3 = sol.generateParenthesis(2);
    cout << "Test 3 (n=2): ";
    for (const string& s : result3) {
        cout << s << " ";
    }
    cout << endl;
    // Expected: (()), ()()
    
    return 0;
}

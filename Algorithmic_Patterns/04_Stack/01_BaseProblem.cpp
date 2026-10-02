/*
PROBLEM: Valid Parentheses
DESCRIPTION: Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
An input string is valid if:
1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.
3. Every close bracket has a corresponding open bracket of the same type.
CONSTRAINTS:
- 1 <= s.length <= 10^4
- s consists of parentheses only '()[]{}'.
EXAMPLE INPUT/OUTPUT:
Input: s = "()"
Output: true

Input: s = "()[]{}"
Output: true

Input: s = "(]"
Output: false
*/

/*
APPROACH:
Bracket matching is the textbook stack use case because closing brackets must resolve the most recently
opened bracket first — that's exactly last-in-first-out order. I walk the string once: whenever I see an
opening bracket I push it onto the stack, and whenever I see a closing bracket I check that the stack
isn't empty and that its top matches the corresponding opening bracket, popping it if so, or returning
false immediately if not. After processing the whole string, the stack must be empty, otherwise there are
unmatched opens left over. A hash map from closing to opening bracket keeps the matching check O(1), so
the whole thing runs in O(n) time and O(n) space.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

Classic STACK problem for matching pairs.

KEY INSIGHT:
- When we see opening bracket: push it
- When we see closing bracket: check if it matches top of stack
- If stack is empty or doesn't match: invalid
- After processing all characters, stack should be empty

ALGORITHM:
1. Use stack to store opening brackets
2. For each character:
   - If opening bracket '(', '[', '{': push to stack
   - If closing bracket ')', ']', '}':
     * Check if stack is empty → invalid
     * Check if top matches → valid, pop
     * If doesn't match → invalid
3. After loop, check if stack is empty

TIME: O(n), SPACE: O(n)

TRICKS:
1. Use hash map to store matching pairs
2. Only push opening brackets to stack
3. Check stack.empty() before accessing top()
*/

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        unordered_map<char, char> matching = {
            {')', '('}, {']', '['}, {'}', '{'}
        };
        
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                // Opening bracket
                st.push(c);
            } else {
                // Closing bracket
                if (st.empty() || st.top() != matching[c]) {
                    return false;
                }
                st.pop();
            }
        }
        
        return st.empty();
    }
};

int main() {
    Solution sol;
    
    cout << "Test 1: " << (sol.isValid("()") ? "true" : "false") << endl;
    // Expected: true
    
    cout << "Test 2: " << (sol.isValid("()[]{}") ? "true" : "false") << endl;
    // Expected: true
    
    cout << "Test 3: " << (sol.isValid("(]") ? "true" : "false") << endl;
    // Expected: false
    
    cout << "Test 4: " << (sol.isValid("([)]") ? "true" : "false") << endl;
    // Expected: false
    
    cout << "Test 5: " << (sol.isValid("{[]}") ? "true" : "false") << endl;
    // Expected: true
    
    cout << "Test 6: " << (sol.isValid("]") ? "true" : "false") << endl;
    // Expected: false
    
    return 0;
}

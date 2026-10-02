/*
PROBLEM: Evaluate Reverse Polish Notation
DESCRIPTION: Evaluate the value of an arithmetic expression in Reverse Polish Notation.
Valid operators are +, -, *, and /. Each operand may be an integer or another expression.
Note that division between two integers should truncate toward zero.
CONSTRAINTS:
- 1 <= tokens.length <= 10^4
- tokens[i] is either an operator: "+", "-", "*", or "/", or an integer in the range [-200, 200].
EXAMPLE INPUT/OUTPUT:
Input: tokens = ["2","1","+","3","*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9

Input: tokens = ["4","13","5","/","+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6
*/

/*
APPROACH:
Reverse Polish Notation is designed to be evaluated with a stack: operands appear before the operator that
uses them, so no parentheses or precedence rules are needed. I scan the tokens left to right — whenever I
see a number I push it, and whenever I see an operator I pop the two most recent operands off the stack,
apply the operator, and push the result back. The one subtlety worth saying out loud is operand order:
since the second operand was pushed last, I pop b first then a, and compute a op b, not b op a, which
matters for subtraction and division. After processing every token, the single value left on the stack is
the answer. Time and space are both O(n).
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

Classic STACK problem for expression evaluation.

RPN (Reverse Polish Notation) / Postfix:
- Operands come before operators
- No need for parentheses
- Easy to evaluate with stack

ALGORITHM:
1. For each token:
   - If it's a number: push to stack
   - If it's an operator:
     * Pop two operands (b then a)
     * Apply operation: a op b
     * Push result back
2. Final stack top is the result

TIME: O(n), SPACE: O(n)

IMPORTANT:
Order matters when popping!
b = pop(), a = pop()
Result = a op b (NOT b op a)

TRICK:
For division, use integer division that truncates toward zero.
In C++, / operator does this by default for positive results,
but for negative results we may need special handling.
*/

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        
        for (const string& token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                // Pop two operands (order matters!)
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                
                int result;
                if (token == "+") result = a + b;
                else if (token == "-") result = a - b;
                else if (token == "*") result = a * b;
                else result = a / b;  // Integer division
                
                st.push(result);
            } else {
                // It's a number
                st.push(stoi(token));
            }
        }
        
        return st.top();
    }
    
    // Helper function approach
    bool isOperator(const string& s) {
        return s == "+" || s == "-" || s == "*" || s == "/";
    }
    
    int applyOp(int a, int b, const string& op) {
        if (op == "+") return a + b;
        if (op == "-") return a - b;
        if (op == "*") return a * b;
        return a / b;
    }
    
    int evalRPNClean(vector<string>& tokens) {
        stack<int> st;
        
        for (const string& token : tokens) {
            if (isOperator(token)) {
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                st.push(applyOp(a, b, token));
            } else {
                st.push(stoi(token));
            }
        }
        
        return st.top();
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    vector<string> tokens1 = {"2", "1", "+", "3", "*"};
    cout << "Test 1: " << sol.evalRPN(tokens1) << endl;
    // Expected: 9
    
    // Test Case 2
    vector<string> tokens2 = {"4", "13", "5", "/", "+"};
    cout << "Test 2: " << sol.evalRPN(tokens2) << endl;
    // Expected: 6
    
    // Test Case 3
    vector<string> tokens3 = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    cout << "Test 3: " << sol.evalRPN(tokens3) << endl;
    // Expected: 22
    
    // Test Case 4 - Single number
    vector<string> tokens4 = {"42"};
    cout << "Test 4: " << sol.evalRPN(tokens4) << endl;
    // Expected: 42
    
    return 0;
}

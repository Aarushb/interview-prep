/*
PROBLEM: Min Stack
DESCRIPTION: Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
Implement the MinStack class:
- MinStack() initializes the stack object.
- void push(int val) pushes the element val onto the stack.
- void pop() removes the element on the top of the stack.
- int top() gets the top element of the stack.
- int getMin() retrieves the minimum element in the stack.
You must implement a solution with O(1) time complexity for each function.
CONSTRAINTS:
- -2^31 <= val <= 2^31 - 1
- Methods pop, top and getMin will always be called on non-empty stacks.
- At most 3 * 10^4 calls will be made to push, pop, top, and getMin.
EXAMPLE INPUT/OUTPUT:
Input: ["MinStack","push","push","push","getMin","pop","top","getMin"]
       [[],[-2],[0],[-3],[],[],[],[]]
Output: [null,null,null,null,-3,null,0,-2]
*/

/*
APPROACH:
The constraint that forces this into a stack-based design is needing O(1) getMin alongside O(1) push/pop
— scanning for the minimum on demand would be O(n). The insight is to maintain a second "min stack" in
parallel with the main stack: every time I push a value, I also push it onto the min stack if it's less
than or equal to the current minimum, so the min stack's top is always the minimum of everything currently
in the main stack. On pop, if the popped value equals the min stack's top, I pop the min stack too, which
correctly restores the previous minimum. This keeps every operation O(1) time at the cost of O(n) extra
space.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

Design problem requiring O(1) for ALL operations including getMin().

NAIVE APPROACH:
- Use single stack, scan for minimum each time: O(n) for getMin

OPTIMAL APPROACH 1: Two Stacks
- One stack for values
- One stack for minimums (parallel)
- When push: also push current min to minStack
- When pop: pop from both stacks
- getMin: return top of minStack
- TIME: O(1) all operations, SPACE: O(2n) = O(n)

OPTIMAL APPROACH 2: Single Stack with Pairs
- Store pairs (value, currentMin) in stack
- SPACE: O(2n) = O(n)

OPTIMAL APPROACH 3: Single Stack with Min Tracking (Space-optimized)
- Only push to minStack when new minimum found
- SPACE: O(n) worst case, better in practice

TRICK:
The minimum at any point is determined by all elements currently in stack.
When we pop, if we pop the minimum, the previous minimum becomes current.
We can track this with a separate minStack.
*/

class MinStack {
private:
    stack<int> st;
    stack<int> minSt;  // Stores minimums
    
public:
    MinStack() {
        // Constructor
    }
    
    void push(int val) {
        st.push(val);
        
        // Push to minStack if it's new minimum or equal to current min
        if (minSt.empty() || val <= minSt.top()) {
            minSt.push(val);
        }
    }
    
    void pop() {
        if (st.empty()) return;
        
        // If popping the minimum, also pop from minStack
        if (st.top() == minSt.top()) {
            minSt.pop();
        }
        
        st.pop();
    }
    
    int top() {
        return st.top();
    }
    
    int getMin() {
        return minSt.top();
    }
};

// Alternative: Using pairs
class MinStackPair {
private:
    stack<pair<int, int>> st;  // {value, currentMin}
    
public:
    void push(int val) {
        if (st.empty()) {
            st.push({val, val});
        } else {
            int currentMin = min(val, st.top().second);
            st.push({val, currentMin});
        }
    }
    
    void pop() {
        st.pop();
    }
    
    int top() {
        return st.top().first;
    }
    
    int getMin() {
        return st.top().second;
    }
};

int main() {
    MinStack minStack;
    
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    
    cout << "Min: " << minStack.getMin() << endl;  // -3
    
    minStack.pop();
    
    cout << "Top: " << minStack.top() << endl;  // 0
    cout << "Min: " << minStack.getMin() << endl;  // -2
    
    return 0;
}

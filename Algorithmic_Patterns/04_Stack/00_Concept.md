# Stack

## Pattern Overview
Stack is a Last-In-First-Out (LIFO) data structure used for problems involving nested structures, reversing, matching pairs, and maintaining order with quick access to most recent elements.

## When to Use This Pattern

### Problem Statement Signals:
- "Valid parentheses/brackets"
- "Next greater/smaller element"
- "Evaluate expression"
- "Remove adjacent duplicates"
- "Reverse Polish Notation"
- "Min/max stack"
- "Undo operations"
- Need to **backtrack** or **remember previous state**
- Process elements in **reverse order** of arrival

### Key Indicators:
1. **Matching pairs**: Parentheses, brackets, tags
2. **Nesting depth**: Track nested structures
3. **Most recent element access**: Need last added element frequently
4. **Reverse order processing**: LIFO behavior needed
5. **Cancel/undo operations**: Remove most recent additions

## Complexity Analysis

### Time Complexity:
- Push: **O(1)**
- Pop: **O(1)**
- Top/Peek: **O(1)**
- Most stack problems: **O(n)** single pass

### Space Complexity:
- Usually **O(n)** for stack storage
- Can be **O(1)** for in-place modifications

## Generic Templates

```cpp
#include <bits/stdc++.h>
using namespace std;

// TEMPLATE 1: Basic Stack Operations
void basicStackPattern() {
    stack<int> st;
    
    // Push elements
    st.push(1);
    st.push(2);
    
    // Access top
    if (!st.empty()) {
        int top = st.top();
    }
    
    // Pop element
    if (!st.empty()) {
        st.pop();
    }
    
    // Check if empty
    bool isEmpty = st.empty();
    
    // Get size
    int size = st.size();
}

// TEMPLATE 2: Matching Pairs Pattern
bool matchingPairsPattern(string s) {
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

// TEMPLATE 3: Monotonic Stack (Next Greater Element)
vector<int> nextGreaterPattern(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> st;  // Store indices
    
    for (int i = 0; i < n; i++) {
        // Pop smaller elements and update their next greater
        while (!st.empty() && nums[i] > nums[st.top()]) {
            result[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    
    return result;
}

// TEMPLATE 4: Expression Evaluation
int evaluatePostfix(vector<string>& tokens) {
    stack<int> st;
    
    for (string& token : tokens) {
        if (isOperator(token)) {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            st.push(applyOperation(a, b, token));
        } else {
            st.push(stoi(token));
        }
    }
    
    return st.top();
}
```

## Common Patterns & Variations

### 1. Matching/Validation
- Valid parentheses
- Remove invalid parentheses
- Tag validator
- **Strategy**: Push opening symbols, pop on closing

### 2. Monotonic Stack
- Next greater/smaller element
- Stock span problem
- **Strategy**: Maintain stack in increasing/decreasing order

### 3. Expression Evaluation
- Calculator problems
- Postfix evaluation
- Infix to postfix
- **Strategy**: Stack for operators and operands

### 4. String Manipulation
- Remove duplicates
- Decode string
- **Strategy**: Build result using stack

### 5. Min/Max Stack
- Track minimum/maximum efficiently
- **Strategy**: Maintain auxiliary stack

## Key Tricks & Tips

### 1. Monotonic Stack
```cpp
// Decreasing stack (values decrease bottom-to-top; for next greater element)
while (!st.empty() && nums[i] > nums[st.top()]) {
    // Found next greater for st.top()
    st.pop();
}
st.push(i);

// Increasing stack (values increase bottom-to-top; for next smaller element)
while (!st.empty() && nums[i] < nums[st.top()]) {
    st.pop();
}
```

### 2. String Building with Stack
```cpp
stack<char> st;
for (char c : s) {
    if (!st.empty() && shouldRemove(st.top(), c)) {
        st.pop();
    } else {
        st.push(c);
    }
}

// Convert stack to string
string result;
while (!st.empty()) {
    result = st.top() + result;  // Prepend (LIFO reversal)
    st.pop();
}
```

### 3. Track Min/Max
```cpp
class MinStack {
    stack<int> st;
    stack<int> minStack;  // Stores minimums
    
    void push(int val) {
        st.push(val);
        if (minStack.empty() || val <= minStack.top()) {
            minStack.push(val);
        }
    }
    
    int getMin() {
        return minStack.top();
    }
};
```

## Common Mistakes to Avoid

1. **Not checking if stack is empty before pop/top**
2. **Forgetting to pop after processing**
3. **Wrong order when converting stack to result** (LIFO reversal needed)
4. **Using stack when array/deque would be better** (need random access)
5. **Not handling edge cases**: Empty input, all same elements

## Pattern Recognition Checklist

Use Stack when you see:
- ✅ Matching/balancing pairs
- ✅ Need most recent element frequently
- ✅ Reverse order processing
- ✅ Nested structures
- ✅ Undo/backtrack operations
- ❌ Need random access → Use array instead
- ❌ Need both ends → Use deque
- ❌ Need sorted order → Different structure

## Example Problems by Difficulty

### Easy:
- Valid Parentheses ⭐
- Implement Stack using Queues
- Baseball Game
- Remove All Adjacent Duplicates

### Medium:
- Min Stack
- Evaluate Reverse Polish Notation
- Daily Temperatures (Monotonic Stack) ⭐
- Decode String
- Remove K Digits

### Hard:
- Basic Calculator
- Largest Rectangle in Histogram (Monotonic Stack) ⭐
- Maximal Rectangle
- Trapping Rain Water (can use stack)

## Interview Tips

1. **Ask about duplicates**: Can elements repeat?
2. **Clarify input**: Already validated or need validation?
3. **Edge cases**: Empty input, single element, all same
4. **Space constraints**: Can you use O(n) space?
5. **Alternative approaches**: Sometimes deque is better than stack

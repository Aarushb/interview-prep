/*
PROBLEM: Valid Parentheses (LeetCode 20)
DESCRIPTION: Given a string containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid: every opening bracket must be closed by the same type of
bracket, and in the correct order.
CONSTRAINTS: String may contain only bracket characters.
EXAMPLE INPUT/OUTPUT: "()[]{}" -> true. "(]" -> false. "([)]" -> false. "{[]}" -> true.
*/

/*
APPROACH:
Classic stack application. Push every opening bracket onto a stack. On seeing a closing bracket,
check the stack isn't empty and that its top matches the corresponding opening bracket for this
closer; if so pop it, otherwise the string is invalid. At the end the stack must be empty (no
unmatched openers left). This exercises pure LIFO push/pop/top usage.
*/

#include <bits/stdc++.h>
using namespace std;

bool isValid(const string& s) {
    stack<char> st;
    unordered_map<char, char> closeToOpen = { {')', '('}, {']', '['}, {'}', '{'} };

    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (st.empty() || st.top() != closeToOpen[c]) return false;
            st.pop();
        }
    }
    return st.empty();
}

/*
PROBLEM: Implement Queue using Stacks (LeetCode 232)
DESCRIPTION: Implement a first-in-first-out (FIFO) queue using only two stacks. The queue should
support push, pop, peek, and empty, all using standard stack operations only.
CONSTRAINTS: Only push, pop, top/peek, and empty operations are valid on the underlying stacks.
EXAMPLE INPUT/OUTPUT: push(1); push(2); peek()->1; pop()->1; empty()->false.
*/

/*
APPROACH:
Use two stacks: `inStack` for incoming pushes, `outStack` for outgoing pops/peeks. push() always
goes onto inStack in O(1). When pop() or peek() is called and outStack is empty, transfer all
elements from inStack to outStack (reversing their order, which converts stack LIFO order into
queue FIFO order), then operate on outStack's top. Each element is moved from inStack to outStack
at most once, so although a single transfer can be O(n), the amortized cost per operation is O(1).
*/

class MyQueue {
    stack<int> inStack;
    stack<int> outStack;

    void transferIfNeeded() {
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
    }

public:
    MyQueue() {}

    void push(int x) {
        inStack.push(x);
    }

    int pop() {
        transferIfNeeded();
        int front = outStack.top();
        outStack.pop();
        return front;
    }

    int peek() {
        transferIfNeeded();
        return outStack.top();
    }

    bool empty() {
        return inStack.empty() && outStack.empty();
    }
};

int main() {
    cout << "-- Valid Parentheses --\n";
    vector<string> tests = {"()[]{}", "(]", "([)]", "{[]}", "((()))"};
    for (const string& t : tests) {
        cout << "\"" << t << "\" -> " << (isValid(t) ? "true" : "false") << "\n";
    }
    cout << "\n";

    cout << "-- Implement Queue using Stacks --\n";
    MyQueue q;
    q.push(1);
    q.push(2);
    cout << "peek() = " << q.peek() << "\n"; // 1
    cout << "pop()  = " << q.pop() << "\n";  // 1
    cout << "empty() = " << (q.empty() ? "true" : "false") << "\n"; // false
    q.push(3);
    cout << "pop()  = " << q.pop() << "\n";  // 2
    cout << "pop()  = " << q.pop() << "\n";  // 3
    cout << "empty() = " << (q.empty() ? "true" : "false") << "\n"; // true

    return 0;
}

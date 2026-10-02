/*
PROBLEM: Find Median from Data Stream
DESCRIPTION: The median is the middle value in an ordered integer list. Implement the
MedianFinder class: addNum(int num) adds an integer from the data stream to the data structure;
findMedian() returns the median of all elements so far.
CONSTRAINTS: -10^5 <= num <= 10^5; there will be at least one element in the data structure
before calling findMedian; at most 5 * 10^4 calls will be made to addNum and findMedian.
EXAMPLE INPUT/OUTPUT: addNum(1); addNum(2); findMedian() -> 1.5; addNum(3); findMedian() -> 2.
*/

/*
APPROACH:
Split the stream into two halves using two heaps: a max-heap ("low") holding the smaller half of
the numbers and a min-heap ("high") holding the larger half. On every insertion, route the value
to the correct half and then rebalance so the two heaps' sizes never differ by more than one
(low is allowed to have at most one extra element). The median is then O(1) to read: either the
top of low (if it has the extra element) or the average of both tops when sizes are equal.
*/

#include <bits/stdc++.h>
using namespace std;

class MedianFinder {
public:
    void addNum(int num){
        if(low.empty() || num <= low.top()) low.push(num); else high.push(num);
        if(low.size() > high.size()+1){ high.push(low.top()); low.pop(); }
        else if(high.size() > low.size()){ low.push(high.top()); high.pop(); }
    }
    double findMedian(){
        if(low.size()==high.size()) return (low.top()+high.top())/2.0;
        return low.top();
    }
private:
    priority_queue<int> low; // max-heap
    priority_queue<int, vector<int>, greater<int>> high; // min-heap
};

int main(){
    MedianFinder mf;
    mf.addNum(1); mf.addNum(2);
    cout << mf.findMedian() << "\n"; // 1.5
    mf.addNum(3);
    cout << mf.findMedian() << "\n"; // 2
    mf.addNum(10); mf.addNum(-2); mf.addNum(5);
    cout << mf.findMedian() << "\n"; // 2
    return 0;
}

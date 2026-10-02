/*
PROBLEM: Online Stock Span
DESCRIPTION: Design an algorithm that collects daily price quotes for a stock and returns the
span of that stock's price for the current day. The span of the stock's price today is defined
as the maximum number of consecutive days (starting from today and going backward) for which
the stock price was less than or equal to today's price. Implement the StockSpanner class:
- StockSpanner() Initializes the object of the class.
- int next(int price) Returns the span of the stock's price given that today's price is price.
CONSTRAINTS:
- 1 <= price <= 10^5
- At most 10^4 calls will be made to next.
EXAMPLE INPUT/OUTPUT:
Input: ["StockSpanner","next","next","next","next","next","next","next"]
       [[],[100],[80],[60],[70],[60],[75],[85]]
Output: [null,1,1,1,2,1,4,6]
*/

/*
APPROACH:
Maintain a monotonic decreasing stack of (price, span) pairs. When a new price arrives, pop
every entry whose price is <= the new price, accumulating their spans into the new entry's
span (since those days are now "absorbed" into today's consecutive-<=-price streak), then push
(price, accumulatedSpan + 1). This works because span is really just "how far back can I see a
price <= mine," and once a smaller-or-equal price is absorbed we never need it again — the new
larger price now represents the whole absorbed run. Each price is pushed once and popped at
most once, so total work across all `next` calls is amortized O(1) each, O(n) overall.
*/

#include <bits/stdc++.h>
using namespace std;

class StockSpanner {
public:
    StockSpanner() {}

    int next(int price) {
        int span = 1;
        while (!st.empty() && st.top().first <= price) {
            span += st.top().second;
            st.pop();
        }
        st.push({price, span});
        return span;
    }

private:
    stack<pair<int, int>> st; // (price, span)
};

int main() {
    StockSpanner spanner;

    vector<int> prices = {100, 80, 60, 70, 60, 75, 85};
    vector<int> expected = {1, 1, 1, 2, 1, 4, 6};

    cout << "Calling next() on prices [100,80,60,70,60,75,85]" << endl;
    cout << "Output: [";
    for (size_t i = 0; i < prices.size(); i++) {
        cout << spanner.next(prices[i]) << (i + 1 < prices.size() ? "," : "");
    }
    cout << "] (Expected: [1,1,1,2,1,4,6])" << endl;

    return 0;
}

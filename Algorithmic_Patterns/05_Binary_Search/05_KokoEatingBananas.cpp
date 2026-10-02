/*
PROBLEM: Koko Eating Bananas
DESCRIPTION: Koko loves to eat bananas. There are n piles of bananas, the i-th pile has piles[i] bananas. The guards have gone and will come back in h hours. Koko can decide her bananas-per-hour eating speed of k. Each hour she chooses some pile and eats k bananas from it; if the pile has fewer than k bananas, she eats all of them and won't eat any more bananas during that hour. Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return. Return the minimum integer k such that she can eat all the bananas within h hours.
CONSTRAINTS:
- 1 <= piles.length <= 10^4
- piles.length <= h <= 10^9
- 1 <= piles[i] <= 10^9
EXAMPLE INPUT/OUTPUT:
Input: piles = [3,6,7,11], h = 8
Output: 4

Input: piles = [30,11,23,4,20], h = 5
Output: 30
*/

/*
APPROACH:
This isn't binary search over the array itself, it's binary search on the answer: the
eating speed k. The key insight is that "can Koko finish within h hours at speed k" is a
monotonic condition — if she can finish at some speed, she can finish at any faster speed
too. That monotonicity means I can binary search k between 1 and max(piles), using a helper
that computes total hours needed at a given speed (ceiling division per pile) and checks it
against h. Whenever a speed works, I record it and try smaller (right = mid - 1); otherwise
I need to go faster (left = mid + 1). This gives O(n log(max(piles))) time and O(1) space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1, right = *max_element(piles.begin(), piles.end());
        int result = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canFinish(piles, mid, h)) {
                result = mid;
                right = mid - 1;  // Try smaller speed
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
    
private:
    bool canFinish(vector<int>& piles, int speed, int h) {
        long long hours = 0;
        for (int pile : piles) {
            hours += (pile + speed - 1) / speed;  // Ceiling division
        }
        return hours <= h;
    }
};

int main() {
    Solution sol;
    vector<int> piles = {3,6,7,11};
    cout << sol.minEatingSpeed(piles, 8) << endl;  // 4
    return 0;
}

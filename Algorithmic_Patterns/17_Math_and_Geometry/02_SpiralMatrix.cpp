/*
PROBLEM: Spiral Matrix
DESCRIPTION: Given an m x n matrix, return all elements of the matrix in spiral order
(starting from the top-left, moving right, then down, then left, then up, spiraling inward).
CONSTRAINTS:
- m == matrix.length
- n == matrix[i].length
- 1 <= m, n <= 10
- -100 <= matrix[i][j] <= 100
EXAMPLE INPUT/OUTPUT:
- Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
  Output: [1,2,3,6,9,8,7,4,5]
- Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
  Output: [1,2,3,4,8,12,11,10,9,5,6,7]
*/

/*
APPROACH:
Maintain four boundary pointers: top, bottom, left, right, representing the current
unvisited "ring" of the matrix. Repeatedly walk the top row left-to-right, then the right
column top-to-bottom, then (if a distinct row remains) the bottom row right-to-left, then
(if a distinct column remains) the left column bottom-to-top, shrinking each boundary after
its pass. The extra checks before the third and fourth passes (top <= bottom, left <= right)
are essential to avoid re-visiting or skipping cells on non-square matrices where a ring can
collapse to a single row or column. Repeat until the boundaries cross.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        if (matrix.empty() || matrix[0].empty()) return result;

        int top = 0, bottom = (int)matrix.size() - 1;
        int left = 0, right = (int)matrix[0].size() - 1;

        while (top <= bottom && left <= right) {
            for (int c = left; c <= right; ++c) result.push_back(matrix[top][c]);
            ++top;

            for (int r = top; r <= bottom; ++r) result.push_back(matrix[r][right]);
            --right;

            if (top <= bottom) {
                for (int c = right; c >= left; --c) result.push_back(matrix[bottom][c]);
                --bottom;
            }

            if (left <= right) {
                for (int r = bottom; r >= top; --r) result.push_back(matrix[r][left]);
                ++left;
            }
        }
        return result;
    }
};

static void printVec(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i + 1 < v.size()) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;

    vector<vector<int>> matrix1 = {{1,2,3},{4,5,6},{7,8,9}};
    cout << "Input: [[1,2,3],[4,5,6],[7,8,9]]" << endl;
    cout << "Output: ";
    printVec(sol.spiralOrder(matrix1));
    cout << "Expected: [1,2,3,6,9,8,7,4,5]" << endl << endl;

    vector<vector<int>> matrix2 = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    cout << "Input: [[1,2,3,4],[5,6,7,8],[9,10,11,12]]" << endl;
    cout << "Output: ";
    printVec(sol.spiralOrder(matrix2));
    cout << "Expected: [1,2,3,4,8,12,11,10,9,5,6,7]" << endl;

    return 0;
}

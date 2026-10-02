/*
PROBLEM: Set Matrix Zeroes
DESCRIPTION: Given an m x n integer matrix, if an element is 0, set its entire row and
column to 0's. You must do it in place.
CONSTRAINTS:
- m == matrix.length
- n == matrix[i].length
- 1 <= m, n <= 200
- -2^31 <= matrix[i][j] <= 2^31 - 1
EXAMPLE INPUT/OUTPUT:
- Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
  Output: [[1,0,1],[0,0,0],[1,0,1]]
- Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
  Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
*/

/*
APPROACH:
To achieve O(1) extra space (beyond a couple of scalars), use the matrix's own first row and
first column as the marker arrays for "this row/column must be zeroed", instead of allocating
separate boolean arrays. First scan the matrix and, whenever matrix[i][j] == 0 for i>0 or
j>0, mark matrix[i][0] = 0 and matrix[0][j] = 0. Use a separate boolean to remember whether
column 0 itself originally contained a zero (since matrix[i][0] is being reused as a marker,
we can't tell afterward just by reading it) and check matrix[0][0] directly for whether row 0
needs zeroing. Then zero out the body of the matrix (rows/cols 1..end) based on the markers,
and finally zero row 0 and column 0 themselves based on the original flags, in that order so
the markers aren't destroyed before they're read.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = (int)matrix.size();
        int n = (int)matrix[0].size();

        bool firstRowHasZero = false;
        bool firstColHasZero = false;

        for (int j = 0; j < n; ++j) {
            if (matrix[0][j] == 0) { firstRowHasZero = true; break; }
        }
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) { firstColHasZero = true; break; }
        }

        // Use first row/col as markers for the rest of the matrix
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        // Zero out body cells based on markers
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // Finally handle first row and first column themselves
        if (firstRowHasZero) {
            for (int j = 0; j < n; ++j) matrix[0][j] = 0;
        }
        if (firstColHasZero) {
            for (int i = 0; i < m; ++i) matrix[i][0] = 0;
        }
    }
};

static void printMatrix(const vector<vector<int>>& m) {
    cout << "[";
    for (size_t i = 0; i < m.size(); ++i) {
        cout << "[";
        for (size_t j = 0; j < m[i].size(); ++j) {
            cout << m[i][j];
            if (j + 1 < m[i].size()) cout << ",";
        }
        cout << "]";
        if (i + 1 < m.size()) cout << ",";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;

    vector<vector<int>> matrix1 = {{1,1,1},{1,0,1},{1,1,1}};
    cout << "Input: [[1,1,1],[1,0,1],[1,1,1]]" << endl;
    sol.setZeroes(matrix1);
    cout << "Output: ";
    printMatrix(matrix1);
    cout << "Expected: [[1,0,1],[0,0,0],[1,0,1]]" << endl << endl;

    vector<vector<int>> matrix2 = {{0,1,2,0},{3,4,5,2},{1,3,1,5}};
    cout << "Input: [[0,1,2,0],[3,4,5,2],[1,3,1,5]]" << endl;
    sol.setZeroes(matrix2);
    cout << "Output: ";
    printMatrix(matrix2);
    cout << "Expected: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]" << endl;

    return 0;
}

/*
PROBLEM: Rotate Image
DESCRIPTION: You are given an n x n 2D matrix representing an image. Rotate the image by
90 degrees (clockwise), in place. You have to rotate the image in place, meaning you must
modify the input 2D matrix directly without allocating another 2D matrix for the rotation.
CONSTRAINTS:
- n == matrix.length == matrix[i].length
- 1 <= n <= 20
- -1000 <= matrix[i][j] <= 1000
EXAMPLE INPUT/OUTPUT:
- Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
  Output: [[7,4,1],[8,5,2],[9,6,3]]
- Input: matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
  Output: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
*/

/*
APPROACH:
A 90-degree clockwise rotation can be decomposed into two simpler, well-known in-place
operations: first transpose the matrix (swap matrix[i][j] with matrix[j][i] for i < j),
then reverse each row in place. Transposing flips the matrix across its main diagonal, and
reversing each row then flips it horizontally — the composition of those two reflections is
exactly a 90-degree clockwise rotation. This avoids fiddly four-way cell-swapping index math
and is easy to state and verify correct in an interview, while still being O(1) extra space.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = (int)matrix.size();

        // Step 1: transpose in place
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Step 2: reverse each row in place
        for (int i = 0; i < n; ++i) {
            reverse(matrix[i].begin(), matrix[i].end());
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

    vector<vector<int>> matrix1 = {{1,2,3},{4,5,6},{7,8,9}};
    cout << "Input: [[1,2,3],[4,5,6],[7,8,9]]" << endl;
    sol.rotate(matrix1);
    cout << "Output: ";
    printMatrix(matrix1);
    cout << "Expected: [[7,4,1],[8,5,2],[9,6,3]]" << endl << endl;

    vector<vector<int>> matrix2 = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    cout << "Input: [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]" << endl;
    sol.rotate(matrix2);
    cout << "Output: ";
    printMatrix(matrix2);
    cout << "Expected: [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]" << endl;

    return 0;
}

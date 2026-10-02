/*
PROBLEM: Valid Sudoku
DESCRIPTION: Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:
1. Each row must contain the digits 1-9 without repetition.
2. Each column must contain the digits 1-9 without repetition.
3. Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
Note: A Sudoku board (partially filled) could be valid but is not necessarily solvable. Only the filled cells need to be validated.
CONSTRAINTS:
- board.length == 9
- board[i].length == 9
- board[i][j] is a digit 1-9 or '.'
EXAMPLE INPUT/OUTPUT:
Input: board = 
[["5","3",".",".","7",".",".",".","."]
,["6",".",".","1","9","5",".",".","."]
,[".","9","8",".",".",".",".","6","."]
,["8",".",".",".","6",".",".",".","3"]
,["4",".",".","8",".","3",".",".","1"]
,["7",".",".",".","2",".",".",".","6"]
,[".","6",".",".",".",".","2","8","."]
,[".",".",".","4","1","9",".",".","5"]
,[".",".",".",".","8",".",".","7","9"]]
Output: true
*/

/*
APPROACH:
I need to check three overlapping constraints (rows, columns, 3x3 boxes) at once, so I maintain one
hash set per row, per column, and per box, and do a single pass over all 81 cells. For each filled
cell I compute its box index as (row/3)*3 + (col/3) and check whether the digit already exists in
the corresponding row, column, or box set; if so, the board is invalid. Otherwise I insert the digit
into all three sets and continue, giving a one-pass, effectively O(1) solution since the board size
is fixed.
*/

#include <bits/stdc++.h>
using namespace std;

/*
SOLUTION APPROACH:

We need to validate three constraints simultaneously:
1. No duplicate in any row
2. No duplicate in any column  
3. No duplicate in any 3x3 sub-box

NAIVE APPROACH:
- Check each row separately: O(81)
- Check each column separately: O(81)
- Check each 3x3 box separately: O(81)
- Total: 3 passes through board

OPTIMAL APPROACH (One Pass):
Use hash sets to track seen numbers in:
- 9 row sets
- 9 column sets
- 9 box sets

TRICK FOR BOX INDEX:
For cell at (row, col), which box does it belong to?
- Box index = (row / 3) * 3 + (col / 3)

Example mapping:
(0,0) to (0,8), (1,0) to (1,8), (2,0) to (2,8) → boxes 0,1,2
(3,0) to (3,8), (4,0) to (4,8), (5,0) to (5,8) → boxes 3,4,5
(6,0) to (6,8), (7,0) to (7,8), (8,0) to (8,8) → boxes 6,7,8

Box visualization:
[0][1][2]
[3][4][5]
[6][7][8]

ALGORITHM:
1. Create 9 sets each for rows, columns, and boxes
2. Iterate through each cell
3. If cell is not empty:
   - Check if number exists in corresponding row/col/box set
   - If yes → duplicate found, return false
   - If no → add to all three sets
4. If all cells checked without duplicates → return true

TIME: O(1) since board is fixed 9x9 = 81 cells
SPACE: O(1) since maximum 9 sets × 9 elements each = constant
*/

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        // Create hash sets for rows, columns, and boxes
        vector<unordered_set<char>> rows(9);
        vector<unordered_set<char>> cols(9);
        vector<unordered_set<char>> boxes(9);
        
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                char num = board[row][col];
                
                // Skip empty cells
                if (num == '.') continue;
                
                // Calculate box index
                int boxIndex = (row / 3) * 3 + (col / 3);
                
                // Check if number already exists in row, column, or box
                if (rows[row].count(num) || 
                    cols[col].count(num) || 
                    boxes[boxIndex].count(num)) {
                    return false;  // Duplicate found
                }
                
                // Add number to respective sets
                rows[row].insert(num);
                cols[col].insert(num);
                boxes[boxIndex].insert(num);
            }
        }
        
        return true;  // No duplicates found
    }
    
    // Alternative: Using strings instead of sets (more memory efficient)
    bool isValidSudokuString(vector<vector<char>>& board) {
        unordered_set<string> seen;
        
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                char num = board[row][col];
                
                if (num == '.') continue;
                
                // Create unique identifiers
                string rowKey = to_string(num) + " in row " + to_string(row);
                string colKey = to_string(num) + " in col " + to_string(col);
                string boxKey = to_string(num) + " in box " + to_string(row/3) + "-" + to_string(col/3);
                
                // Check if any key already exists
                if (seen.count(rowKey) || seen.count(colKey) || seen.count(boxKey)) {
                    return false;
                }
                
                seen.insert(rowKey);
                seen.insert(colKey);
                seen.insert(boxKey);
            }
        }
        
        return true;
    }
};

int main() {
    Solution sol;
    
    // Test Case 1 - Valid Sudoku
    vector<vector<char>> board1 = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    cout << "Test 1 (Valid): " << (sol.isValidSudoku(board1) ? "true" : "false") << endl;
    // Expected: true
    
    // Test Case 2 - Invalid (duplicate in row)
    vector<vector<char>> board2 = {
        {'8','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','8','.','.','.','.','6','.'},
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    cout << "Test 2 (Invalid - dup in column): " << (sol.isValidSudoku(board2) ? "true" : "false") << endl;
    // Expected: false (8 appears twice in first column)
    
    // Test Case 3 - Invalid (duplicate in box)
    vector<vector<char>> board3 = {
        {'5','3','.','.','7','.','.','.','.'},
        {'6','.','.','1','9','5','.','.','.'},
        {'.','9','5','.','.','.','.','6','.'},  // 5 appears twice in top-left box
        {'8','.','.','.','6','.','.','.','3'},
        {'4','.','.','8','.','3','.','.','1'},
        {'7','.','.','.','2','.','.','.','6'},
        {'.','6','.','.','.','.','2','8','.'},
        {'.','.','.','4','1','9','.','.','5'},
        {'.','.','.','.','8','.','.','7','9'}
    };
    cout << "Test 3 (Invalid - dup in box): " << (sol.isValidSudoku(board3) ? "true" : "false") << endl;
    // Expected: false
    
    // Test Case 4 - Using string approach
    cout << "\n=== Using String Approach ===" << endl;
    cout << "Test 4 (String method): " << (sol.isValidSudokuString(board1) ? "true" : "false") << endl;
    // Expected: true
    
    return 0;
}

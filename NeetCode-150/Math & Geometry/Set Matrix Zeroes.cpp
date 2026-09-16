// Problem: Set Matrix Zeroes
// Platform: NeetCode
// Link: https://neetcode.io/problems/set-matrix-zeroes
// time complexity: O(m * n); m = matrix.size(), n = matrix[0].size()
// space complexity: O(1); 

/*
Example Matrix
1 1 1
1 0 1
1 1 1

row = 3, col = 3

Step 1: First column e 0 ache kina check (colZero)

Loop: i=0,1,2 → check matrix[i][0]

matrix[0][0] = 1 → না
matrix[1][0] = 1 → না
matrix[2][0] = 1 → না

→ colZero = false

Step 2: First row e 0 ache kina check (rowZero)

Loop: j=0,1,2 → check matrix[0][j]

matrix[0][0] = 1 → না
matrix[0][1] = 1 → না
matrix[0][2] = 1 → না

→ rowZero = false

(Ei example e first row/column e কোনো 0 নেই, তাই দুটোই false থাকবে — পরে ei flag গুলো use হবে না।)

Step 3: Baki matrix scan kore marker বসানো (i=1,2 ar j=1,2)
i=1, j=1: matrix[1][1] = 0 → হ্যাঁ, 0! তাই:
matrix[1][0] = 0 (row 1 marker)
matrix[0][1] = 0 (column 1 marker)
i=1, j=2: matrix[1][2] = 1 → না, skip
i=2, j=1: matrix[2][1] = 1 → না, skip
i=2, j=2: matrix[2][2] = 1 → না, skip

Matrix ekhon (marker বসার পর):

1 0 1
0 0 1
1 1 1
Step 4: Marker onujayi actual zero বসানো (i=1,2 ar j=1,2)
i=1, j=1: check matrix[1][0]==0 (হ্যাঁ, true) → matrix[1][1] = 0 (already 0 ছিল, থাকলোই)
i=1, j=2: check matrix[1][0]==0 (true, row marker) → matrix[1][2] = 0
i=2, j=1: check matrix[0][1]==0 (true, column marker) → matrix[2][1] = 0
i=2, j=2: check matrix[2][0]==0 false, matrix[0][2]==0 false → skip, unchanged

Matrix ekhon:

1 0 1
0 0 0
1 0 1
Step 5 & 6: colZero/rowZero false, tাই first row/column আলাদা করে zero করার দরকার নেই — skip।
Final Result:
1 0 1
0 0 0
1 0 1

Check kore dekho — original matrix[1][1]=0 chilo, tার পুরো row 1 (0 0 0) ar পুরো column 1 (উপর-নিচে 0,0,0) zero হয়ে গেছে, baki cell unchanged আছে। এটাই expected output।  
*/

class Solution
{
public:
    void setZeroes(vector<vector<int>>& matrix)
    {
        int row = matrix.size(), col = matrix[0].size();
        bool rowZero = false, colZero = false;   // first row/column e originally 0 ache kina track korbe
        // First column e kono 0 ache kina check
        for (int i = 0; i < row; i++)
        {
            if (matrix[i][0] == 0)
            {
                colZero = true;
            }
        }
        // First row e kono 0 ache kina check
        for (int j = 0; j < col; j++)
        {
            if (matrix[0][j] == 0)
            {
                rowZero = true;
            }
        }

        // Baki matrix scan kore (i=1, j=1 theke) first row/col ke marker banao
        for (int i = 1; i < row; i++)
        {
            for (int j = 1; j < col; j++)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;   // ei row zero hobe, mark koro
                    matrix[0][j] = 0;   // ei column zero hobe, mark koro
                }
            }
        }

        // Marker onujayi actual value 0 koro (first row/col chara)
        for (int i = 1; i < row; i++)
        {
            for (int j = 1; j < col; j++)
            {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                {
                    matrix[i][j] = 0;
                }
            }
        }

        // Original first column e 0 thakle, pura first column 0 koro
        if (colZero)
        {
            for (int i = 0; i < row; i++)
            {
                matrix[i][0] = 0;
            }
        }

        // Original first row e 0 thakle, pura first row 0 koro
        if (rowZero)
        {
            for (int j = 0; j < col; j++)
            {
                matrix[0][j] = 0;
            }
        }
    }
};
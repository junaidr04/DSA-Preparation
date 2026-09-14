// Problem: Rotate Image
// Platform: NeetCode
// Link: https://neetcode.io/problems/rotate-image
// time complexity: O(n^2); n = matrix.size()
// space complexity: O(1); 

/*
Original matrix (4x4):

 1  2  3  4
 5  6  7  8
 9 10 11 12
13 14 15 16
Step 1: Transpose (matrix[i][j] <-> matrix[j][i], j starts from i+1)

i = 0 (row 0):

j=1: swap matrix[0][1](2) ও matrix[1][0](5) → 2↔5
j=2: swap matrix[0][2](3) ও matrix[2][0](9) → 3↔9
j=3: swap matrix[0][3](4) ও matrix[3][0](13) → 4↔13

Matrix ekhon:

 1  5  9 13
 2  6  7  8
 3 10 11 12
 4 14 15 16

i = 1 (row 1):

j=2: swap matrix[1][2](7) ও matrix[2][1](10) → 7↔10
j=3: swap matrix[1][3](8) ও matrix[3][1](14) → 8↔14

Matrix ekhon:

 1  5  9 13
 2  6 10 14
 3  7 11 12
 4  8 15 16

i = 2 (row 2):

j=3: swap matrix[2][3](12) ও matrix[3][2](15) → 12↔15

Matrix ekhon:

 1  5  9 13
 2  6 10 14
 3  7 11 15
 4  8 12 16

i = 3: j start hobে i+1 = 4, kintু loop condition j < n = 4 — tai loop run e hobে na। (Eijonyoi last row e kono swap lagে na, already sob hoye gেছে।)

Transpose shesh hole:

 1  5  9 13
 2  6 10 14
 3  7 11 15
 4  8 12 16

(Dekho — original column 1 ekhon row 1, column 2 → row 2, etc.)

Step 2: Prottek row reverse koro
Row 0: [1,5,9,13] → reverse → [13,9,5,1]
Row 1: [2,6,10,14] → reverse → [14,10,6,2]
Row 2: [3,7,11,15] → reverse → [15,11,7,3]
Row 3: [4,8,12,16] → reverse → [16,12,8,4]

Final matrix:

13  9  5  1
14 10  6  2
15 11  7  3
16 12  8  4

Check kore dekho — original first column chilo [1,5,9,13] (top theke niche), ar ekhon eitাই hoye গেছে top row, kintু reverse order e (13,9,5,1)। Eita-ই 90° clockwise rotation er property — first column bottom-to-top order e new first row hoy।  
*/

class Solution
{
public:
    void rotate(vector<vector<int>>& matrix)
    {
        int n = matrix.size();               // matrix square, tai n x n
        // Step 1: Transpose — row o column swap kore felo
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)  // j = i+1 theke shuru, double-swap avoid korte
            {
                swap(matrix[i][j], matrix[j][i]); // (i,j) ar (j,i) er value oদল-বদল
            }
        }
        // Step 2: Prottek row ke reverse koro — eita clockwise rotation complete kore
        for (int i = 0; i < n; i++)
        {
            reverse(matrix[i].begin(), matrix[i].end()); // row-er left-right flip
        }
    }
};
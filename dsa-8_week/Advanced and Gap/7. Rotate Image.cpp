// TC: O(n²), protita ghor ekbar
// SC: O(n²), extra temp grid

/*
matrix = [[1, 2, 3],
          [4, 5, 6],
          [7, 8, 9]]
Shuru
cpp
int n = matrix.size();                         // n = 3
vector<vector<int>> temp(n, vector<int>(n));   // temp = 3x3, sob 0
temp = 0 0 0
       0 0 0
       0 0 0

Formula: (i, j) er number jabe temp[j][n-1-i] te. n-1 = 2, tai temp[j][2-i].

Loop er dry run (9 ta step)
i = 0 (row 1 2 3), column position = 2 - 0 = 2
j	matrix[i][j]	temp[j][2-i]	temp er obostha (por)
0	1	temp[0][2]	0 0 1 / 0 0 0 / 0 0 0
1	2	temp[1][2]	0 0 1 / 0 0 2 / 0 0 0
2	3	temp[2][2]	0 0 1 / 0 0 2 / 0 0 3

Prothom row 1 2 3 temp er sesh column e upor theke niche boshlo.

i = 1 (row 4 5 6), column position = 2 - 1 = 1
j	matrix[i][j]	temp[j][2-i]	temp er obostha (por)
0	4	temp[0][1]	0 4 1 / 0 0 2 / 0 0 3
1	5	temp[1][1]	0 4 1 / 0 5 2 / 0 0 3
2	6	temp[2][1]	0 4 1 / 0 5 2 / 0 6 3

Dwitiyo row 4 5 6 majher column e boshlo.

i = 2 (row 7 8 9), column position = 2 - 2 = 0
j	matrix[i][j]	temp[j][2-i]	temp er obostha (por)
0	7	temp[0][0]	7 4 1 / 0 5 2 / 0 6 3
1	8	temp[1][0]	7 4 1 / 8 5 2 / 0 6 3
2	9	temp[2][0]	7 4 1 / 8 5 2 / 9 6 3

Tritiyo row 7 8 9 baam column e boshlo.

Shesh
cpp
matrix = temp;
matrix = 7 4 1
         8 5 2
         9 6 3

Expected [[7,4,1],[8,5,2],[9,6,3]] er sathe mile gelo ✅

Pattern ta dekho
Input row i	Output e kothay gelo
0	column 2 (sesh)
1	column 1 (majh)
2	column 0 (baam)

Row i -> column n-1-i, ar row er j-th number -> row j. Mane input row ta output column hoye jay, upor theke niche.

*/

// brute force..
class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        int n = matrix.size(); // grid n x n
        vector<vector<int>> temp(n, vector<int>(n));
        // temp ekta notun n x n grid, shuru te sob 0
        // Example: temp = [[0,0,0],[0,0,0],[0,0,0]]
        // eta ekta "khata" jekhane rotate kora answer likhbo
        for (int i = 0; i < n; i++)
        {
            // i = purono grid er row. i = 0, 1, 2 (n=3, tai i < 3)
            for (int j = 0; j < n; j++)
            {
                // j = purono grid er column. protita row er sob 3 ta column dekhbo
                temp[j][n - 1 - i] = matrix[i][j];
                // purono (i, j) er number ta notun grid er (j, n-1-i) te boshao
                // matrix[row][column] format: notun row = j, notun column = n-1-i
            }
        }
        matrix = temp;
        // temp er sob kichu asol matrix e copy. matrix reference, tai caller er grid o change hoye gelo
    }
};

// TC: O(n²), protita ghor ekbar
// SC: O(1), extra space nai



// In-place (transpose + reverse)
class Solution
{
public:
    void rotate(vector<vector<int>> &matrix)
    {
        // void: kichu return korbe na. matrix& (reference): asol matrix-i change hobe, copy na.

        int n = matrix.size();
        // grid n x n, tai row = column = n
        // Example: n = 3

        // ---------- Step 1: Transpose (row ke column banano) ----------
        for (int i = 0; i < n; i++)
        {
            // i = row. i = 0, 1, 2

            for (int j = i + 1; j < n; j++)
            {
                // j = column, shuru hoy i+1 theke, mane diagonal er UPORER ghor gulo
                // keno i+1? (i,j) ar (j,i) ek-i jora. ekbar-i swap korle hoy.
                // j = 0 theke shuru korle same jora duibar swap hoto, ager obostha-i ferot ashto.
                // Example: i=0 hole j = 1, 2 | i=1 hole j = 2 | i=2 hole j er kono maan nei (3<3 false)

                swap(matrix[i][j], matrix[j][i]);
                // (i,j) ar (j,i) er number jaygа bodlalo
                // i=0,j=1: matrix[0][1]=2 <-> matrix[1][0]=4  =>  1 4 3 / 2 5 6 / 7 8 9
                // i=0,j=2: matrix[0][2]=3 <-> matrix[2][0]=7  =>  1 4 7 / 2 5 6 / 3 8 9
                // i=1,j=2: matrix[1][2]=6 <-> matrix[2][1]=8  =>  1 4 7 / 2 5 8 / 3 6 9
            }
        }
        // Transpose shesh: 1 4 7 / 2 5 8 / 3 6 9
        // diagonal (1, 5, 9) kokhono swap hoy nai, nijer jaygay-i

        // ---------- Step 2: Protita row reverse ----------
        for (int i = 0; i < n; i++)
        {
            // i = row. i = 0, 1, 2

            reverse(matrix[i].begin(), matrix[i].end());
            // matrix[i] = ekta row. begin() = row er shuru, end() = row er shesh (ekই row er duita)
            // reverse = row er number gulo ulte dey
            // i=0: 1 4 7 -> 7 4 1
            // i=1: 2 5 8 -> 8 5 2
            // i=2: 3 6 9 -> 9 6 3
        }
        // Final: 7 4 1 / 8 5 2 / 9 6 3 ✅ Expected er sathe mile gelo
    }
};
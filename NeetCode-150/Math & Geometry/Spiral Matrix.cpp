// Problem: Spiral Matrix
// Platform: NeetCode
// Link: https://neetcode.io/problems/spiral-matrix
// time complexity: O(m * n); m = matrix.size(), n = matrix[0].size()
// space complexity: O(1); extra space use koreni, output vector chara

/*
Example diye Calculation

Matrix (3x4):

 1  2  3  4
 5  6  7  8
 9 10 11 12

Start: top=0, bottom=2, left=0, right=3

Iteration 1 (top<=bottom && left<=right → 0<=2 && 0<=3 ✅ true):

Top row (col: 0→3, row fixed top=0):
matrix[0][0]=1, matrix[0][1]=2, matrix[0][2]=3, matrix[0][3]=4
ans = [1,2,3,4]
top++ → top=1
Right column (row: 1→2, column fixed right=3):
matrix[1][3]=8, matrix[2][3]=12
ans = [1,2,3,4,8,12]
right-- → right=2
Bottom row check (top<=bottom → 1<=2 ✅ true):
col: 2→0 (reverse), row fixed bottom=2:
matrix[2][2]=11, matrix[2][1]=10, matrix[2][0]=9
ans = [1,2,3,4,8,12,11,10,9]
bottom-- → bottom=1
Left column check (left<=right → 0<=2 ✅ true):
row: 1→1 (reverse, since bottom=1, top=1 — ekটাই value), column fixed left=0:
matrix[1][0]=5
ans = [1,2,3,4,8,12,11,10,9,5]
left++ → left=1

Iteration 2 check: top<=bottom && left<=right → 1<=1 && 1<=2 ✅ true, loop chaলবে।

Top row (col: 1→2, row fixed top=1):
matrix[1][1]=6, matrix[1][2]=7
ans = [1,2,3,4,8,12,11,10,9,5,6,7]
top++ → top=2
Right column (row: 2→1 → loop condition row<=bottom → 2<=1 false, loop run e hobe na)
right-- → right=1
Bottom row check (top<=bottom → 2<=1 ❌ false — skip)
Left column check (left<=right → 1<=1 ✅ true):
row: bottom→top → 1→2 → condition row>=top → 1>=2 false, loop run e hobe na
left++ → left=2

Iteration 3 check: top<=bottom && left<=right → 2<=1 ❌ false → loop exit

Final answer:

ans = [1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7]
*/

class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix)
    {
        vector<int> ans;                              // final spiral order er result store korbe
        int top=0, bottom=matrix.size()-1;             // top = প্রথম row index, bottom = শেষ row index
        int left=0, right=matrix[0].size()-1;           // left = প্রথম column index, right = শেষ column index
        while(top <= bottom && left <= right)           // jotokhon valid region (row/column) bakhi ache
        {
            for(int col=left; col<=right; col++)        // top row ta left theke right porjonto ghuraw
            {
                ans.push_back(matrix[top][col]);         // row fixed (top), column change hocche
            }
            top++;                                        // top row done, tai top row ke ek ghor niche namao
            for(int row=top; row<=bottom; row++)          // right column ta (notun) top theke bottom porjonto
            {
                ans.push_back(matrix[row][right]);         // column fixed (right), row change hocche
            }
            right--;                                       // right column done, tai right ke ek ghor bame ashao
            if(top <= bottom)                              // check: ekটা row o ki bakhi ache? (single-row matrix hole na thakte pare)
            {
                for(int col=right; col>=left; col--)        // bottom row ta right theke left (reverse direction)
                {
                    ans.push_back(matrix[bottom][col]);      // row fixed (bottom), column reverse e change
                }
                bottom--;                                     // bottom row done, tai bottom ke ek ghor upore tulo
            }
            if(left <= right)                              // check: ekটা column o ki bakhi ache? (single-column matrix hole na thakte pare)
            {
                for(int row=bottom; row>=top; row--)         // left column ta bottom theke top (reverse direction)
                {
                    ans.push_back(matrix[row][left]);         // column fixed (left), row reverse e change
                }
                left++;                                        // left column done, tai left ke ek ghor dane sorao
            }
        }
        return ans;                                          // pura spiral order return
    }
};
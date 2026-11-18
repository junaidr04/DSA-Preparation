// TC: O(m × n), protita ghor ekbar-i dekha hoy
// SC: O(1) extra (ans chhara shudhu 4 ta variable)

/*
Dry run 1: 3x3

matrix = [[1,2,3],[4,5,6],[7,8,9]], shuru: top=0, bottom=2, left=0, right=2

Step	Ki hoy	                        ans	    Boundary por
1	    matrix[0][0..2]	                1,2,3	top=1
2	    matrix[1..2][2]	                +6,9	right=1
3	    1<=2 ok, matrix[2][1..0]	    +8,7	bottom=1
4	    0<=1 ok, matrix[1][0]	        +4	    left=1
abar 1	matrix[1][1]	                +5	    top=2
abar 2	i=2; 2<=1 false, kichu na		        right=0
abar 3	top=2 <= bottom=1 false, skip		
abar 4	left=1 <= right=0 false, skip		

while: top=2 <= bottom=1 false, thame. Return [1,2,3,6,9,8,7,4,5]
*/


class Solution
{
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix)
    {
        vector<int> ans;                       // answer ekhane jog hobe
        int m = matrix.size();                 // row er songkha
        int n = matrix[0].size();              // column er songkha
        int top = 0;                           // upor er row
        int bottom = m - 1;                    // sobcheye niche er row (index 0 theke, tai m-1)
        int left = 0;                          // baam er column
        int right = n - 1;                     // sobcheye dan er column

        while (top <= bottom && left <= right) // bhitore ghor baki thakle
        {
            // Step 1: upor row, baam theke dane
            for (int j = left; j <= right; j++)
                ans.push_back(matrix[top][j]); // row top fixed, column j ghure
            top++;                             // upor row shesh, sima niche namlo

            // Step 2: dan column, upor theke niche
            for (int i = top; i <= bottom; i++)
                ans.push_back(matrix[i][right]); // row i ghure, column right fixed
            right--;                           // dan column shesh, sima baame shorlo

            // Step 3: niche row, dan theke baame
            if (top <= bottom)                 // row baki na thakle duplicate hobe, tai check
            {
                for (int j = right; j >= left; j--)
                    ans.push_back(matrix[bottom][j]); // row bottom fixed, column j komche
                bottom--;                      // niche row shesh, sima upore uthlo
            }

            // Step 4: baam column, niche theke upore
            if (left <= right)                 // column baki na thakle duplicate hobe, tai check
            {
                for (int i = bottom; i >= top; i--)
                    ans.push_back(matrix[i][left]); // row i komche, column left fixed
                left++;                        // baam column shesh, sima dane shorlo
            }
        }
        return ans;                            
    }
};
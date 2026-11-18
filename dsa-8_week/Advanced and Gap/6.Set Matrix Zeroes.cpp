// TC: O(m × n), duita pass, protita ghor 2 bar dekha
// SC: O(m + n), rowZero ar colZero er jonno


/*
Dry run (Example 1)
1 1 1
1 0 1
1 1 1

Pass 1: (1,1) e 0 pelam, rowZero[1] = true, colZero[1] = true. Baki ghor e 0 nei.

rowZero = [F, T, F]
colZero = [F, T, F]

Pass 2:

ghor	rowZero[i] || colZero[j]	result
(0,0)	F || F	                    1
(0,1)	F || T	                    0
(0,2)	F || F	                    1
(1,0)	T || F	                    0
(1,1)	T || T	                    0
(1,2)	T || F	                    0
(2,0)	F || F	                    1
(2,1)	F || T	                    0
(2,2)	F || F	                    1

Output [[1,0,1],[0,0,0],[1,0,1]]  
*/

class Solution
{
public:
    void setZeroes(vector<vector<int>> &matrix)
    {
        int m = matrix.size();    // row er songkha
        int n = matrix[0].size(); // column er songkha

        vector<bool> rowZero(m, false); // rowZero[i] = true mane row i te asol 0 ache
        vector<bool> colZero(n, false); // colZero[j] = true mane column j te asol 0 ache

        // Pass 1: shudhu dekho, grid change korbo na
        for (int i = 0; i < m; i++) // i = row
        { 
            for (int j = 0; j < n; j++) // j = column
            { 
                if (matrix[i][j] == 0) // asol 0 peyechi
                {                      
                    rowZero[i] = true; // ei row ke mark koro
                    colZero[j] = true; // ei column ke mark koro
                }
            }
        }

        // Pass 2: ebar grid change koro
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (rowZero[i] || colZero[j]) // row ba column marked hole
                {                     
                    matrix[i][j] = 0; // ei ghor 0
                }
            }
        }
    }
};
// time complexity: O(m*n) where m is the number of rows and n is the number of columns in the grid, as we need to visit each cell once in the worst case
// space complexity: O(m*n) in the worst case, where all cells are rotten at the same time and added to the queue

class Solution
{
public:
    int orangesRotting(vector<vector<int>>& grid)
    {
        // grid er row (m) ar column (n) ber kore nilam
        int m = grid.size(), n = grid[0].size();

        // queue te pocha phol (2) er position (row, col) thakbe, BFS er shuru ekhan theke
        queue<pair<int,int>> q;

        // bhalo phol (1) koyta ache ta gunbo, shesh e -1 check er jonno lagbe
        int fresh = 0;

        // grid scan korbo, upor-bam theke niche-dan porjonto
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // pocha phol pele queue te rakhlam (shob 2 ek shathe, multi-source BFS)
                if (grid[i][j] == 2)
                    q.push({i, j});
                // bhalo phol pele gonona baralam
                else if (grid[i][j] == 1)
                    fresh++;
            }
        }

        // koto minute lagche ta ekhane gunbo
        int minutes = 0;

        // dr, dc: chardike jaoar jonno (upor, niche, bam, dan), diagonal na
        vector<int> dr = {-1, 1, 0, 0};
        vector<int> dc = {0, 0, -1, 1};

        // jotokkhon queue te cell ache ebong bhalo phol baki ache, ghurbo
        // (fresh > 0 na dile shesh level e extra minute jog hoto)
        while (!q.empty() && fresh > 0)
        {
            // ei level (ek minute) e koyta cell ache; for er age nilam
            // karon for er bhitore queue te notun cell dhukbe, size bodle jabe
            int sz = q.size();

            // ei minute er shob pocha cell ek shathe process korbo
            for (int k = 0; k < sz; k++)
            {
                // queue theke samner cell nilam
                auto [row, col] = q.front();
                // oita queue theke soriye dilam
                q.pop();

                // oi cell er chardike dekhbo
                for (int d = 0; d < 4; d++)
                {
                    // neighbour er row ar column
                    int nr = row + dr[d], nc = col + dc[d];

                    // grid er baire gele skip korbo
                    if (nr < 0 || nc < 0 || nr >= m || nc >= n)
                        continue;

                    // neighbour bhalo phol hole pocabo
                    if (grid[nr][nc] == 1)
                    {
                        grid[nr][nc] = 2;   // pocha banalam (visited chinho-o eta)
                        q.push({nr, nc});   // porer minute e eta theke spread hobe
                        fresh--;            // ekta bhalo phol kombe
                    }
                }
            }
            // ei level shesh, ek minute pass holo
            minutes++;
        }

        // kichu bhalo phol ekhono baki mane kokhono pocbe na, tai -1
        if (fresh > 0)
            return -1;

        // shob pocheche, koto minute lagche ta ferot dilam
        return minutes;
    }
};
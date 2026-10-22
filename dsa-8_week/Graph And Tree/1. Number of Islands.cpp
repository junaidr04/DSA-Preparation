// Time: O(m × n); Scan loop prottek cell e ekbar jay: m × n. DFS prottek '1' cell e dhukar shathe shathe '0' kore dey, tai ekta cell e DFS maksimum ekbar-i dhuke. Baki call gulo base case e ('0' ba grid er baire) shathe shathe ferot jay, ar eta constant kaj. Mot kaj O(m × n).

// Space: O(m × n); worst case, extra visited array lage na.Chinhito korar jonno: O(1) extra, karon grid er cell e-i '0' likhecho. Recursion stack: eta-i asol space. Sob cell '1' hole (jemon snake-shape ba puro grid '1'), DFS ta ekta lomba pothe ghure, ek shathe prai m × n ta call stack e thake. Tai worst case e stack O(m × n). 300×300 e prai 90,000 ta nested call, ja kichu environment e stack overflow korte pare.

class Solution {
public:
    int numIslands(vector<vector<char>> &grid)
    {
        // grid er row (m) ar column (n) ber kore nilam
        int m = grid.size(), n = grid[0].size();
        // koyta island paisi, ta ekhane gunbo
        int count = 0;
        // prottek cell e scan korbo, upor-bam theke niche-dan porjonto
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // '1' (char) mane sthol; ei cell ta ekta notun island er shuru
                if (grid[i][j] == '1')
                {
                    count++;          // notun island paisi, tai count baralam
                    dfs(grid, i, j);  // ei island er shob connected '1' ke '0' kore dilam,
                                      // jeno scan e porer cell gulo abar count na hoy
                }
            }
        }
        return count;
    }

    // grid ke reference (&) e pathacchi, jeno copy na hoy ar original grid modify hoy
    void dfs(vector<vector<char>>& grid, int i, int j)
    {
        int m = grid.size(), n = grid[0].size();
        // base case: grid er baire gele ba jol ('0') / ager dekha cell pele ferot jabo
        // mone rakho: age range check, tarpor grid[i][j] access, na hole out-of-bounds
        if (i < 0 || j < 0 || i >= m || j >= n || grid[i][j] == '0')
            return;
        // dhukar shathe shathe cell ta '0' kore dilam (visited chinho),
        // eta-i ager cell e fire jaoa ar infinite loop thamay
        grid[i][j] = '0';
        // chardike jabo (diagonal na)
        dfs(grid, i + 1, j);  // niche
        dfs(grid, i - 1, j);  // upore
        dfs(grid, i, j + 1);  // dane
        dfs(grid, i, j - 1);  // bame
    }
};
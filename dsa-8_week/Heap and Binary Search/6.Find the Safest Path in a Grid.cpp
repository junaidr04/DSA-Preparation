// TC: O(n² log n); n is the size of the grid, because we are using a priority queue to explore the grid, and in the worst case, we may need to explore all n² cells. Each insertion and extraction from the priority queue takes O(log n²) time, which simplifies to O(log n). Therefore, the overall time complexity is O(n² log n).
// SC: O(n²); n is the size of the grid, because we are storing all the cells in the priority queue, which can contain up to n² cells in the worst case.

/*
Dry run: grid = [[0,0,1],[0,0,0],[0,0,0]]
0 0 1
0 0 0
0 0 0

Part 1: Safeness table (multi-source BFS)

Shuru: chor (0,2). dist[0][2] = 0, q = [(0,2)]. Baki -1.

-1 -1  0
-1 -1 -1
-1 -1 -1
Pop	Neighbor (notun)	dist set
(0,2)	(1,2) niche, (0,1) baam	dono 1
(1,2)	(2,2), (1,1)	dono 2
(0,1)	(0,0)	2 ((1,1) already set, skip)
(2,2)	(2,1)	3
(1,1)	(1,0)	3
(0,0)	kichu notun na	
(2,1)	(2,0)	4
baki	kichu notun na	

Final table:

2 1 0
3 2 1
4 3 2
Part 2: Binary search

lo = 0, hi = min(dist[0][0], dist[2][2]) = min(2, 2) = 2, ans = 0.

Round 1: k = 0 + (2 - 0)/2 = 1

canReach(1): dist[0][0] = 2 >= 1 ok. Cell >= 1 open, shudhu (0,2) block.
BFS: (0,0) → (1,0)(3) ✅ → (1,1)(2) ✅, (2,0)(4) ✅ → ... → (2,2) e pouchhai → true
ans = 1, lo = 2

Round 2: k = 2 + (2 - 2)/2 = 2

canReach(2): dist[0][0] = 2 >= 2 ok. Open cell: value >= 2, mane (0,0), (1,0), (1,1), (2,0), (2,1), (2,2).
Path (0,0) → (1,0) → (2,0) → (2,1) → (2,2). Shob >= 2 ✅ → true
ans = 2, lo = 3

Round 3: lo = 3 > hi = 2, loop shesh.

Return 2
*/


class Solution
{
public:
    // canReach: dist >= k wala cell diye (0,0) theke (n-1,n-1) e jaoa jay ki na
    // k = amra jante chai "safeness kompokkhe k" possible kina
    bool canReach(int k, vector<vector<int>>& dist, int n)
    {
        // shuru cell (0,0) er doori k er cheye choto hole shuru-i block, jaoa jabe na
        if(dist[0][0] < k)
            return false;

        // 4 dik er jonno: dr = row er poriborton, dc = col er poriborton
        // (-1,0)=upore, (1,0)=niche, (0,-1)=baam, (0,1)=dan
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        // visited[r][c] = true mane oi cell ekbar dekha hoyeche. shuru te shob false
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        // BFS er queue, cell (row, col) rakhbe
        queue<pair<int,int>> q;

        // shuru cell (0,0) ke visited kori
        visited[0][0] = true;
        // (0,0) ke queue te dhukai
        q.push({0, 0});

        // queue te cell thakle chalte thako
        while(!q.empty())
        {
            // queue er shamner cell er row ar col nai
            auto [r, c] = q.front();
            // oi cell queue theke ber kore dai (na dile infinite loop)
            q.pop();
            // shesh cell (n-1,n-1) e pouchhe gele jaoa possible, true
            if(r == n - 1 && c == n - 1)
                return true;
            // 4 dik e jaoar chesta kori
            for(int d = 0; d < 4; d++)
            {
                // notun cell er row
                int nr = r + dr[d];
                // notun cell er col
                int nc = c + dc[d];
                // 3 ta shorto: grid er bhitore, ager dekha na, ar doori >= k
                // (bounds age, noile out of bounds hobe)
                if(nr >= 0 && nr < n && nc >= 0 && nc < n
                   && !visited[nr][nc] && dist[nr][nc] >= k)
                {
                    // push korar somoy-i visited, jate ek cell duibar na dhuke
                    visited[nr][nc] = true;
                    // notun cell queue te dhukai
                    q.push({nr, nc});
                }
            }
        }
        // queue shesh, (n-1,n-1) e pouchhate pari ni
        return false;
    }

    int maximumSafenessFactor(vector<vector<int>>& grid)
    {
        // grid n x n, n = size
        int n = grid.size();
        // dist[r][c] = (r,c) cell theke sobcheye kachher chor er doori
        // -1 mane ekhono dekhini
        vector<vector<int>> dist(n, vector<int>(n, -1));
        // multi-source BFS er queue (shob chor ekshathe dhukbe)
        queue<pair<int,int>> q;
        // shob cell dekhi: row er upor loop
        for(int r = 0; r < n; r++)
        {
            // col er upor loop
            for(int c = 0; c < n; c++)
            {
                // cell e chor thakle
                if(grid[r][c] == 1)
                {
                    // chor nijei, tai doori 0
                    dist[r][c] = 0;
                    // chor ke queue te dhukai (BFS er shuru)
                    q.push({r, c});
                }
            }
        }
        // 4 dik array
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};
        // multi-source BFS: chor theke chhorie pore
        while(!q.empty())
        {
            // front cell nai
            auto [r, c] = q.front();
            // pop kori
            q.pop();
            // 4 dik e jai
            for(int d = 0; d < 4; d++)
            {
                // notun cell
                int nr = r + dr[d];
                int nc = c + dc[d];
                // grid er bhitore, ar ekhono dekhini (-1)
                if(nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == -1)
                {
                    // ager cell er doori + 1 (ek dhap dure)
                    dist[nr][nc] = dist[r][c] + 1;
                    // queue te dhukai
                    q.push({nr, nc});
                }
            }
        }
        // lo = kompokkhe 0 shobshomoy possible
        // hi = shuru ar shesh cell path e thakbei, tai duto-r choto ta-r beshi hobe na
        // ans = ekhon porjonto sobcheye boro possible k
        int lo = 0, hi = min(dist[0][0], dist[n - 1][n - 1]), ans = 0;
        // jotokkhon range e kichu baki
        while(lo <= hi)
        {
            // majher k
            int k = lo + (hi - lo) / 2;
            // k possible hole
            if(canReach(k, dist, n))
            {
                // k possible, ans e rakhi
                ans = k;
                // aro boro k try kori
                lo = k + 1;
            }
            else
            {
                // k possible na, tai choto k try kori
                hi = k - 1;
            }
        }
        // sobcheye boro possible k-i answer
        return ans;
    }
};
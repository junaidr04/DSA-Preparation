// Time: O(n² log n); n is the size of the grid, because we are using a priority queue to explore the grid, and in the worst case, we may need to explore all n² cells. Each insertion and extraction from the priority queue takes O(log n²) time, which simplifies to O(log n). Therefore, the overall time complexity is O(n² log n).
// Space: O(n²) (canReach shesh hole memory chhere dey, tai ekshathe ekta-i).


/*
Ekta n x n grid. Protyek cell e ekta number, eta oi cell er uchchota (elevation).

0 2
1 3
Shuru (0,0), shesh (n-1, n-1).
Somoy t er sathe jol er star t hoy. Tumi shudhu oi cell e dhukte paro jar elevation <= t.
Ek cell theke pashe cell e jete kono somoy lage na, shudhu dekho pashe cell er elevation <= t ki na.
Prosno: sobcheye choto t koto, jate (0,0) theke (n-1,n-1) e pouchhano jay?

Example: upore er grid.

t = 0: shudhu (0,0) open. Shesh cell 3, jawa jay na. ❌
t = 1: (0,0), (1,0) open. (1,1) er elevation 3, ❌
t = 2: (0,0), (1,0), (0,1) open. (1,1) ekhono 3, ❌
t = 3: shob open, pouchhano jay ✅

Tahole answer 3. Shesh cell-i 3, tai 3 er kom hote-i pare na.
Idea: t boro hole beshi cell open, pouchhano shohoj. Mane t possible hole t + 1 o possible. Ei “possible ❌❌❌✅✅✅” line er shuru-r ✅ khujte hobe, tai t er upor binary search, ar “possible kina” check BFS.


grid = [[0,2],[1,3]], n = 2

lo = 0, hi = 3, ans = 3.

Round 1: t = 0 + (3 - 0)/2 = 1

canReach(1): grid[0][0] = 0 <= 1 ok. Queue [(0,0)].
Pop (0,0): niche (1,0) elevation 1 <= 1 ✅ push. Dan (0,1) elevation 2 <= 1 ❌.
Pop (1,0): dan (1,1) elevation 3 <= 1 ❌. Upore (0,0) visited.
Queue khali → false
lo = 2

Round 2: t = 2 + (3 - 2)/2 = 2

canReach(2): (1,0) ✅, (0,1) ✅ (2 <= 2) push.
Pop (1,0): (1,1): 3 <= 2 ❌. Pop (0,1): (1,1) ❌.
Queue khali → false
lo = 3

Round 3: t = 3 + (3 - 3)/2 = 3

canReach(3): (1,0), (0,1) push. Pop (1,0): (1,1): 3 <= 3 ✅ push. Pop (0,1): (1,1) visited. Pop (1,1): r == n-1 && c == n-1 → true
ans = 3, hi = 2

lo = 3 > hi = 2, loop shesh. Return 3 ✅
*/


class Solution
{
public:
    // t somoy e shudhu grid[r][c] <= t wala cell diye
    // (0,0) theke (n-1,n-1) e jaoa jay ki na
    bool canReach(int t, vector<vector<int>>& grid, int n)
    {
        // table-er naam grid (dist na). shuru cell-i t er cheye uchu hole dhukte-i pari na
        if(grid[0][0] > t)
            return false;

        // 4 dik: upore, niche, baam, dan (dr = row poriborton, dc = col poriborton)
        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        // visited[r][c] = true mane oi cell ekbar dekha hoyeche, shuru te shob false
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        // BFS er queue
        queue<pair<int,int>> q;
        // shuru cell visited kore queue te dhukai
        visited[0][0] = true;
        q.push({0, 0});

        // queue te cell thakle chalte thako
        while(!q.empty())
        {
            // front cell nai, tarpor pop (pop bhulle infinite loop)
            auto [r, c] = q.front();
            q.pop();

            // shesh cell e pouchhe gele true (loop er bhitore)
            if(r == n - 1 && c == n - 1)
                return true;

            // 4 dik e jai
            for(int d = 0; d < 4; d++)
            {
                // notun cell er row ar col
                int nr = r + dr[d];
                int nc = c + dc[d];

                // FIX 2: bounds age, visited, tarpor elevation <= t
                // (grid, t, ar <=; dist/k/>= na)
                if(nr >= 0 && nr < n && nc >= 0 && nc < n
                   && !visited[nr][nc] && grid[nr][nc] <= t)
                {
                    // push korar somoy-i visited, noile ek cell onek bar dhukbe
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }

        // BFS shesh, shesh cell e pouchhate pari ni (loop er baire)
        return false;
    }

    int swimInWater(vector<vector<int>>& grid)
    {
        // grid n x n, n = size
        int n = grid.size();

        // lo = shuru cell er elevation er cheye kom t e kichu hoy-i na
        // hi = n*n-1 (shob elevation 0..n*n-1, tai ei somoy e shob cell open)
        // ans = ekhon porjonto sobcheye choto possible t
        int lo = grid[0][0], hi = n * n - 1, ans = hi;

        // jotokkhon range e kichu baki
        while(lo <= hi)
        {
            // variable er naam t (k na)
            int t = lo + (hi - lo) / 2;

            // t possible hole
            if(canReach(t, grid, n))
            {
                // ans e rakhi, aro choto t try (hi soray)
                ans = t;
                hi = t - 1;
            }
            else
            {
                // possible na, aro boro t lagbe (lo soray)
                lo = t + 1;
            }
        }
        return ans;
    }
};

// Problem: Longest Increasing Path in Matrix
// Platform: NeetCode
// Link:  https://neetcode.io/problems/longest-increasing-path-in-matrix
// time complexity: O(m × n); দুইটা nested loop — i যায় 1 থেকে m, j যায় 1 থেকে n.. প্রতিটা cell এ constant work
// space complexity: O(m × n); প্রতিটা cell এর জন্য একটি value store করতে হয়

/*
matrix =
9  9  4
6  6  8
2  1  1

r=3, c=3। আমরা (i,j) কে (row, col) হিসেবে ভাবি।

Loop order অনুযায়ী dfs call হবে: (0,0), (0,1), (0,2), (1,0), (1,1), (1,2), (2,0), (2,1), (2,2)
dfs(0,0) — value=9

Neighbors: up(invalid), down=(1,0)=6, left(invalid), right=(0,1)=9

6 > 9? না
9 > 9? না (equal, strictly না)
কোনো valid move নাই → best = 1
memo[0][0] = 1
dfs(0,1) — value=9

Neighbors: up(invalid), down=(1,1)=6, left=(0,0)=9, right=(0,2)=4

সবগুলাই ≤ 9 → কোনো valid move নাই → best = 1
memo[0][1] = 1
dfs(0,2) — value=4

Neighbors: up(invalid), down=(1,2)=8, left=(0,1)=9, right(invalid)

8 > 4? হ্যাঁ! → dfs(1,2) call করতে হবে (নিচে দেখি)

এখানে dfs(1,2) এ recursively যাই:

dfs(1,2) — value=8

Neighbors: up=(0,2)=4, down=(2,2)=1, left=(1,1)=6, right(invalid)

সবগুলাই ≤ 8 → কোনো valid move নাই → best = 1
memo[1][2] = 1

dfs(0,2) এ ফিরে আসি:

best = max(1, 1 + dfs(1,2)) = max(1, 1+1) = 2
memo[0][2] = 2
dfs(1,0) — value=6

Neighbors: up=(0,0)=9, down=(2,0)=2, left(invalid), right=(1,1)=6

9 > 6? হ্যাঁ! → dfs(0,0) (already memo তে আছে, memo[0][0]=1) → best = max(1, 1+1) = 2
2 > 6? না
6 > 6? না (equal)
memo[1][0] = 2
dfs(1,1) — value=6

Neighbors: up=(0,1)=9, down=(2,1)=1, left=(1,0)=6, right=(1,2)=8

9 > 6? হ্যাঁ! → dfs(0,1) (memo তে আছে, =1) → best = max(1, 1+1) = 2
1 > 6? না
6 > 6? না (equal)
8 > 6? হ্যাঁ! → dfs(1,2) (memo তে আছে, =1) → best = max(2, 1+1) = 2 (already 2, তাই থাকলো 2)
memo[1][1] = 2
dfs(1,2) — already computed! সরাসরি memo[1][2] = 1 return
dfs(2,0) — value=2

Neighbors: up=(1,0)=6, down(invalid), left(invalid), right=(2,1)=1

6 > 2? হ্যাঁ! → dfs(1,0) (memo তে আছে, =2) → best = max(1, 1+2) = 3
1 > 2? না
memo[2][0] = 3
dfs(2,1) — value=1

Neighbors: up=(1,1)=6, down(invalid), left=(2,0)=2, right=(2,2)=1

6 > 1? হ্যাঁ! → dfs(1,1) (memo তে আছে, =2) → best = max(1, 1+2) = 3
2 > 1? হ্যাঁ! → dfs(2,0) (memo তে আছে, =3) → best = max(3, 1+3) = 4
1 > 1? না (equal)
memo[2][1] = 4
dfs(2,2) — value=1

Neighbors: up=(1,2)=8, down(invalid), left=(2,1)=1, right(invalid)

8 > 1? হ্যাঁ! → dfs(1,2) (memo তে আছে, =1) → best = max(1, 1+1) = 2
1 > 1? না
memo[2][2] = 2
Final memo table
1  1  2
2  2  1
3  4  2
ans এ maximum নিচ্ছি

সবগুলার মধ্যে maximum = 4 (এইটা memo[2][1] থেকে আসছে)

Answer = 4

Verify করি — কোন path এ 4 length পাওয়া গেলো?

memo[2][1]=4 এর পেছনের path track করি: (2,1)=1 → (2,0)=2 (কারণ best update হয়েছিলো এইদিক থেকে, 1+3=4)
তারপর (2,0)=2 → (1,0)=6 (কারণ memo[2][0]=3 আসছে dfs(1,0) থেকে)
তারপর (1,0)=6 → (0,0)=9 (কারণ memo[1][0]=2 আসছে dfs(0,0) থেকে)

Path: 1 → 2 → 6 → 9, length = 4 ✓

matrix এ দেখো — (2,1)=1 → (2,0)=2 → (1,0)=6 → (0,0)=9, প্রতিটা move valid (adjacent এবং strictly increasing)। এইটাই সবচেয়ে লম্বা path।
*/

class Solution {
public:
    // dfs function: cell (i,j) theke shuru kore shobcheye lomba.. increasing path koto, seita ber kore
    // memo: 2D array, already compute kora cell er answer store rakhe.. current cell gula rkhbe i, j diye
    int dfs(int i, int j, vector<vector<int>>& matrix, vector<vector<int>>& memo)
    {
        int r = matrix.size(), c = matrix[0].size();

        // 4 direction: up, down, left, right..dx[] = row change, dy[] = column change
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        // ei cell er answer age compute kora hoye thakle, direct return (0 mane "ekhono compute hoyni", karon minimum answer shobshomoy 1)
        if(memo[i][j] != 0)
            return memo[i][j];
        int best = 1; // nijei ekta cell, minimum path length always 1
        for(int d = 0; d < 4; d++)
        {
            // current cell theke ei direction e gele kon cell e pouchabo
            int ni = i + dx[d], nj = j + dy[d];
            // boundary check: matrix er baire gele shei direction skip
            if(ni < 0 || ni >= r || nj < 0 || nj >= c)
                continue;
            // strictly increasing condition: neighbor er value current 
            // cell er cheye beshi hote hobe, tobei move kora jabe
            if(matrix[ni][nj] > matrix[i][j])
            {
                // valid move, tai oi neighbor theke shuru kora path + nijer cell (1) jog kore best update korlam
                best = max(best, 1 + dfs(ni, nj, matrix, memo));
            }
        }
        
        // ei cell er final answer memo te store, porerbar recompute na lagar jonno
        memo[i][j] = best;
        return best;
    }
    
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int r = matrix.size(), c = matrix[0].size();
        int ans = 0;
        // memo array banalam, shob 0 diye initialize (uncomputed marker)
        vector<vector<int>> memo(r, vector<int>(c, 0));
        
        // path je kono cell theke shuru hote pare, tai shob (i,j) cell 
        // theke dfs chalabo, tader moddhe maximum ta e final answer
        for(int i = 0; i < r; i++)
        {
            for(int j = 0; j < c; j++)
            {
                ans = max(ans, dfs(i, j, matrix, memo));
            }
        }
        return ans;
    }
};
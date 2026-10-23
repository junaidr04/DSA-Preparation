// time complexity: O(m*n) where m is the number of rows and n is the number of columns in the grid, as we need to visit each cell once in the worst case
// space complexity: O(m*n) for the two boolean matrices to track reachable cells from each ocean


class Solution
{
    // ei DFS "উল্টো দিকে" hato — ocean theke shুরু kore উঁচুর দিকে যায়
    // (normal e pani উঁচু theke নিচুতে বহে, kintu amra উল্টো দিক থেকে ভাবছি:
    //  "ocean theke কোথায় কোথায় পৌঁছানো যায়" — তাই condition ta উল্টো)
    void dfs(vector<vector<int>> &heights, vector<vector<bool>> &visited, int i, int j, int prevHeight)
    {
        int r = heights.size(), c = heights[0].size();
        // bounds বাইরে গেলে return
        if (i < 0 || i >= r || j < 0 || j >= c)
            return;
        // already visited hole return (আবার visit korার দরকার নাই)
        if (visited[i][j])
            return;
        // height condition: current cell আগের cell এর থেকে খাটো (কম উচ্চতা) হলে যাওয়া যাবে না
        // (কারণ উল্টো দিকে হাঁটছি, শুধু সমান বা বেশি উচ্চতায় যেতে পারবো)
        if (heights[i][j] < prevHeight)
            return;
        visited[i][j] = true; // ei cell theke ocean e pani পৌঁছাতে পারে, mark kore dilam
        // 4 direction e dfs call koro, current height ta porer call er prevHeight hবে
        dfs(heights, visited, i + 1, j, heights[i][j]);
        dfs(heights, visited, i - 1, j, heights[i][j]);
        dfs(heights, visited, i, j + 1, heights[i][j]);
        dfs(heights, visited, i, j - 1, heights[i][j]);
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>> &heights)
    {
        int r = heights.size(), c = heights[0].size();
        vector<vector<bool>> paci(r, vector<bool>(c, false)); // pacific e কারা কারা পৌঁছাতে পারে
        vector<vector<bool>> atla(r, vector<bool>(c, false)); // atlantic e কারা কারা পৌঁছাতে পারে
        // top row + bottom row theke dfs shুরু (multi-source)
        // INT_MIN diye shuru korছি — jাতে প্রথম cell টা কখনোই "height কম" বলে বাদ না যায়
        for (int j = 0; j < c; j++)
        {
            dfs(heights, paci, 0, j, INT_MIN);     // top row -> pacific
            dfs(heights, atla, r - 1, j, INT_MIN); // bottom row -> atlantic
        }
        // left column + right column theke dfs shুরু
        for (int i = 0; i < r; i++)
        {
            dfs(heights, paci, i, 0, INT_MIN);     // left column -> pacific
            dfs(heights, atla, i, c - 1, INT_MIN); // right column -> atlantic
        }
        // jekhane duটা ocean e-i pani পৌঁছাতে পারে (mane duটা visited grid e-i true),
        // shei cell ta answer e push kori
        vector<vector<int>> ans;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (paci[i][j] && atla[i][j])
                {
                    ans.push_back({i, j});
                }
            }
        }
        return ans;
    }
};

/*
Ocean গুলা কোথায় touch করে সেটা প্রথমে বুঝি:
         Pacific (উপরে ar বামে touch kore)
              ↓  ↓  ↓
Pacific →   1   2   2
Pacific →   3   2   3
Pacific →   2   4   5   ← Atlantic
                     ↑
                 Atlantic (নিচে ar ডানে touch kore)
Pacific Ocean touch kore: top row (row0: 1,2,2) ar left column (col0: 1,3,2)
Atlantic Ocean touch kore: bottom row (row2: 2,4,5) ar right column (col2: 2,3,5)
Pani কিভাবে বহে — rule মনে করি:

Pani উঁচু থেকে নিচু বা সমান উচ্চতায় যেতে পারে। Mane height[current] >= height[neighbor] hলে pani current cell theke neighbor e যেতে পারবে।

Ekটা specific cell dিয়ে check kori — (1,1) = 2 (মাঝখানের cell)

প্রশ্ন: এই cell থেকে pani কি Pacific এ পৌঁছাতে পারে?

Pani (1,1)=2 theke যেতে পারে যেসব neighbor এ যাদের height <= 2:

Left (1,0)=3 → 3 > 2, না, যেতে পারবে না এদিকে (কারণ pani উঁচুতে উঠতে পারে না)
Up (0,1)=2 → 2 <= 2, হ্যাঁ যেতে পারবে, ar (0,1) তো top row, mane সরাসরি Pacific! ✅

তাহলে (1,1) theke pani Pacific এ পৌঁছাতে পারে (via (0,1))।

এখন Atlantic এ পৌঁছাতে পারে কিনা check kori:

Down (2,1)=4 → 4 > 2, যেতে পারবে না
Right (1,2)=3 → 3 > 2, যেতে পারবে না

Hmm, direct neighbor দিয়ে Atlantic এ পৌঁছানো যাচ্ছে না এই মুহূর্তে (কারণ charপাশের সবাই উঁচু)। তাহলে (1,1) শুধু Pacific এ পৌঁছাতে পারে, Atlantic এ না — তাই এই cell answer এ থাকবে না (দুইটাতেই পৌঁছানো লাগবে)।

Answer কি format এ চাওয়া হয়:

Output hবে একটা list of coordinates — যেসব [row, col] cell থেকে pani উভয় ocean এই পৌঁছাতে পারে।

Output: [[0,0], [0,1], [1,0], [2,1], [1,2], ...] (example, exact answer trace korলে বের হবে)
Ekটা সহজ intuition — corner cell গুলা দিয়ে বুঝি:
(0,0)=1 — top-left corner। এইটা তো সরাসরি Pacific এর সাথে touch kore (top row + left column দুটোতেই আছে)। তাহলে Pacific এ তো পৌঁছাবেই। Atlantic এ পৌঁছাতে হলে নিচে/ডানে যেতে হবে — কিন্তু (0,0)=1 সবচেয়ে নিচু, তাই charপাশের সবার height বেশি, pani কোথাও উঠতে পারবে না — Atlantic এ পৌঁছাতে পারবে না।
(2,2)=5 — bottom-right corner, সবচেয়ে উঁচু। এইটা তো Atlantic এর সাথে সরাসরি touch kore। Pacific এর দিকে যেতে পারবে কিনা — যেহেতু এটাই সবচেয়ে উঁচু, charপাশের সবাই এর চেয়ে নিচু বা সমান, তাই pani যেকোনো দিকে যেতে পারবে, ar ধাপে ধাপে Pacific পর্যন্তও পৌঁছাতে পারবে। তাই (2,2) উভয় ocean এই পৌঁছাতে পারে — এটা answer এ থাকবে।
সারমর্ম — কি বের করতে হবে:

প্রতিটা cell এর জন্য চেক করতে হবে — সেই cell থেকে (উঁচু থেকে নিচুর দিকে পানি বইয়ে) Pacific এ পৌঁছানো যায় কিনা, আর Atlantic এ পৌঁছানো যায় কিনা। দুটোই "হ্যাঁ" হলে সেই cell এর coordinate answer list এ যাবে।
*/
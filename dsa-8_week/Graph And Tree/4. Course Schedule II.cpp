// time complexity: O(V + E) where V is the number of courses and E is the number of prerequisites
// space complexity: O(V + E) for the adjacency list and state array


class Solution
{
    // dfs function ta bujhায় "ei node theke shuru kore cycle ache kina" (hasCycle check)
    // true return korle mane cycle paওয়া গেছে (bad)
    // false return korle mane cycle nai, safe (good)
    bool dfs(int node, vector<vector<int>> &adj, vector<int> &state, vector<int> &ans)
    {
        // state[node] == 1 mane node ta ekhon current DFS path e "active" ache (in-progress)
        // abar shei active node e ফিরে এলে mane ghure ghure nijer kache ফিরে এসেছি -> cycle!
        if (state[node] == 1)
            return true; // cycle found
        // state[node] == 2 mane node ta already অন্য কোনো path theke fully process হয়ে গেছে
        // eta cycle na, shudhu shared dependency, তাই abar process korার দরকার নাই
        if (state[node] == 2)
            return false; // no cycle from this node, already done
        // node ta ekhon "in-progress" mark koro (current recursion stack e active)
        state[node] = 1;
        // ei node er shob dependency (neighbor) explore koro
        for (int neigh : adj[node])
        {
            // jodi kono neighbor theke cycle paওয়া যায়, shathe shathe true propagate koro উপরে
            if (dfs(neigh, adj, state, ans))
            {
                return true;
            }
        }
        // ei point e pouche gele mane node er shob dependency safely process hয়ে গেছে
        // tai eke "fully done" mark koro
        state[node] = 2;
        // node ta ans vector e push koro -- eituku IMPORTANT:
        // eta push hচ্ছে TOKHON, jokhon tar shob dependency already push হয়ে গেছে
        // tার mane push hওয়ার order টাই automatically "dependency-first" (correct) order
        ans.push_back(node);
        // ei node theke kono cycle paওয়া jায়নি
        return false;
    }

public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        // adjacency list banাচ্ছি: adj[a] e ache shob course jegulo 'a' er dependency
        // [a, b] mane 'a' nite hole 'b' age lagবে, tai adj[a] te 'b' push kori
        vector<vector<int>> adj(numCourses);
        // state array: 0 = unvisited, 1 = in-progress, 2 = fully processed
        vector<int> state(numCourses, 0);
        // adjacency list build kora hচ্ছে prerequisites theke
        for (auto &p : prerequisites)
        {
            int a = p[0], b = p[1];
            adj[a].push_back(b);
        }
        // result (topological order) rakhar jonno vector
        vector<int> ans;
        // প্রতিটা course er jonno dfs call koro, jodি already visited na hoy
        // (graph disconnected hote pare, tai sob node theke try korte hobe)
        for (int i = 0; i < numCourses; i++)
        {
            if (state[i] != 2) // mane fully process হয়নি এখনো
            {
                if (dfs(i, adj, state, ans))
                {
                    // dfs true return korle mane cycle পাওয়া গেছে
                    // cycle থাকলে valid order possible na, tai empty vector return koro
                    return {};
                }
            }
        }
        // sob course safely process হয়ে গেছে, kono cycle nai
        // ans vector e already valid dependency-first order ache (reverse lagbe na,
        // karon adjacency ta 'a -> dependency' direction e banano ছিল)
        return ans;
    }
};




// Another approach


// Time: O(V + E), V = numCourses, E = prerequisites.size(). Graph toiri O(E), prottek course ekbar queue e dhuke ber hoy O(V), ar prottek edge ekbar-i dekha hoy O(E).
// Space: O(V + E). adj e O(V + E), indegree ar queue ar ans e O(V). Recursion nei, tai stack overflow er bhoy nei.

class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
    {
        // adj[x] = x korar por je course gulo korte parbe
        vector<vector<int>> adj(numCourses);
        // indegree[x] = x nite ekhono koyta prerequisite baki
        vector<int> indegree(numCourses, 0);
        // graph toiri: [a, b] mane a korte hole age b, tai edge b -> a
        for (auto& p : prerequisites)
        {
            int a = p[0], b = p[1];
            adj[b].push_back(a);   // b er por a
            indegree[a]++;         // a er ekta prerequisite barlo
        }
        // final order ekhane jomabe
        vector<int> ans;
        // queue te thakbe oi course gulo jader ekhoni nite pari (indegree == 0)
        queue<int> q;
        // jader kono prerequisite nei, tader prothome queue te rakhlam
        for (int i = 0; i < numCourses; i++)
        {
            if (indegree[i] == 0)
                q.push(i);
        }
        // jotokkhon nite pari emon course ache, ghurbo
        // (level gonar dorkar nei, karon amra minute gunchi na, shudhu order chai)
        while (!q.empty())
        {
            // samner course ta nilam
            int cur = q.front();
            q.pop();
            // order e rakhlam
            ans.push_back(cur);
            // cur shesh, tai cur er por je course gulo opekkha korchilo tader prerequisite ekta kombe
            for (int next : adj[cur])
            {
                indegree[next]--;
                // shob prerequisite shesh hole ei course ekhon nite pari
                if (indegree[next] == 0)
                    q.push(next);
            }
        }
        // shob course order e ashle valid, na hole cycle ache (jemon [[0,1],[1,0]]), tai khali list
        if ((int)ans.size() == numCourses)
            return ans;
        return {};
    }
};
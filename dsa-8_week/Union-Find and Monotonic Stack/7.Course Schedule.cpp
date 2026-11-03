// Time: O(V + E), protyek node ar edge ekbar-i dekha hoy (state 2 hole abar dhuke na).
// Space: O(V + E) adj list er jonno, ar recursion stack O(V) worst case.

class Solution
{
public:
    // node theke DFS chalabe. cycle paile true return korbe.
    // state[node]: 0 = dekhini, 1 = ekhon path e ache, 2 = shesh
    bool dfs(int node, vector<vector<int>> &adj, vector<int> &state)
    {
        // ekhon-i path e thaka node abar pelam, mane cycle, tai true
        if (state[node] == 1)
            return true;
        // ager-i pura check kora, cycle nei, tai false
        if (state[node] == 2)
            return false;
        // ei node e dhukchi, tai state = 1 (ekhon path e ache)
        state[node] = 1;
        // protyek neighbor e DFS chalai
        for (int neigh : adj[node])
        {
            // neighbor er niche cycle pele sathe sathe true return
            // (false return korbo na, karon baki neighbor dekha dorkar)
            if (dfs(neigh, adj, state))
                return true;
        }
        // shob neighbor dekhlam, cycle pai ni, tai state = 2 (shesh)
        state[node] = 2;
        // ei node theke cycle nei
        return false;
    }

    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        // adj: protyek course er jonno khali list, state: shobai 0 (dekhini)
        vector<vector<int>> adj(numCourses);
        vector<int> state(numCourses, 0);
        // protyek pair [a, b]: b age, a pore, tai edge b -> a
        for (auto &pre : prerequisites)
        {
            int a = pre[0], b = pre[1];
            adj[b].push_back(a); // FIX 1: a (int) push, adj[a] na
        }
        // graph disconnected hote pare, tai shob course theke try kori
        for (int i = 0; i < numCourses; i++)
        {
            // ekhono dekhini emon node theke-i DFS shuru
            if (state[i] == 0)
            {
                // FIX 2: dfs true = cycle ache, tai false return
                if (dfs(i, adj, state))
                {
                    return false;
                }
            }
        }
        // kono cycle pai ni, shob course shesh kora jabe
        return true;
    }
};
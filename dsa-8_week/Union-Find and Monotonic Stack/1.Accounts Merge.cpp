// TC: O(K log K). Union-find part e O(K · α(N)), kintu set insert ar sorting e log K ashe, seta-i dominate kore.
// SC: O(K). Map, set, ar output.


class DSU {
public:
    vector<int> parent, size;
    // Constructor: prottek account er nijer parent initialize korbo
    DSU(int n) 
    {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) 
        {
            parent[i] = i;
        }
    }
    // Find: kono node er ultimate parent/root ber korbo
    int find(int node) 
    {
        // Jodi node nijei tar parent hoy, tahole etai root
        if (parent[node] == node) 
        {
            return node;
        }
        // Path Compression:
        // Directly root er shathe connect kore dibo
        return parent[node] = find(parent[node]);
    }
    // Unite: duita account ke same group e connect korbo
    void unite(int u, int v) 
    {
        // Duita node er root ber korbo
        u = find(u);
        v = find(v);
        // Jodi already same group e thake, kichu korar nai
        if (u == v) 
        {
            return;
        }
        // Union by Size:
        // Choto group ke boro group er shathe connect korbo
        if (size[u] < size[v]) 
        {
            swap(u, v);
        }
        // v er root ke u er root er child banabo
        parent[v] = u;
        // Group er size update korbo
        size[u] += size[v];
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        // Step 1: Total account count
        int n = accounts.size();
        // Prottek account ke ekta DSU node hisebe consider korbo
        DSU dsu(n);
        // Email -> kon account e prothom paoa geche
        unordered_map<string, int> emailToAcc;

        // STEP 1: SAME EMAIL THAKLE ACCOUNTS UNITE

        for (int i = 0; i < n; i++) 
        {
            // Index 0 te name thake, tai email shuru index 1 theke
            for (int j = 1; j < accounts[i].size(); j++) 
            {
                string& email = accounts[i][j];
                // Jodi email age thekei map e thake
                if (emailToAcc.count(email)) 
                {
                    // Previous account er shathe current account unite korbo
                    dsu.unite(emailToAcc[email], i);
                }
                else 
                {
                    // First time email ta paoa gele map e store korbo
                    emailToAcc[email] = i;
                }
            }
        }

        // STEP 2: ROOT ONUSARE EMAIL GROUP KORBO

        // Root -> oi group er shob email store korbo
        // Set automatically duplicate remove kore + sorted rakhe
        unordered_map<int, set<string>> groups;
        for (int i = 0; i < n; i++) 
        {
            // Current account er ultimate root ber korbo, i kon group e, tar root
            int root = dsu.find(i);
            // Current account er shob email traverse korbo
            for (int j = 1; j < accounts[i].size(); j++) 
            {
                // Root er group e email insert korbo
                groups[root].insert(accounts[i][j]);
            }
        }

        // STEP 3: FINAL ANSWER BUILD KORBO

        vector<vector<string>> ans;
        // Prottek group traverse korbo.. emails = oi root er set<string>
        for (auto& [root, emails] : groups) 
        {
            vector<string> merged;
            // Group er account er name prothome add korbo
            merged.push_back(accounts[root][0]);
            // Set theke shob sorted email vector e add korbo..set er naam "emails", ar element const tai const string&
            for (const string& email : emails) 
            {
                merged.push_back(email);
            }
            // Complete merged account answer e add korbo
            ans.push_back(merged);
        }
        return ans;
    }
};
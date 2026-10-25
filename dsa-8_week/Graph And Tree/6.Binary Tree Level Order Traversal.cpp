// Time: O(n), n = tree er node songkha. Prottek node ekbar queue te dhuke, ekbar ber hoy, ar ber hole O(1) kaj (value rakha, duto child dekha). Mot kaj O(n).
// Space: O(n). Queue te worst case ek shathe ek puro stor thake. Perfect binary tree te shesh stor e prai n/2 ta node, tai O(n). Output ans e shob node-i thake, seta-o O(n).

class Solution
{
public:
    vector<vector<int>> levelOrder(TreeNode* root)
    {
        // answer: prottek stor er value gulo alada alada list e
        vector<vector<int>> ans;
        // tree khali hole khali [] ferot (age check, tahole NULL queue te dhukbe na)
        if (root == NULL)
            return ans;
        // queue te tree node er pointer thakbe, BFS er shuru ekhan theke
        queue<TreeNode*> q;
        q.push(root);   // shuru te shudhu root
        // jotokkhon queue te node ache, ghurbo (ek iteration = ek stor)
        while (!q.empty())
        {
            // ei stor e koyta node ache; for er AGE nilam
            // karon for er bhitore child dhukbe, q.size() bodle jabe
            int n = q.size();
            // ei stor er value gulo ekhane jomabe
            vector<int> level;
            // ei stor er sz ta node-i process korbo, bam theke dan
            for (int i = 0; i < n; i++)
            {
                // queue theke samner node nilam
                TreeNode* curr = q.front();
                q.pop();
                // ei node er value ei stor e rakhlam
                level.push_back(curr->val);
                // bam child thakle queue te rakhlam (porer stor e jabe)
                if (curr->left)
                    q.push(curr->left);
                // dan child thakle queue te rakhlam
                if (curr->right)
                    q.push(curr->right);
            }
            // ek stor shesh, tai ei stor er list ta ans e rakhlam (for er BAIRE)
            ans.push_back(level);
        }
        return ans;
    }
};
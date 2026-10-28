/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec
{
public:
    string serialize(TreeNode *root)
    {
        // empty tree hole khali string
        if (!root)
            return "";
        string ans;
        queue<TreeNode *> q;
        q.push(root); // BFS root theke shuru
        while (!q.empty())
        {
            TreeNode *curr = q.front(); // shamner node nilam
            q.pop();
            if (curr == NULL)
            {
                ans += "N,"; // null hole "N" likhlam
                // null er child nei, tai kichu push korbo na (korle crash)
            }
            else
            {
                ans += to_string(curr->val) + ","; // value + ',' separator (12 ar 1,2 alada chena jabe)
                q.push(curr->left);                // bam child, null hole o push (jate "N" likha hoy)
                q.push(curr->right);               // dan child, null hole o push
            }
        }
        return ans; // loop er baire
    }

    TreeNode *deserialize(string data)
    {
        // serialize e empty tree er jonno "" diyechhilam
        if (data.empty())
            return NULL;
        stringstream ss(data);
        string token;
        getline(ss, token, ','); // prothom token = root er value
        TreeNode *root = new TreeNode(stoi(token));
        queue<TreeNode *> q;
        q.push(root); // root er child gulo porer token e ache
        while (!q.empty())
        {
            TreeNode *curr = q.front(); // je node er child jurbo
            q.pop();

            // bam child: porer token pori
            getline(ss, token, ',');
            if (token != "N") // "N" na hole asol node
            {
                curr->left = new TreeNode(stoi(token));
                q.push(curr->left); // ei node er child o pore jurte hobe, tai queue te
            }

            // dan child: notun token pori (alada if, karon dan er token alada)
            getline(ss, token, ',');
            if (token != "N")
            {
                curr->right = new TreeNode(stoi(token));
                q.push(curr->right);
            }
        }
        return root; // loop er baire
    }
};
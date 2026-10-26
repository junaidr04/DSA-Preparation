// Time: O(n) — prottek node ekbar check kori.
// Space: O(h) — recursion stack; ekhane h holo tree-r height.


class Solution
{
    // Prottek node-er value minVal ar maxVal er moddhe ache kina check korbe
    bool check(TreeNode* root, long minVal, long maxVal)
    {
        // Node NULL hole, ei branch valid
        if(root == NULL)
            return true;

        // Node-er value allowed range-er baire hole BST valid na
        if(root->val <= minVal || root->val >= maxVal)
            return false;

        // Left subtree-r sob value root->val er cheye choto hote hobe
        // Tai left subtree-r maximum value hobe root->val
        return check(root->left, minVal, root->val) &&

               // Right subtree-r sob value root->val er cheye boro hote hobe
               // Tai right subtree-r minimum value hobe root->val
               check(root->right, root->val, maxVal);
    }

public:
    bool isValidBST(TreeNode* root)
    {
        // Shurute kono minimum ba maximum limit nai
        // Tai LONG_MIN theke LONG_MAX range diye check shuru
        return check(root, LONG_MIN, LONG_MAX);
    }
};

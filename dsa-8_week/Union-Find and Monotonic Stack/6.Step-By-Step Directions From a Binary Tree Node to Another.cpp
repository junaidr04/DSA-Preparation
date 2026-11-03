// Time: O(n), findPath duibar, protyek bar worst case shob node dekhe.
// Space: O(h), recursion stack + path string. Skewed tree te h = n, tai worst case O(n).


class Solution
{
public:
    // root theke target node porjonto path ('L'/'R') banay.
    // path paile true, na paile false return kore.
    bool findPath(TreeNode* node, int target, string& path)
    {
        // node nei (nullptr) mane ei dike target nei, tai false
        if(node == NULL)
            return false;
        // target node pelam, path ta ekhane shesh, tai true
        // (path e kichu push kori ni, karon ei node e ei pouchhechi)
        if(node->val == target)
            return true;
        // left e jaoar ager 'L' likhe rakhi
        path.push_back('L');
        // left subtree te target pele sathe sathe true return,
        // path ta rekhe dibo (pop korbo na)
        if(findPath(node->left, target, path))
            return true;
        // left e pailam na, tai backtrack: 'L' ta ber kore dai
        path.pop_back();
        // ekhon right e jaoar jonno 'R' likhi
        path.push_back('R');
        // right subtree te pele true return
        if(findPath(node->right, target, path))
            return true;
        // right e o pailam na, 'R' ta ber kore dai
        path.pop_back();
        // duto dike-i nei, tai ei node er niche target nei
        return false;
    }

    string getDirections(TreeNode* root, int startValue, int destValue)
    {
        // root theke start ar root theke dest er path rakhar string
        string toStart, toDest;
        // duto path ber kori (reference diye pass, tai string duto vore jabe)
        findPath(root, startValue, toStart);
        findPath(root, destValue, toDest);
        // common prefix er length: duto path jotokkhon same dike gelo,
        // totokkhon root theke LCA porjonto ek-i path
        int i = 0;
        // size check age, noile out of bounds hobe
        while(i < toStart.size() && i < toDest.size() && toStart[i] == toDest[i])
        {
            i++;   // pore character o same, tai ek dhap egilam
        }
        // answer string, shuru te empty
        string ans;
        // start theke LCA te jete koyta dhap upore uthbo
        // = toStart er common prefix bade baki character
        int upCount = toStart.size() - i;
        // protyek dhap er jonno ekta 'U'
        for(int j = 0; j < upCount; j++)
        {
            ans += 'U';
        }
        // LCA theke dest e namar path = toDest er common prefix er por theke baki
        ans += toDest.substr(i);
        return ans;
    }
};
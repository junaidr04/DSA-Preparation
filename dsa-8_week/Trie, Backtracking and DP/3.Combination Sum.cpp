// Time: O(N^(T/M)), N = candidates songkha, T = target, M = sobcheye chhoto candidate. Recursion tree er gobhirota max T/M, prottek level e max N branch.
// Space: O(T/M) recursion stack + path (output bad diye).


/*
Dry run ([2,3,6,7], target = 7):

dfs(7, start=0): i=0, 2 choose, path=[2], target=5.
dfs(5, start=0): 2 choose, path=[2,2], target=3.
dfs(3, start=0): 2 choose, path=[2,2,2], target=1. dfs(1): 2 choose, target=-1, return. Pop. 3 choose, target=-2, return. Sob dike beshi, return.
Pop 2, i=1: 3 choose, path=[2,2,3], target=0. result = [[2,2,3]].
Backtrack kore [2] e ferot, 3 choose: [2,3], target=2. 2 hole [2,3,2] hoto, kintu start=1 tai 2 abar ashe na. 3, 6, 7 e beshi, dead end.
Root e ferot, 3, 6 e dead end. 7 choose, path=[7], target=0. result = [[2,2,3],[7]].  
*/

class Solution
{
public:
    void dfs(vector<int>& candidates, int target, int start, vector<int>& path, vector<vector<int>>& ans)
    {
        if(target == 0)                           // target 0 mane path er jog fol thik target
        {
            ans.push_back(path);               // path ta ekta answer, result e copy kore rakho (FIX: ager bar 'ans' chhilo)
            return;                               // ar egiye lav nai, ekhanei thamo
        }
        if(target < 0)                            // beshi hoye gelo
            return;                               // ei path e answer nai, ferot jao
        for (int i = start; i < candidates.size(); i++)   // start theke shuru, tai ager index e ferot jai na (duplicate rodh)
        {
            path.push_back(candidates[i]);        // choose, candidates[i] ke path e rakho
            // explore. target komlo, start = i (ek-i number abar nite pari)
            // ager bar argument er order ulta chhilo ar 'result' miss chhilo
            dfs(candidates, target - candidates[i], i, path, result);
            path.pop_back();                      // un-choose, backtrack. Ager 'board[r][c] = ch' er moto, noile path e ager element theke jabe
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target)
    {
        vector<vector<int>> ans;               // sob combination ekhane
        vector<int> path;                         // ekhon porjonto choose kora number gulo
        dfs(candidates, target, 0, path, ans); // start = 0, FIX: ager bar argument order ar 'result' chhilo
        return ans;                            // ekhon result e dfs er answer ache
    }
};
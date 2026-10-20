// Time: O(n log n); sort-i dominant, tarpor ek pass O(n)
// Space: O(n); ans (sort bade extra space), sort er internal space alada

/*  
Dry run 1: [[1,3],[2,6],[8,10],[15,18]]

Sort er por same thake (already start er order e).

cur	        ans faka / ans.back()[1] < cur[0]?	Kon branch	            ans er por
[1,3]	    ans faka	                        push	                [[1,3]]
[2,6]	    3 < 2? na	                        merge: max(3, 6) = 6	[[1,6]]
[8,10]	    6 < 8? ha	                        push	                [[1,6],[8,10]]
[15,18]	    10 < 15? ha	                        push	                [[1,6],[8,10],[15,18]]

Final = [[1,6],[8,10],[15,18]]. Sothik.

Dry run 2 (touch case): [[1,4],[4,5]]
cur	    Condition	Branch	                ans
[1,4]	ans faka	push	                [[1,4]]
[4,5]	4 < 4? na	merge: max(4, 5) = 5	[[1,5]]

Final = [[1,5]]. Touch korle merge hoy, < (strict) er karone.

Dry run 3 (bhitore thaka): [[1,10],[2,5]]
cur	    Condition	Branch	                ans
[1,10]	ans faka	push	                [[1,10]]
[2,5]	10 < 2? na	merge: max(10, 5) = 10	[[1,10]]

Final = [[1,10]]. min dile 5 hoye jeto, tai max lage.
*/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // start er upor base kore sort, tahole overlap hole shudhu ager merged interval er sathe check korlei hobe
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> ans;   // merged interval gulo
        for (auto& cur : intervals)
        {
            // ans faka hole ba ager merged interval er end < cur er start,
            // mane majhkhane fanka ache, overlap nai -> notun interval hisebe push
            // NOTE: '<' (strict), tai [1,4] ar [4,5] touch korle merge hoy
            if (ans.empty() || ans.back()[1] < cur[0])
            {
                ans.push_back(cur);   // puro interval push (cur[0] na)
            }
            else
            {
                // overlap kore -> ager interval er end baraw
                // max keno: [1,10] ar [2,5] e end 10-i thakbe, min dile 5 hoye bhul hobe
                ans.back()[1] = max(ans.back()[1], cur[1]);
            }
        }
        return ans;
    }
};

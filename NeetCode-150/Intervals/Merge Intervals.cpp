// Problem: Merge Intervals
// Platform: NeetCode
// Link: https://neetcode.io/problems/merge-intervals
// time complexity: O(n) - Array-ta ekbar matro traverse kora hoy
// space complexity: O(n) - Result array create kora hoy

/*
Example Calculation
intervals = [[3,5],[1,2],[6,9],[8,10],[15,18]]

Step 1 — Sort: (start onujayi sort hobe)

Before: [[3,5],[1,2],[6,9],[8,10],[15,18]]
After:  [[1,2],[3,5],[6,9],[8,10],[15,18]]

Step 2 — Loop trace (ans khali diye shuru):

curr	ans.empty()?	curr[0] > ans.back()[1]?	    Action	        ans after
[1,2]	true	        — (empty check e already true)	push [1,2]	    [[1,2]]
[3,5]	false	        3 > 2? hae	                    push [3,5]	[[1,2],[3,5]]
[6,9]	false	        6 > 5? hae	                    push [6,9]	[[1,2],[3,5],[6,9]]
[8,10]	false	        8 > 9? na	                    merge: ans.back()[1] = max(9,10) = 10	[[1,2],[3,5],[6,10]]
[15,18]	false	        15 > 10? hae	                push [15,18]	[[1,2],[3,5],[6,10],[15,18]]

Final Output:

[[1,2],[3,5],[6,10],[15,18]]
*/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> ans; // merge kora result rakhar jonno empty vector
        // sort kora hocche start time onujayi (default sort intervals-er
        // 0-index, mane start, diye age compare kore)
        sort(intervals.begin(), intervals.end());
        // sorted intervals gulor upor loop chalano hocche ekta ekta kore
        for (auto& curr : intervals)
        {
            // check kora hocche: ans khali kina, OTHOBA
            // current interval-er start, ans-er shesh interval-er end
            // theke boro kina (mane overlap nai)
            if (ans.empty() || curr[0] > ans.back()[1])
            {
                // overlap nai, tai notun interval hishebe push kore dao
                ans.push_back(curr);
            }
            else
            {
                // overlap ache, tai merge korte hobe
                // ans-er last interval-er end ke boro kore dao jodi
                // current interval-er end tar theke boro hoy
                ans.back()[1] = max(ans.back()[1], curr[1]);
            }
        }
        return ans; // merge kora shob interval return kore dao
    }
};
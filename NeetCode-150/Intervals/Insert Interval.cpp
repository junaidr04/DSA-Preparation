// Problem: Insert Interval
// Platform: NeetCode
// Link: https://neetcode.io/problems/insert-new-interval/question
// time complexity: O(n) - Array-ta ekbar matro traverse kora hoy
// space complexity: O(n) - Result array create kora hoy

/*
Example
intervals = [[1,3],[4,7],[9,12],[15,18]]
newInterval = [5,10]
Start kori: i = 0, n = 4, ans = []

Phase 1: age-r intervals (no overlap)
Condition: intervals[i][1] < newInterval[0] → intervals[i][1] < 5

i	intervals[i]	end	    end < 5?	Action
0	[1,3]	        3	    3 < 5 ✓	    push [1,3], i→1
1	[4,7]	        7	    7 < 5 ✗	    loop stop

Loop shesh: i = 1, ans = [[1,3]]

Phase 2: overlap merge
Condition: intervals[i][0] <= newInterval[1] → intervals[i][0] <= 10

i	intervals[i]	start	start<=10?	newInterval update
1	[4,7]	        4	    4<=10 ✓	    start=min(5,4)=4, end=max(10,7)=10 → newInterval=[4,10]
2	[9,12]	        9	    9<=10 ✓	    start=min(4,9)=4, end=max(10,12)=12 → newInterval=[4,12]
3	[15,18]	        15	    15<=10 ✗	loop stop

Loop shesh: i = 3, newInterval = [4,12]

Merged interval push kori: ans = [[1,3],[4,12]]

Phase 3: baki intervals
i	Action
3	push [15,18], i→4
4	i==n, loop stop

Final: ans = [[1,3],[4,12],[15,18]]

Result
Output: [[1,3],[4,12],[15,18]]

Bhalo kore lokkho koro: [4,7], [9,10] (newInterval-er original range), ar [9,12] — teen-ta interval mile ekta continuous [4,12] hoye geche, karon eder moddhe gap nai — shob e connect kore ache.
*/

class Solution
{
public:
    vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
    {
        int i = 0, n = intervals.size();
        vector<vector<int>> ans;
        // Phase 1: newInterval er aage jegulo ache (kono overlap nai)
        // condition: current interval er end, newInterval er start er theke choto hole
        // overlap kora shomvob na, tai shoja push kore dao
        while (i < n && intervals[i][1] < newInterval[0])
        {
            ans.push_back(intervals[i++]);
        }
        // Phase 2: overlap kora shob interval ke merge kore newInterval boro kora
        // condition: <= use korte hobe, karon touch kora intervals (end == start)
        // o overlap hishebe dhora hoy, merge korte hobe
        while (i < n && intervals[i][0] <= newInterval[1])
        {
            newInterval[0] = min(newInterval[0], intervals[i][0]); // start choto ta rakho
            newInterval[1] = max(newInterval[1], intervals[i][1]); // end boro ta rakho
            i++;
        }
        // merge shesh, ekbar e merged newInterval ta push kore dao
        ans.push_back(newInterval);
        // Phase 3: baki jegulo overlap kore nai (pore ache), shoja push koro
        while (i < n)
        {
            ans.push_back(intervals[i++]);
        }
        return ans;
    }
};
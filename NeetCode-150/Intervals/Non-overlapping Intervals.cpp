// Problem: Non-overlapping Intervals
// Platform: NeetCode
// Link: https://neetcode.io/problems/non-overlapping-intervals/question
// time complexity: O(n log n); 
// space complexity: O(1); 

/*  
intervals — ekta list of [start, end] intervals, sorted na, overlap thakte pare.
Kaaj: Minimum koyta interval remove korte hobe jate baki shob intervals non-overlapping hoye jaay (kono duita overlap na kore). Return korte hobe shei minimum removal count-ta (interval list na, শুধু number).

Example 1
Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1

Ken: [1,3] remove korle baki [1,2],[2,3],[3,4] shobgulo non-overlapping hoye jai. Shudhu 1-ta remove korlei hoy.

Example 2
Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2

Ken: Tinta e ekdom shomo, tai duita remove korte hobe, ekta rakhle-i chole.

Example 3
Input: intervals = [[1,2],[2,3]]
Output: 0
Ken: [1,2]-er end, [2,3]-er start-er shathe touch kore, kintu eta overlap na ei problem-e (careful — Merge Intervals-e amra touch-ke overlap dhorechilam, kintu ekhane rule ta different, eta khial rakhba). Tai kono removal lagbe na.

Example Calculation
intervals = [[1,4],[2,3],[3,5],[6,8]]

Step 1 — Sort by end time:

Original end values: 4, 3, 5, 8 → sort korle order hobe end-er choto theke boro:

Before: [[1,4],[2,3],[3,5],[6,8]]
After:  [[2,3],[1,4],[3,5],[6,8]]   (end: 3, 4, 5, 8)

Step 2 — Initialize: count = 0, prevEnd = intervals[0][1] = 3

Step 3 — Loop trace (i=1 theke shuru):

i	intervals[i]	start	start < prevEnd?	Action	            count	prevEnd after
1	[1,4]	        1	        1 < 3? hae	    overlap → remove	1	    3 (unchanged)
2	[3,5]	        3	        3 < 3? na	    no overlap → keep	1	    5
3	[6,8]	        6	        6 < 5? na	    no overlap → keep	1	    8

Final Output: count = 1

Bhalo kore lokkho koro row 1-e: [1,4] overlap korche [2,3]-er shathe (karon [1,4]-er start=1, jeta prevEnd=3-er theke choto). Ekhane amra [1,4]-ke "remove" hishebe dhorlam — karon [2,3]-er end (3) ta [1,4]-er end (4)-er theke choto, tai [2,3]-ke rekhe deoya beshi valuable (future overlap-er chance kom thakbe). Ei jonno-i amra end diye sort kore choto end-wala interval-take priority dei — eta hocche ei greedy pattern-er mul insight.
*/

class Solution
{
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals)
    {
        // end time onujayi sort kora hocche (start diye na!)
        // karon choto end-wala interval future-e kom "jaiga" nibe,
        // tai greedy bhabe eita e best choice rakhar jonno
        sort(intervals.begin(), intervals.end(), []
             (vector<int>&a, vector<int>&b)
        {
            return a[1] < b[1];
        });

        int count = 0; // koyta interval remove korte hobe, eta count kora hocche

        // prevEnd rakhche "last valid (kept) interval"-er end value
        // shuru te prothom interval-take valid dhore nicchi
        int prevEnd = intervals[0][1];

        // i=1 theke shuru, karon intervals[0] already "kept" dhore nichi
        for(int i=1; i<intervals.size(); i++)
        {
            // check kora hocche: current interval-er start,
            // prevEnd-er theke choto kina (mane overlap ache kina)
            if(intervals[i][0] < prevEnd)
            {
                // overlap ache, tai ei interval-take "remove" kora hocche
                count++;
                // prevEnd update kora hocche na, karon age-r choto
                // end-wala interval e best choice hishebe rekhe dicchi
            }
            else
            {
                // overlap nai, tai ei interval-take "keep" kora hocche
                // prevEnd ke update kora hocche current interval-er end diye
                prevEnd = intervals[i][1];
            }
        }
        return count; // total koyta remove korte hoyeche, eta return
    }
};
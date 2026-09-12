// Problem: Meeting Rooms
// Platform: NeetCode
// Link: https://neetcode.io/problems/meeting-rooms/question
// time complexity: O(n log n) - sort kora hocche, tarpor ekbar traverse kora hocche
// space complexity: O(1) - extra space use kora hocche na, except for sorting

/*
Example Calculation
intervals = [(9,10), (4,9), (4,17)]

(format: (start, end))

Step 1 — Sort by start:

Start values: 9, 4, 4 → sort korle:

Before: [(9,10), (4,9), (4,17)]
After:  [(4,9), (4,17), (9,10)]

(Lokkho koro: (4,9) ar (4,17)-er start shomo, tai relative order stable thake — jeta age chilo shei order-e thake, C++ sort unstable hote pare kintu eta problem-er result-e effect fele na, karon amra just overlap check korchi.)

Step 2 — Initialize: loop i=1 theke shuru

Step 3 — Loop trace:

i	intervals[i]	intervals[i].start	intervals[i-1]	intervals[i-1].end	start < prevEnd?	Action
1	(4,17)	        4	                (4,9)	        9	                4 < 9? hae	        return false

Final Output: false

Bhalo kore lokkho koro: Loop-er prothom iteration-e e overlap dhora porlo — (4,9) ar (4,17) overlap kore, karon dutar start e 4, mane ek shathe shuru hocche. Tai ekjon manush duita meeting-e ekshathe thakte parbe na — result সাথে সাথে false return hoye jai, baki interval gulo check করার দরকার e porlo না।
*/

/**
 * Interval class-e duita field ache: start ar end (int type)
 * constructor diye duita value niye object toiri hoy
 */

class Solution
{
public:
    bool canAttendMeetings(vector<Interval>& intervals)
    {
        // intervals gulo start time onujayi sort kora hocche
        // custom comparator lagche karon Interval ekta custom class,
        // eitar kono default '<' operator define kora nai
        sort(intervals.begin(), intervals.end(), [](Interval& a, Interval& b)
        {
            return a.start < b.start; // a-r start choto hole a age ashbe
        });

        // sorted list-e consecutive (paashapashi) pair check kora hocche
        // i=1 theke shuru, karon prothom ta-r shathe compare korar age kichu nai
        for(int i=1; i<intervals.size(); i++)
        {
            // current interval-er start, previous interval-er end-er
            // theke choto hole overlap ache
            if(intervals[i].start < intervals[i-1].end)
            {
                return false; // overlap paoya gele, shobai attend korte parbe na
            }
        }
        return true; // loop shesh, kono overlap pawa jai nai
    }
};
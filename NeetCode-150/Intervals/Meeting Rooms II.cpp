// Problem: Meeting Rooms II
// Platform: NeetCode
// Link: https://neetcode.io/problems/meeting-rooms-ii/question
// time complexity: O(n log n) - sort kora hocche, tarpor ekbar traverse kora hocche
// space complexity: O(n) - heap er space

/*
Bhabo eta ekta timeline-er moto. Prottek meeting-er start-ke dhoro "+1 room lagbe" ar end-ke dhoro "-1 room free hoy"।
intervals = [[0,30],[5,10],[15,20]]

Alada kore shajao (sorted):

Starts: 0, 5, 15
Ends:   10, 20, 30

Ekhon timeline dhore ghurte thako (choto theke boro number, s ar e pointer diye):

Time 0 — start ache (st[0]=0) → room lagbe → room = 1 → maxRoom = 1
Time 5 — porer start (st[1]=5), kintu shobar age dekho end list-e 5-er age kichu ache kina — nai (End[0]=10, 5<10) → tai eta o start hishebe count hobe → room = 2 → maxRoom = 2
Time 10 — ekta meeting shesh hoy (End[0]=10), kintu porer start (st[2]=15) eta 10-er theke boro (15 < 10 na), tai age end process hobe → room = 1
Time 15 — notun start (st[2]=15) ache, 15 < End[1]=20, tai start age → room = 2...

Wait, let's just trust the pointer trace (eta shohoj):

step	st[s] vs End[e]	    Action	            room	    maxRoom
1	    0 < 10	            start → room++	    1	        1
2	    5 < 10	            start → room++	    2	        2
3	    15 < 10? na	        end → room--	    1	        2

Loop shesh (s=3, ar st.size()=3, tai s < size false hoye jai)।

Final Answer: maxRoom = 2

Shohoj bhashay bujhle: Time 5-e dekho — [0,30] cholteche (0 theke 30 porjonto), ar [5,10] shuru hoye geche (5 theke 10)। Duita meeting ek shathe cholche shei muhurte, tai oi shomoy 2-ta room lagbe। [15,20] shuru hobar age [5,10] already shesh hoye geche (10-e), tai [15,20]-er jonno purono room-i reuse kora jai — notun room lagbe na। Tai shob thekhe beshi ekshathe koyta meeting cholche, oita e answer — 2।
*/

class Solution
{
public:
    int minMeetingRooms(vector<Interval>& intervals)
    {
        // start time onujayi sort kora hocche (eita ashole
        // porer step-e dorkar nai, kintu rakhle o kono khoti nai)
        sort(intervals.begin(), intervals.end(),[](Interval& a, Interval& b)
        {
            return a.start < b.start;
        });

        // duita alada vector banano hocche - ekta shudhu start time gulo rakhbe, arekta shudhu end time gulo
        vector<int> st, End;
        for(auto& iv:intervals)
        {
            st.push_back(iv.start);   // start time ta st vector-e push
            End.push_back(iv.end);    // end time ta End vector-e push
        }

        // duita vector ke ALADA ALADA sort kora hocche (kon start kon interval-er chilo eta ekhon ar matter kore na)
        sort(st.begin(), st.end());
        sort(End.begin(), End.end());
        int s=0, e=0;        // duita pointer: st ar End array-er jonno
        int room=0;          // ei muhurte koyta room use hocche
        int maxRoom=0;       // ekhon porjonto max koyta room lagche

        // jotokhon shob start time process kora na hoy
        while(s < st.size())
        {
            // jodi kono notun meeting shuru hoy kono existing meeting shesh howar AGE
            if(st[s] < End[e])
            {
                room++;   // notun room lagbe, tai barano hocche
                s++;      // porer start time-e jaw
            }
            else
            {
                // eta mane kono ekta meeting shesh hoye geche
                room--;   // ekta room free hocche, tai komano hocche
                e++;      // porer end time-e jaw
            }
            // prottek step-er por check kora hocche - ekhon porjonto max koyta room lagche
            maxRoom=max(maxRoom, room);
        }
        return maxRoom; // shesh answer - max koyta room ekshathe lagche
    }
};
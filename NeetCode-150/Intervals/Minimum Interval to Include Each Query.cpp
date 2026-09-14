// Problem: Minimum Interval to Include Each Query
// Platform: NeetCode
// Link: https://neetcode.io/problems/minimum-interval-to-include-each-query/question
// time complexity: O((n+m) log n); n = intervals.size(), m = queries.size().. heap er jonno log n lagbe, ar sort er jonno o log n lagbe
// space complexity: O(n+m); heap er jonno n, ar result vector er jonno m lagbe

/*
intervals = [[1,4],[2,4],[3,6],[4,4]]   (start diye already sorted)
queries   = [2,3,4,5]

Queries-ke sort korlam (value, original_index) shoho:
sortedQueries = [(2,0), (3,1), (4,2), (5,3)]
(Ei case-e value already choto-theke-boro chilo, tai order change hoy nai, shudhu index-gula shathe attach hoyeche)

Shuru te: i=0 (intervals pointer), minHeap = {} (khali), ans = [-1,-1,-1,-1]

Query 1: q=2, idx=0
Step 1 (push): Dekho intervals[i] mane intervals[0] = [1,4]। Start=1, eta q=2-er cheye choto ba shomo? Hae (1<=2)। Tai push koro heap-e: size = 4-1+1=4, end=4 → push (4,4)। i ekhon 1।
Abar check koro: intervals[1] = [2,4]। Start=2 <= 2? Hae। Push: size=4-2+1=3, end=4 → push (3,4)। i ekhon 2।
Abar check koro: intervals[2] = [3,6]। Start=3 <= 2? Na (3>2)। Loop thamo।
Heap-e ekhon ache: (4,4) ar (3,4) — min-heap hওয়ay top-e thakbe choto size ta, mane (3,4)।

Step 2 (stale felo): Top (3,4) — end=4, eta q=2-er cheye choto? Na (4>=2, valid)। Kichu felte hobe na।
Step 3 (answer): Heap khali na, top-er size = 3 → ans[0] = 3

Query 2: q=3, idx=1
Step 1 (push): intervals[2] = [3,6]। Start=3 <= 3? Hae। Push: size=6-3+1=4, end=6 → push (4,6)। i ekhon 3।
Abar check: intervals[3]=[4,4]। Start=4 <=3? Na। Loop thamo।
Heap-e ekhon ache: (3,4), (4,4), (4,6) — top hocche choto size, mane (3,4)।

Step 2 (stale felo): Top (3,4) — end=4 >= 3? Hae, valid। Felte hobe na।
Step 3 (answer): top-er size = 3 → ans[1] = 3

Query 3: q=4, idx=2

Step 1 (push): intervals[3]=[4,4]। Start=4<=4? Hae। Push: size=4-4+1=1, end=4 → push (1,4)। i ekhon 4 (list shesh)।
Heap-e ekhon ache: (1,4), (3,4), (4,4), (4,6) — top hocche shobcheye choto size, mane (1,4)।
Step 2 (stale felo): Top (1,4) — end=4>=4? Hae, valid।
Step 3 (answer): top size = 1 → ans[2] = 1

Query 4: q=5, idx=3

Step 1 (push): i=4, ar intervals.size()=4, tai i < size false — kichu push hobe na।
Step 2 (stale felo): Heap top ekhono (1,4) — end=4, eta q=5-er cheye choto (4<5) → stale! Pop koro।
Notun top: (3,4) — end=4, ekhono 4<5 → stale! Pop koro।
Notun top: (4,4) — end=4, ekhono 4<5 → stale! Pop koro।
Notun top: (4,6) — end=6, 6<5? Na (6>=5, valid!) → thamo।

Step 3 (answer): top size = 4 → ans[3] = 4

Final Answer
ans = [3, 3, 1, 4]
*/

class Solution
{
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries)
    {
        // intervals ke start diye sort kora
        sort(intervals.begin(), intervals.end(), []
             (vector<int>&a, vector<int>&b)
        {
            return a[0] < b[0];
        });
        // queries ke {value, original_index} pair banaiya sort kora
        // (original index lagbe karon answer original order e boshate hobe)
        vector<pair<int,int>> sortedQueries;
        for(int i=0; i<queries.size(); i++)
        {
            sortedQueries.push_back({queries[i], i});
        }
        sort(sortedQueries.begin(), sortedQueries.end());
        vector<int> ans(queries.size(), -1); // default -1, jodi kono interval cover na kore
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minHeap; // {size, end}
        int i = 0; // intervals er pointer
        // sorted queries loop kora (choto theke boro)
        for(auto& [q, idx] : sortedQueries)
        {
            // Step 1: shob interval jegular start <= q, heap e push koro
            while(i < intervals.size() && intervals[i][0] <= q)
            {
                int size = intervals[i][1] - intervals[i][0] + 1;
                minHeap.push({size, intervals[i][1]});
                i++;
            }
            // Step 2: heap er top theke stale intervals felo (jegular end < q, mane ora ar q ke cover korte pare na)
            while(!minHeap.empty() && minHeap.top().second < q)
            {
                minHeap.pop();
            }
            // Step 3: heap khali na hoile, top-er size e answer
            if(!minHeap.empty())
            {
                ans[idx] = minHeap.top().first;
            }
        }
        return ans;
    }
};
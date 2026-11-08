// Time: O(n log n). 2n ta event sort O(n log n), protyek event e multiset insert/erase/rbegin O(log n).
// Space: O(n) event, heap, ans.


/*
(buildings = [[2,9,10],[3,7,15]]):

Event sorted: (2,-10), (3,-15), (7,15), (9,10). Shuru: heap = {0}, prevTop = 0.

Event	    Ki hoy	    heap	    curTop	prevTop	Point?
(2,-10)	    insert 10	{0,10}	    10	    0	    ✅ [2,10], prevTop=10
(3,-15)	    insert 15	{0,10,15}	15	    10	    ✅ [3,15], prevTop=15
(7,15)	    erase 15	{0,10}	    10	    15	    ✅ [7,10], prevTop=10
(9,10)	    erase 10	{0}	        0	    10	    ✅ [9,0], prevTop=0

Output: [[2,10],[3,15],[7,10],[9,0]]
*/


class Solution
{
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings)
    {
        // event = (x, value) pair er list
        // shuru event: (left, -height), shesh event: (right, +height)
        vector<pair<int, int>> event;

        // protyek building er jonno duto event
        for(auto& b : buildings)
        {
            // shuru: negative height (sort e shuru age ashe, uchu building age ashe)
            event.push_back({b[0], -b[2]});
            // shesh: positive height
            event.push_back({b[1], b[2]});
        }

        // x er order e sort (ek-i x e negative age, tai shuru age, shesh pore)
        sort(event.begin(), event.end());
        vector<vector<int>> ans;

        // heap = ekhon dariye thaka building gulor height (sorted thake)
        multiset<int> heap;
        // ground level 0, jate heap khali hole-o top = 0 pai
        heap.insert(0);

        // ager top height (shuru te ground = 0)
        int prevTop = 0;
        // sorted event e baam theke dane haati
        for(auto [x, h] : event)
        {
            if(h < 0)
            {
                // shuru event: negative ke positive kore heap e dhukai
                heap.insert(-h);
            }
            else
            {
                // shesh event: heap theke ekta-i h ber kori
                // (erase(h) dile shob h muche jay, tai find diye)
                heap.erase(heap.find(h));
            }

            // ekhon sobcheye uchu building er height (multiset er shesh element)
            int curTop = *heap.rbegin();

            // uchchota bodlale-i point likhbo
            if(curTop != prevTop)
            {
                // x e shiri curTop e uthlo/namlo
                ans.push_back({x, curTop});
                // porer tulonar jonno update
                prevTop = curTop;
            }
        }
        return ans;
    }
};
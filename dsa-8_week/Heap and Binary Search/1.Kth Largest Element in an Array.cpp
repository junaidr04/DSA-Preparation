// Time Complexity  : O(n log k)  -> n ta element, proti ta push/pop e O(log k)
// Space Complexity : O(k)        -> heap e max k+1 ta element thake

/*
Dry Run

nums = [3, 2, 1, 5, 6, 4], k = 2

Step	val	push er por heap	size > 2?	pop er por heap
1	3	{3}	                    No	            {3}
2	2	{2, 3}	                No	            {2, 3}
3	1	{1, 2, 3}	            Yes (3)	        pop 1 → {2, 3}
4	5	{2, 3, 5}	            Yes (3)	        pop 2 → {3, 5}
5	6	{3, 5, 6}	            Yes (3)	        pop 3 → {5, 6}
6	4	{4, 5, 6}	            Yes (3)	        pop 4 → {5, 6}

Shesh e heap = {5, 6}, top() = 5.

Check kori: sorted descending = [6, 5, 4, 3, 2, 1], 2nd largest = 5. ✅  
*/

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {

        // min-heap banalam: top() e shobsomoy shobcheye CHHOTO element thakbe
        // (default priority_queue max-heap, tai greater<int> dilam)
        priority_queue<int, vector<int>, greater<int>> minHeap;
        // array er proti ta element ke ek ek kore nicchi
        for(int val : nums)
        {
            // element ta heap e dhukalam, cost O(log k)
            minHeap.push(val);

            // heap er size k er beshi hoye gele
            // shobcheye chhoto element (top) ta fele dei
            // karon amra shudhu k ta BORO element rakhte chai
            if(minHeap.size() > k)
            {
                minHeap.pop();
            }
        }

        // loop shesh e heap e ache shobcheye boro k ta element
        // tader moddhe shobcheye chhoto ta (top) = k-th largest
        return minHeap.top();
    }
};
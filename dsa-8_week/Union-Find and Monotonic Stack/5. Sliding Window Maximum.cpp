// TC: O(n), prottek index max 1 bar push, 1 bar pop.
// SC: O(k), deque e max k ta index.


/*
Example: nums = [1, 3, -1, -3, 5, 3, 6, 7], k = 3 (n = 8)
Window er baam shima = i - 3 + 1 = i - 2. Shuru: dq = [], ans = []

i	nums[i]	    1. front pop (front < i-2?)	    2. back pop (nums[back] <= nums[i]?)	3. push er por dq (index)	dq er value	    4. i >= 2? ans
0	1	        khali, skip	                    khali, skip	                                [0]	                        1	            na
1	3	        khali na, 0 < -1? na	        1 <= 3 ✅ pop 0	                           [1]	                       3	            na
2	-1	        1 < 0? na	                    3 <= -1? na	                                [1, 2]	                    3, -1	        ✅ nums[1] = 3
3	-3	        1 < 1? na	                    -1 <= -3? na	                            [1, 2, 3]	                3, -1, -3	    ✅ 3
4	5	        1 < 2 ✅ pop 1	                -3 <= 5 ✅ pop 3, -1 <= 5 ✅ pop 2	   [4]	                        5	            ✅ 5
5	3	        4 < 3? na	                    5 <= 3? na	                                [4, 5]	                    5, 3	        ✅ 5
6	6	        4 < 4? na	                    3 <= 6 ✅ pop 5, 5 <= 6 ✅ pop 4	        [6]	                        6	            ✅ 6
7	7	        6 < 5? na	                    6 <= 7 ✅ pop 6	                          [7]	                      7               ✅ 7

Output: [3, 3, 5, 5, 6, 7] ✅
*/

class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k)
    {
        int n = nums.size();                 // array te koyta number ache
        vector<int> ans;                     // prottek window er max ekhane jomabo
        deque<int> dq;                       // INDEX rakhbo (value na). deque er bhitore value decreasing, tai front e shobsomoy max
        for (int i = 0; i < n; i++)          // i = ekhon window er dan dik er (notun) index
        {
            //  1. FRONT POP: window er baire gele 
            // window er baam shima = i-k+1. front er index er cheyeo chhoto mane oi element window theke bairie geche
            if (!dq.empty() && dq.front() < i-k+1)   // !dq.empty() age, na hole khali deque te front() crash
            {
                dq.pop_front();              // expire howa index ta samne theke fele dao
            }
            //  2. BACK POP: chhoto/equal gulo soraao 
            // nums[i] boro ar pore porjonto thakbe, tai back er chhoto/equal gulo kokhono max hobe na
            while (!dq.empty() && nums[dq.back()] <= nums[i])   // dq.back() = index, nums[...] diye value
            {
                dq.pop_back();               // pichon theke chhoto gulo fele dao (while, karon ekadhik hote pare)
            }
            // 3. PUSH 
            dq.push_back(i);                 // i ke pichone rakho, ekhon i-i candidate
            //  4. ANSWER 
            if (i >= k-1)                    // i < k-1 porjonto prothom window ekhono purno hoy ni
            {
                ans.push_back(nums[dq.front()]);   // front = max er index, nums[...] diye value
            }
        }
        return ans;                          // return loop er BAIRE
    }
};
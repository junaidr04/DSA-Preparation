// TC: O(n). Prottek index max 1 bar push ar 1 bar pop hoy, tai while thaka shotteo total O(n).
// SC: O(n). Stack e worst case (decreasing temperature) shob index thake.


/*
Example: [73, 74, 75, 71, 69, 72, 76, 73] (n = 8)

Shuru te ans = [0,0,0,0,0,0,0,0], st = []

i	temp[i]	    while shorto (top er temp)	    pop + ans update	        push er por stack (index)
0	73	        stack khali	                      kichu na	                      [0]
1	74	        74 > 73 ✅	                    pop 0, ans[0] = 1-0 = 1	        [1]
2	75	        75 > 74 ✅	                    pop 1, ans[1] = 2-1 = 1	        [2]
3	71	        71 > 75? ❌	                    kichu na	                    [2, 3]
4	69	        69 > 71? ❌	                    kichu na	                    [2, 3, 4]
5	72	        72 > 69 ✅	                    pop 4, ans[4] = 5-4 = 1	
		        72 > 71 ✅	                    pop 3, ans[3] = 5-3 = 2	
		        72 > 75? ❌ thamo		                                        [2, 5]
6	76	        76 > 72 ✅	                    pop 5, ans[5] = 6-5 = 1	
		        76 > 75 ✅	                    pop 2, ans[2] = 6-2 = 4	
		        stack khali, thamo		[6]
7	73	        73 > 76? ❌	                    kichu na	                    [6, 7]

Shesh: stack e [6, 7] baki, tader ans 0 (age thekei 0).

Final: ans = [1, 1, 4, 2, 1, 1, 0, 0]   
*/


class Solution
{
public:
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        int n = temperatures.size();
        vector<int> ans(n, 0); // shuru te shob 0 (beshi din na ashle 0-i thakbe)
        stack<int> st;         // index rakhbo (value na), "opekkhay" thaka din gulo
        for (int i = 0; i < n; i++) // i = ekhon er din
        {
            // jotokkhon stack khali na ar aj er temp top er din er cheye beshi
            while (!st.empty() && temperatures[i] > temperatures[st.top()])
            {
                int idx = st.top(); // opekkhay thaka din er index
                st.pop();           // top() age, pop() pore
                ans[idx] = i - idx; // idx er prothom beshi din holo i, tai index difference
            }
            st.push(i); // FIX: stack e push (ans e na), i ekhon opekkhay
        }
        return ans; // return loop er BAIRE
    }
};
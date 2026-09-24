// Problem: Sliding Window Maximum
// Platform: NeetCode
// Link: https://neetcode.io/problems/sliding-window-maximum
// time complexity: O(n); single pass through the array
// space complexity: O(k); where k is the size of the sliding window

/*  
nums = [1, 3, -1, -3, 5, 3, 6, 7]
         0  1   2   3  4  5  6  7
k = 3
Step 1: i = 0

Current value:
nums[0] = 1

Deque empty: dq = []
Back থেকে remove করার কিছু নেই।

তারপর:
dq.push_back(0);

তাই: dq = [0]

এখন i >= k-1?

0 >= 2 ❌

তাই answer এখনো হবে না।
ans = []

Step 2: i = 1

Current: nums[1] = 3

Deque: dq = [0]
Back check: nums[1] >= nums[dq.back()]

3 >= nums[0]
3 >= 1 ✅

তাই index 0 remove: dq.pop_back();

এখন: dq = []

তারপর:
dq.push_back(1);
dq = [1]

এখন: 1 >= 2 ❌

Answer এখনো নেই।
ans = []

Step 3: i = 2

Current: nums[2] = -1

Deque: dq = [1]

Window হবে: [1, 3, -1]
প্রথমে বাইরে গেছে কিনা:

Window start:

i-k+1
= 2-3+1
= 0

dq.front(): 1
Check:

1 < 0 ❌

তাই remove করব না।

Back থেকে ছোট remove: nums[2] >= nums[1]

-1 >= 3 ❌

তাই কিছু remove হবে না।

তারপর:
dq.push_back(2);
dq = [1, 2]

এখন:
i >= k-1
2 >= 2 ✅

তাই: ans.push_back(nums[dq.front()]);

dq.front(): 1

nums[1]: 3

তাই: ans = [3]
✅ প্রথম window-এর maximum = 3

Step 4: i = 3

Current: nums[3] = -3

Window: [3, -1, -3]

Index: [1, 2, 3]

Window start: 3-3+1 = 1

Deque: [1, 2]

dq.front() = 1
Check:

1 < 1 ❌
Remove হবে না।

Back check: nums[3] >= nums[2]
-3 >= -1 ❌

তারপর: dq = [1, 2, 3]

Maximum:
dq.front() = 1
nums[1] = 3

Answer: ans = [3, 3]

Step 5: i = 4

Current: nums[4] = 5
Window: [-3, 5, 3]
Index: [2, 3, 4]

Current window start: 4-3+1 = 2

Deque আগে: [1, 2, 3]
Outside index remove
dq.front() = 1

1 < 2 ✅

তাই: dq.pop_front();

Deque: [2, 3]
এবার back থেকে ছোটগুলো remove
Current value = 5
Back index = 3
5 >= nums[3]
5 >= -3 ✅

remove: dq = [2]

আবার back:
5 >= nums[2]
5 >= -1 ✅

remove: dq = []

এখন current index:
dq.push_back(4);
dq = [4]

Maximum:
nums[dq.front()]
= nums[4]
= 5

Answer: ans = [3, 3, 5]

🔥 এখানে while কেন দরকার ছিল সেটা পরিষ্কার:

[2,3]
 ↑ ↑
-1 -3

5 দুটোর চেয়েই বড়, তাই দুটোকেই remove করতে হয়েছে।

Step 6: i = 5

Current: nums[5] = 3
Window: [5, 3, 6]
Actually current window at i=5 is:

nums[3], nums[4], nums[5]
= [-3, 5, 3]

Deque: [4]

Outside check:

window start = 5-3+1 = 3
4 < 3 ❌

Back check:
3 >= nums[4]
3 >= 5 ❌

Add: dq = [4,5]

Maximum:
nums[dq.front()]
= nums[4]
= 5

Answer: [3,3,5,5]

Step 7: i = 6

Current: nums[6] = 6
Window: [5, 3, 6]
Deque: [4,5]
Window start: 6-3+1 = 4
Outside: dq.front() = 4

4 < 4 ❌

Back:
6 >= nums[5]
6 >= 3 ✅

Remove index 5:
dq = [4]

আবার:
6 >= nums[4]
6 >= 5 ✅

Remove: dq = []

Add 6: dq = [6]

Maximum: nums[6] = 6

Answer: [3,3,5,5,6]

Step 8: i = 7

Current: nums[7] = 7
Window: [3, 6, 7]
Deque: [6]

Back: 7 >= nums[6]

7 >= 6 ✅

Remove: dq = []
Add: dq = [7]
Maximum: nums[7] = 7

Final: ans = [3, 3, 5, 5, 6, 7]
*/

class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k)
    {
        vector<int> ans; // Final answer রাখার জন্য vector.. আমাদের answer হবে: [3, 3, 5, 5, 6, 7]
        deque<int> dq; // Deque-এর মধ্যে আমরা VALUE রাখব না.. INDEX রাখব.. যেমন: dq = [1, 2] মানে nums[1], nums[2]
        for(int i = 0; i < nums.size(); i++) // i হলো বর্তমানে যে element নিয়ে কাজ করছি তার index
        {
            // Current window-এর বাইরে চলে যাওয়া পুরোনো index remove করছি
            // Current window শুরু হয়: i - k + 1
            // Example: i = 2, k = 3
            // window start = 2 - 3 + 1 = 0
            // তাই valid index = 0,1,2
            // যদি dq.front() < 0 হয়, তাহলে সেটা window-এর বাইরে
            if(!dq.empty() && dq.front() < i-k+1)
            {
                dq.pop_front();
            }
            // নতুন element-এর চেয়ে ছোট বা equal element.. deque-এর back থেকে remove করছি
            // কারণ নতুন element সামনে থাকলে.. ওই ছোট element future-এ maximum হতে পারবে না
            // Example: dq = [0]
            // nums[0] = 1
            // নতুন nums[i] = 3
            // 3 >= 1
            // তাই index 0 remove... dq এখন empty
            while(!dq.empty() && nums[i] >= nums[dq.back()])
            {
                dq.pop_back();
            }
            dq.push_back(i);  // Current element-এর index deque-এর back-এ রাখছি
            // যখন অন্তত k টি element পাওয়া গেছে,
            // তখন একটা complete window তৈরি হয়েছে
            // dq.front() সবসময় current window-এর
            // maximum element-এর index
            // তাই nums[dq.front()] = maximum value, সেটা answer-এ add করছি
            if(i >= k-1)
            {
                ans.push_back(nums[dq.front()]);
            }
        }
        return ans; // সব window-এর maximum return করছি
    }
};

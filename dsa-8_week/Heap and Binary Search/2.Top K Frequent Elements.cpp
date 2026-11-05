// TC:O(n); maximum frequency = n, so bucket size = n+1, and we are iterating through the bucket once, so O(n) + O(n) = O(n)
// SC:O(n); 


/*
Input: nums = [1,1,1,2,2,3], k = 2
Dry Run Table
Step	কাজ	            Result
1	Frequency Count	    1→3, 2→2, 3→1
2	bucket[3]	        [1]
3	bucket[2]	        [2]
4	bucket[1]	        [3]
5	i = 6	            Empty
6	i = 5	            Empty
7	i = 4	            Empty
8	i = 3	            ans = [1]
9	i = 2	            ans = [1,2]
10	ans.size() == k	    2 == 2 → True

Final Answer
[1, 2]


মনে রাখবে: Frequency count → Bucket তৈরি → Reverse loop → K elements return।  
*/


class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {

        // প্রতিটি number কতবার এসেছে তা count করার জন্য HashMap
        unordered_map<int, int> freq;

        // পুরো array-এর প্রতিটি number এক এক করে নিচ্ছি
        for(int n : nums)
        {
            // number-টি যতবার আসবে তার frequency 1 করে বাড়বে
            freq[n]++;
        }

        // Bucket তৈরি করছি
        // Bucket-এর index হবে frequency
        // nums.size()+1 দেওয়ার কারণ maximum frequency হতে পারে nums.size()
        vector<vector<int>> bucket(nums.size() + 1);

        // HashMap থেকে প্রতিটি number এবং তার frequency নিচ্ছি
        for(auto& [num, count] : freq)
        {
            // যে number যতবার এসেছে তাকে সেই frequency-এর bucket-এ রাখছি
            bucket[count].push_back(num);
        }

        // Final answer রাখার জন্য empty vector
        vector<int> ans;

        // সবচেয়ে বেশি frequency পাওয়ার জন্য শেষ index থেকে loop শুরু করছি
        for(int i = bucket.size() - 1; i >= 0; i--)
        {
            // বর্তমান bucket-এর ভিতরে থাকা প্রতিটি number নিচ্ছি
            for(int num : bucket[i])
            {
                // পাওয়া number-টি answer vector-এ যোগ করছি
                ans.push_back(num);

                // প্রয়োজনীয় k সংখ্যক number পাওয়া হয়েছে কি না check করছি
                if(ans.size() == k)
                {
                    // k সংখ্যক number পাওয়া গেলে answer return করছি
                    return ans;
                }
            }
        }

        // Safety return
        return ans;
    }
};
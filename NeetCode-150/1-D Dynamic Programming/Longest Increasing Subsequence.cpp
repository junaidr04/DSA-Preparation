// Problem: Longest Increasing Subsequence
// Platform: NeetCode
// Link: https://neetcode.io/problems/longest-increasing-subsequence
// time complexity: O(n^2); Outer loop i: O(n) Inner loop j: O(n)
// space complexity: O(n); dp vector er size n।


/*
example: nums = [10, 9, 2, 5, 3, 7, 101, 18]
Index:   0    1   2   3   4   5   6    7
nums:    10   9   2   5   3   7   101  18

Shuru te: dp = [1, 1, 1, 1, 1, 1, 1, 1] (protیটা element নিজেই একটা length-1 sequence, কারণ একা একটা number ও "increasing sequence" হিসেবে count হয়)

i = 0 (mane amরা এখন position 0 এ, value = 10)

i=0 এর আগে কোনো j নেই (kারণ j < 0 সম্ভব না)। Loop চলবেই না। dp[0] = 1 থেকে যায়।

i = 1 (mane amরা এখন position 1 এ, value = 9)

j চেক korবো 0 theke i-1=0 porjonto, mane শুধু j=0।

j=0: nums[j]=nums[0]=10, nums[i]=nums[1]=9
     10 < 9? NA (10 boro, 9 er cheye)
     Increasing hচ্ছে না, tাi কিছু হবে না

dp[1] = 1 (কোনো change নাই)

বুঝলে? — 9 এর আগে শুধু 10 আছে, kিন্তু 10 → 9 তো কমে যাচ্ছে, বাড়ছে না। তাই এখান থেকে sequence extend করা যাবে না।

i = 2 (mane position 2 এ, value = 2)

j চেক korবো 0 ar 1।

j=0: nums[0]=10, nums[2]=2. 10<2? NA
j=1: nums[1]=9,  nums[2]=2. 9<2?  NA

দুটোই fail। dp[2] = 1।

বুঝলে? — 2 হলো এখন পর্যন্ত সবচেয়ে ছোট number। এর আগের কোনো number থেকে বাড়তে বাড়তে 2 এ আসা যায় না (কারণ আগের সবগুলোই 2 থেকে বড়)।

i = 3 (mane position 3 এ, value = 5)

j চেক korবো 0, 1, 2।

j=0: nums[0]=10, nums[3]=5. 10<5? NA
j=1: nums[1]=9,  nums[3]=5. 9<5?  NA
j=2: nums[2]=2,  nums[3]=5. 2<5?  HAA! ✅ Increasing hচ্ছে!
     dp[3] = max(dp[3], dp[2]+1) = max(1, 1+1) = 2

dp[3] = 2

বুঝলে? — j=2 (value=2) theke i=3 (value=5) e আসা যায়, কারণ 2 < 5। ওই position (j=2) porjonto sequence length ছিল dp[2]=1 (mane শুধু {2})। এখন 5 যোগ করলে হয় {2, 5} — length 2। তাই dp[3] = 2।

i = 4 (mane position 4 এ, value = 3)

j চেক korবো 0, 1, 2, 3।

j=0: 10<3? NA
j=1: 9<3?  NA
j=2: nums[2]=2, 2<3? HAA! dp[4] = max(1, dp[2]+1) = max(1, 2) = 2
j=3: nums[3]=5, 5<3? NA

dp[4] = 2

বুঝলে? — {2, 3} sequence বানানো যায় (j=2 theke), length 2। j=3 (value 5) diয়ে যাওয়া যায়নি কারণ 5 < 3 না (5 তো 3 থেকে বড়, kিন্তু এখানে দরকার nums[j] < nums[i], mane আগের number ছোট হতে হবে — 5 ছোট না 3 থেকে)।

i = 5 (mane position 5 এ, value = 7)

j চেক korবো 0 theke 4।

j=0: 10<7? NA
j=1: 9<7?  NA
j=2: 2<7?  HAA! dp[5] = max(1, dp[2]+1) = max(1, 2) = 2
j=3: 5<7?  HAA! dp[5] = max(2, dp[3]+1) = max(2, 3) = 3
j=4: 3<7?  HAA! dp[5] = max(3, dp[4]+1) = max(3, 3) = 3

dp[5] = 3

বুঝলে? — এখানে তিনটা j valid হয়েছে (2, 3, 4 — সব nums[j] < 7)। প্রতিটার জন্য আলাদা সম্ভাব্য sequence:

j=2: {2, 7} → length 2
j=3: {2, 5, 7} → length 3 (কারণ dp[3]=2 mane ওই porjonto already {2,5} ছিল)
j=4: {2, 3, 7} → length 3

এদের মধ্যে সবচেয়ে বড়টা (max) নিলাম — 3।

i = 6 (mane position 6 এ, value = 101)

101 সবচেয়ে বড় number, tাi সব আগের j (0 theke 5) valid হবে (সবাই 101 থেকে ছোট)।

j=0: dp[0]+1 = 2
j=1: dp[1]+1 = 2
j=2: dp[2]+1 = 2
j=3: dp[3]+1 = 3
j=4: dp[4]+1 = 3
j=5: dp[5]+1 = 4   <- সবচেয়ে বড়!

dp[6] = 4

বুঝলে? — j=5 (value 7) porjonto already best sequence ছিল {2,3,7} (length 3)। এখন 101 যোগ করলে {2,3,7,101} — length 4।

i = 7 (mane position 7 এ, value = 18)
j=0: 10<18? HAA, dp[0]+1=2
j=1: 9<18?  HAA, dp[1]+1=2
j=2: 2<18?  HAA, dp[2]+1=2
j=3: 5<18?  HAA, dp[3]+1=3
j=4: 3<18?  HAA, dp[4]+1=3
j=5: 7<18?  HAA, dp[5]+1=4   <- best
j=6: 101<18? NA

dp[7] = 4

বুঝলে? — {2,3,7,18} — length 4 (101 এর জায়গায় 18 বসিয়ে একই length পাওয়া যায়, কারণ dp[5]=3 porjonto এসে 18 যোগ করলেও 4 হয়)।

Final Table
Index: 0   1   2   3   4   5   6    7
nums:  10  9   2   5   3   7   101  18
dp:    1   1   1   2   2   3   4    4
Answer বের korা

এখন dp array এর সব value এর মধ্যে maximum বের korো:

ans = max(1,1,1,2,2,3,4,4) = 4

Output: 4 ✅ (matches — LIS হলো {2,3,7,101} অথবা {2,3,7,18})
*/


class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;  // sob dp[i] er modhe maximum ekhane rakhbo
        // dp[i] = index i te SHESH howa longest increasing subsequence er length
        // shuru te sob 1 kore, karon protita single element nijei ekta valid
        // length-1 subsequence
        vector<int> dp(n, 1);
        // i = ekhon amra kon index er dp calculate korchi
        for(int i = 0; i < n; i++)
        {
            // j = i er age kon kon index check korchi
            for(int j = 0; j < i; j++)
            {
                // jodi nums[j] choto hoy nums[i] theke, tahole ekta increasing 
                // pair banano jay (nums[j], nums[i])
                if(nums[i] > nums[j])
                {
                    // dp[j] porjonto ekta subsequence ache (length dp[j])
                    // ei subsequence er shathe nums[i] jog korle notun length = dp[j]+1
                    // amra MAXIMUM rakhi (kotogula j theke asha subsequence er modhe shera ta)
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
        }
        // sob dp[i] er modhe maximum ta ber koro
        // (karon LIS je kono index e shesh hote pare, dp[n-1] fixed answer na)
        for(int i = 0; i < n; i++)
        {
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};
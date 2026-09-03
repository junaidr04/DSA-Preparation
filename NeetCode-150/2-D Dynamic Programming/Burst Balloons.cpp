// Problem: Burst Balloons
// Platform: NeetCode
// Link: https://neetcode.io/problems/burst-balloons
// time complexity: O(n^3); 3ta nested loop — left যায় 0 থেকে n, right যায় left+1 থেকে n, i যায় left+1 থেকে right.. প্রতিটা cell এ constant work
// space complexity: O(n^2); memo array এর size (n+2) x (n+2)

/*
এই problem-এ তোমাকে মূলত কোন order-এ balloon burst করলে total coin সবচেয়ে বেশি হবে, সেটা বের করতে হবে।
ধরি:

nums = [4,2,3,7]
যখন তুমি কোনো balloon burst করবে, তখন coin হবে: left * current * right

মানে, ওই balloon-এর বর্তমান বাম পাশের balloon × ওই balloon × বর্তমান ডান পাশের balloon। যদি পাশে কিছু না থাকে, তাহলে সেই side-এর value 1 ধরবে।
এখন example-টা দেখি।

প্রথমে:
[4,2,3,7]

যদি 2 burst করি:
4 * 2 * 3 = 24

array হয়ে যাবে: [4,3,7]
এরপর 3 burst করি:4 * 3 * 7 = 84

array:[4,7]

এরপর 4 burst করি:
1 * 4 * 7 = 28
array:[7]

শেষে 7:

1 * 7 * 1 = 7
Total: 24 + 84 + 28 + 7 = 143

তাই answer: 143

সবচেয়ে important ব্যাপার হলো, তুমি শুধু সব balloon burst করবে না; কোনটা আগে আর কোনটা পরে burst করলে maximum coin পাওয়া যাবে, সেই best order বের করবে। কারণ order change করলে answer change হয়ে যায়। যেমন প্রথমেই 4 burst করলে:
1 * 4 * 2 = 8
কিন্তু 2 আগে burst করলে পেয়েছিলে:

4 * 2 * 3 = 24
তাই problem-এর main question: nums এর সব balloon burst করার এমন একটা order বের করো, যাতে total coins maximum হয়।  

আমরা কোন balloon আগে burst করবো সেটা চিন্তা করি না। বরং একটি range-এর মধ্যে কোন balloon-টা সবার শেষে burst হবে সেটা চিন্তা করি।

একটা ছোট example নিই:

nums = [3, 1, 5]

Code প্রথমে দুই পাশে 1 যোগ করবে:

ballon = [1, 3, 1, 5, 1]
          0  1  2  3  4

এখন call হবে:

solve(0, 4)

মানে:

1 | 3  1  5 | 1
↑             ↑
left          right

আমাদের 3, 1, 5 এর মধ্যে কে সবার শেষে burst হবে, সেটা try করবো।

মূল Formula
coin =
ballon[left] * ballon[i] * ballon[right]+ solve(left, i)+ solve(i, right);

এখানে i হলো শেষে burst হওয়া balloon।

Case 1: 3 কে শেষে burst করি
1 | 3  1  5 | 1
    ↑
   last

তাহলে 3 burst হওয়ার আগে 1 এবং 5 already burst হয়ে যাবে।
তাই 3 যখন শেষে burst হবে, তার দুই neighbour হবে:
1 and 1

তাই:

coin = 1 × 3 × 1 = 3
কিন্তু তার আগে আমাদের ডান পাশ solve করতে হবে:

solve(1, 4)

মানে:
3 | 1  5 | 1
solve(1,4) এ

এখানে 1,5 এর মধ্যে কে শেষে burst হবে সেটা দেখি।

যদি 1 শেষে burst হয়
3 | 1 | 5

5 আগে burst হবে:
3 × 5 × 1 = 15

তারপর 1:

3 × 1 × 1 = 3

Total:

15 + 3 = 18
যদি 5 শেষে burst হয়

প্রথমে 1 burst:
3 × 1 × 5 = 15

তারপর 5:
3 × 5 × 1 = 15

Total:15 + 15 = 30
তাই:

solve(1,4) = 30
এখন 3-কে শেষে burst করার total:

solve(0,1) + solve(1,4) + শেষের 3 burst
0 + 30 + 3= 33
Case 2: মাঝের 1 কে শেষে burst করি
1 | 3  1  5 | 1
       ↑
      last

শেষে 1 burst হওয়ার সময় তার neighbour হবে boundary: 3 and 5

তাই শেষের coin: 3 × 1 × 5 = 15
এখন left এবং right আলাদা করে solve হবে।

Left side
1 | 3 | 1

3 burst: 1 × 3 × 1 = 3

তাই:

solve(0,2) = 3
Right side
1 | 5 | 1
1 × 5 × 1 = 5

তাই:
solve(2,4) = 5

সব মিলিয়ে:

3 + 15 + 5
= 23
Case 3: 5 কে শেষে burst করি
1 | 3  1  5 | 1
          ↑
         last

5 যখন শেষে burst হবে, তার neighbour হবে:
1 and 1

তাই:
1 × 5 × 1 = 5
এখন বাম পাশ solve:
1 | 3  1 | 5

এখানে best order:
প্রথমে 1 burst: 3 × 1 × 5 = 15

তারপর 3: 1 × 3 × 5 = 15

Total:15 + 15 = 30
    
তাই overall:
30 + 5 = 35
সব Case Compare করি
শেষে burst হবে     Total Coins
--------------------------------
3                  33
1                  23
5                  35  ← Maximum

তাই:
solve(0,4) = 35
Final Answer
nums = [3,1,5]
Maximum Coins = 35
*/


class Solution {
public:
    int solve(int left, int right, vector<vector<int>>& memo, vector<int>& ballon)
    {
        // base case: left ar right er majhe kono balloon nai 
        // (adjacent hoye geche), tai ar burst korar kichu nai
        if(left+1 == right)
            return 0;
        
        // age compute kora thakle direct return
        if(memo[left][right] != -1)
            return memo[left][right];
        int best = 0;
        // 'i' ke range (left, right) er modhye "shesh e burst kora" balloon dhore try kori, protita possible 'i' er jonno
        for(int i=left+1; i<right; i++)
        {
            // i ke shesh e burst korle, tokhon tar neighbor hobe 
            // left ar right (karon majher shob already gone)
            // tai coin = ballon[left]*ballon[i]*ballon[right]
            // + baki duita chhoto range (left,i) ar (i,right) er 
            // best answer (recursively solve)
            int coin = ballon[left]*ballon[i]*ballon[right] + solve(left, i, memo, ballon) + solve(i, right, memo, ballon);
            best = max(best, coin);
        }
        
        // ei (left, right) range er final answer memo te store
        memo[left][right] = best;
        return best;
    }
    
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        
        // notun array banai: shamne ar pichone virtual balloon "1" 
        // boshai (out-of-bound value hisebe)
        vector<int> ballon;
        ballon.push_back(1);
        for(int num : nums)
        {
            ballon.push_back(num);
        }
        ballon.push_back(1);
        // memo initialize: size (n+2) x (n+2), shob -1 (uncomputed marker)
        vector<vector<int>> memo(n+2, vector<int>(n+2, -1));
        
        // pura range solve kori: index 0 (left boundary "1") theke 
        // index n+1 (right boundary "1") porjonto
        return solve(0, n+1, memo, ballon);
    }
};
// Problem: Maximum Product Subarray
// Platform: NeetCode
// Link: https://neetcode.io/problems/maximum-product-subarray
// time complexity: O(n); where n is the length of the array. The algorithm iterates through the array once.
// space complexity: O(1); only a constant amount of extra space is used.

/*
Problem Statement

Ekটা integer array nums[] deya ache। Tomake বের korতে হবে contiguous subarray যার product maximum।

Example:

nums = [2,3,-2,4]
Output: 6

Explanation: [2,3] er product = 6, eটাই maximum
nums = [-2,3,-4]
Output: 24

Explanation: [-2,3,-4] shob miliye product = -2*3*-4 = 24
duটো negative miliye positive hoye jay!
Key Insight — কেন এটা tricky?

Sum হলে negative number সবসময় খারাপ (কমিয়ে দেয়)। Kিন্তু product এ negative number ekটা interesting twist আনে — duটো negative miliye positive হয়ে যায়!

তাই এখানে শুধু "এখন পর্যন্ত maximum product" track করলে হবে না — তোমাকে "এখন পর্যন্ত minimum product"ও track korতে হবে! কারণ jদি current number negative হয়, তাহলে আগের minimum (যেটা সম্ভবত একটা বড় negative number) কে multiply korলে সেটা নতুন maximum হয়ে যেতে পারে। 



Verify koro nums = [2,3,-2,4] diye:
maxP=2, minP=2, ans=2

i=1 (nums[1]=3):
  c1=3, c2=2*3=6, c3=2*3=6
  newMax=max(3,6,6)=6, newMin=min(3,6,6)=3
  maxP=6, minP=3
  ans=max(2,6)=6

i=2 (nums[2]=-2):
  c1=-2, c2=6*-2=-12, c3=3*-2=-6
  newMax=max(-2,-12,-6)=-2, newMin=min(-2,-12,-6)=-12
  maxP=-2, minP=-12
  ans=max(6,-2)=6

i=3 (nums[3]=4):
  c1=4, c2=-2*4=-8, c3=-12*4=-48
  newMax=max(4,-8,-48)=4, newMin=min(4,-8,-48)=-48
  maxP=4, minP=-48
  ans=max(6,4)=6

return ans=6 ✅
Verify koro nums = [-2,3,-4] diye:
maxP=-2, minP=-2, ans=-2

i=1 (nums[1]=3):
  c1=3, c2=-2*3=-6, c3=-2*3=-6
  newMax=max(3,-6,-6)=3, newMin=min(3,-6,-6)=-6
  maxP=3, minP=-6
  ans=max(-2,3)=3

i=2 (nums[2]=-4):
  c1=-4, c2=3*-4=-12, c3=-6*-4=24
  newMax=max(-4,-12,24)=24, newMin=min(-4,-12,24)=-12
  maxP=24, minP=-12
  ans=max(3,24)=24

return ans=24 ✅
*/

class Solution
{
public:
    int maxProduct(vector<int>& nums)
    {
        // maxP = current index porjonto maximum product (subarray shesh hocche ei index e)
        // minP = current index porjonto minimum product (negative*negative diye pore boro hote pare)
        // ans = overall shob theke boro product ekhon porjonto
        // shuru te shob first element diye set kora, karon single element o ekta valid subarray
        int maxP = nums[0], minP = nums[0], ans = nums[0];
        
        // loop i=1 theke shuru, karon i=0 already base case hisebe set kora
        for(int i = 1; i < nums.size(); i++)
        {
            // 3 ta candidate value calculate korchi:
            // c1: nums[i] eka - notun kore ei index theke subarray shuru kora (jodi ager product kharap hoy, tahole notun shuru kora valo)
            int c1 = nums[i];
            // c2: ager maxP er sathe multiply - jodi nums[i] positive hoy,
            //     tahole ager boro product er sathe multiply korle aro boro hobe
            int c2 = maxP * nums[i];
            // c3: ager minP er sathe multiply - jodi nums[i] negative hoy,
            //     tahole ager choto (possibly negative) product er sathe multiply korle
            //     duita negative mile positive hoye boro hoye jete pare
            int c3 = minP * nums[i];
            // temp variable e newMax, newMin store korchi
            // (direct maxP update korle, minP calculate korar somoy purono maxP pawa jabe na - bug hobe)
            int newMax = max({c1, c2, c3});
            int newMin = min({c1, c2, c3});
            
            // ekhon maxP, minP update koro notun value diye
            maxP = newMax;
            minP = newMin;
            
            // overall answer update koro, jodi current maxP boro hoy
            ans = max(ans, maxP);
        }
        return ans;
    }
};
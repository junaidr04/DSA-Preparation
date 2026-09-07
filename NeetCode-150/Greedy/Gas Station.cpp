// Problem: Gas Station
// Platform: NeetCode
// Link: https://neetcode.io/problems/gas-station
// time complexity: O(n) - Array-ta ekbar matro traverse kora hoy
// space complexity: O(1) - Shudhu ekta variable (totalGas, totalCost, currentGas) use hocche

/*
Input:
gas  = [1, 2, 3, 4, 5]
cost = [3, 4, 5, 1, 2]

Initial:
totalTank = 0, currTank = 0, start = 0
Loop (i = 0 theke i = 4 porjonto):

i	gas[i]-cost[i]	    totalTank (running)	    currTank (running)	    currTank < 0?	    Action
0	1-3 = -2	        0+(-2) = -2	            0+(-2) = -2	                Ha	        currTank=0, start = 1
1	2-4 = -2	        -2+(-2) = -4	        0+(-2) = -2             	Ha	        currTank=0, start = 2
2	3-5 = -2	        -4+(-2) = -6	        0+(-2) = -2	                Ha	        currTank=0, start = 3
3	4-1 = 3	            -6+3 = -3	            0+3 = 3	                    Na	            (kichu na, start same thake)
4	5-2 = 3	            -3+3 = 0	            3+3 = 6	                    Na	            (kichu na)

Loop shesh:

totalTank = 0  →  totalTank < 0? NA (0 negative na)
start = 3

Return start = 3 → Answer = Station 3 ✓ (age brute force e o same answer paisilam)

Step by step ki holo bujhi:

i=0,1,2: Protibar currTank -2 hoye jacche — mane Station 0, 1, 2 — kono ekta theke shuru korleo fail korbe. Tai protibar start k porer station-e sorai (start=1, tarpor start=2, tarpor start=3), ar currTank reset kore 0 kori — "fresh start, purano baggage bhule jao".
i=3: Ekhon start=3 dhore rekhe amra track korchi — Station 3 theke shuru korle ki hoy. currTank = 0+3 = 3 (negative hoyni), tai start change hoy na — mane Station 3 ekhono valid candidate hishebe tikey ache.
i=4: Station 3 theke continue kore, currTank = 3+3 = 6 (arO valo hocche, negative hoyni). Loop shesh.
Final check: totalTank = 0 — mane total gas = total cost, tai solution exist kore (negative hoyle -1 hoto).
start = 3 e loop shesh obostha e j value chilo, seta e final answer — karon eta e last "reset" howa candidate, ar tar por theke kono negative dip hoyni.
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        // totalTank = shob station miliye total gas-cost (overall possible kina check korar jonno)
        // currTank = current candidate starting point theke shuru kore ekhon porjonto obostha
        // start = candidate starting index
        int totalTank = 0, currTank = 0, start = 0;
        for (int i = 0; i <= gas.size() - 1; i++) 
        {
            totalTank += gas[i] - cost[i];
            currTank += gas[i] - cost[i];
            // jodi currTank negative hoye jay, mane 'start' theke 'i' porjonto
            // kono starting point e kaj korbe na — tai next station ke notun candidate koro
            if (currTank < 0) 
            {
                currTank = 0;
                start = i + 1;
            }
        }
        // jodi total gas total cost theke kom hoy, kono vabei possible na
        if (totalTank < 0) 
        {
            return -1;
        }
        // naile 'start' e j candidate ache shetai guaranteed valid answer
        return start;
    }
};
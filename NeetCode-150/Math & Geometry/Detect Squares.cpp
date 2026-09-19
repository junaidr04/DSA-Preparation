// Problem: Detect Squares
// Platform: NeetCode
// Link: https://neetcode.io/problems/count-squares/question
// time complexity: O(n); n = points[x] er size (same x-coordinate e koyta point ache)
// space complexity: O(k); k = total unique points added (unordered_map e store hobe)

/*
Setup — Points Add kora
cpp
add([3, 10])
add([11, 2])
add([3, 2])

Iteration 1: add([3,10])

points[3][10]++ → points[3] = {10: 1}

Iteration 2: add([11,2])

points[11][2]++ → points[11] = {2: 1}

Iteration 3: add([3,2])

points[3][2]++ → points[3] = {10: 1, 2: 1}

Final points map ekhon:

points = {
    3:  { 10: 1, 2: 1 },
    11: { 2: 1 }
}

Visualize korলে:

(3,10) ●

(3,2) ●          ● (11,2)
Call: count([11, 10])

x = 11, y = 10, total = 0

points[11] er value: {2: 1} — এখানে একটাই entry।

Loop chalabo points[11] er প্রতিটা (y2, freq) pair niye:

Iteration 1: y2 = 2, freq = 1

Check: y2 == y? → 2 == 10? → না, continue হবে না, agiye jai।

side = y2 - y = 2 - 10 = -8

প্রথম direction check (ডানে, x + side):

cpp
total += freq * points[x + side][y] * points[x + side][y2]
x + side = 11 + (-8) = 3
points[3][y] = points[3][10] → map e points[3] = {10:1, 2:1}, tাই points[3][10] = 1
points[3][y2] = points[3][2] → points[3][2] = 1
total += 1 * 1 * 1 = 1 → total = 1

দ্বিতীয় direction check (বামে, x - side):

cpp
total += freq * points[x - side][y] * points[x - side][y2]
x - side = 11 - (-8) = 19
points[19][10] → points map e 19 key exists না → default 0 return korবে (unordered_map access করলে না থাকলে auto 0 বানিয়ে দেয়)
points[19][2] → same, 0
total += 1 * 0 * 0 = 0 → total = 1 (unchanged)

Loop শেষ (আর কোনো (y2, freq) pair নেই points[11] এ)।

Return total = 1

Visual verification

Square টা যা পাওয়া গেছে (side=8 হিসেবে):

(3,10) ●―――――――● (11,10) ← query point
       |        |
(3,2)  ●―――――――● (11,2)

চারটা corner-ই already points map এ আছে ((3,10), (11,10) [query], (3,2), (11,2)), তাই এটা একটা valid axis-aligned square। Answer = 1 ✅

Ekটা aro example — jodি duplicate point thakে

Dhoro add([3,10]) আরেকবার call korি (মানে total 2 বার add হলো)।

তাহলে points[3][10] = 2 হয়ে যাবে।

count([11,10]) আবার call korলে, প্রথম direction check e:

cpp
total += freq * points[3][10] * points[3][2]
       = 1 * 2 * 1 = 2

Total এখন 2 হবে — কারণ (3,10) point টা 2 বার add হয়েছে, তাই ওই একই query point দিয়ে 2 রকম ভাবে square গঠন করা সম্ভব (যদিও geometrically একই জায়গায়, কিন্তু "কতগুলো point-combination দিয়ে square বানানো যায়" — সেই হিসেবে গণনা হয়)।

এইখান থেকে freq কেন multiply করা লাগে সেটা স্পষ্ট হয় — duplicate points থাকলে সেগুলোর প্রতিটা combination আলাদা count হয়।
*/

class CountSquares {
    unordered_map<int, unordered_map<int, int>> points;
    // 'points' ekটা map-এর-ভিতরে-map — bujhার jonno bhabo eiটা ekটা 2D table
    // points[x][y] = ei (x,y) coordinate ta koybar add() kora hoyeche (frequency)
    // Karon: same point duibar add hote pare, tai count lagbe, শুধু "আছে কিনা" (bool) na

public:
    CountSquares() {
        // Constructor — kichu initialize korার dorkar nei, tai khali
    }
    
    void add(vector<int> point) {
        points[point[0]][point[1]]++;
        // point[0] = x coordinate, point[1] = y coordinate
        // points[x][y]++ mane: ei (x,y) point ta ekbar add hoyeche, tar count 1 barao
        // (jodi age theke na thake, C++ automatically 0 diye shuru kore, tারপর ++ kore 1 বানায়)
    }
    
    int count(vector<int> point) {
        int x = point[0], y = point[1];
        // query point er x, y ber kore alada variable e rakhlam, easy access er jonno

        int total = 0;
        // koyta valid square pawa gelo, shei count rakhbe eiটা

        for (auto& [y2, freq] : points[x])
        // points[x] mane: same x-coordinate e thaka shob point (different y niye)
        // eiটা loop kore protteকটা (y2, freq) pair niye dekhchi
        // y2 = shei onno point er y-coordinate, freq = shei point koybar add hoyeche
        {
            if (y2 == y)
                continue;
            // jodi y2 == y hoy, mane eiটা query point er nijerই match (same point)
            // nijer shathe square banano jay na, tai eiটা skip kore পরের point e jao

            int side = y2 - y;
            // duita point er modhye vertical distance ta ber koro
            // eiটাই amader chaowa square-er side length (positive ba negative hote pare)

            total += freq * points[x + side][y] * points[x + side][y2];
            // Ekটা square banano jay ডানে (x + side dike):
            // - (x+side, y) point ta lagবে ekটা corner hishebe
            // - (x+side, y2) point ta lagবে arekটা corner hishebe
            // Duitাই points map e koybar ache shei count ber kore multiply korchi
            // 'freq' o multiply korchi, karon current (x,y2) point o koybar add hoyeche shetaও matter kore
            // (jemon: jodi (x,y2) 3bar add hoy, tahole 3 rokom vabe square banano jay)

            total += freq * points[x - side][y] * points[x - side][y2];
            // Same logic, kintu এবার bame dike (x - side) — karon square dui dikei banano jete pare
        }
        return total;
        // shob (y2, freq) pair check kora hoye gele, total return kore dao
    }
};
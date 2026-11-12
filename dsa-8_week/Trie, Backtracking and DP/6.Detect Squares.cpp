// Time: add O(1). count O(R), R = coordinate range, karon query er same x column er prottek y try kori.
// Space: O(R²) fixed array er jonno. Range boro hole map use kore space O(n) ar count O(k) kora jay.


/*
Dry run
add(3,10)  add(11,2)  add(3,2)
count(11,10)

qx = 11, qy = 10. Loop e i dhore dhore dekhi:

Beshirbhag i e freq[11][i] = 0 (kono point nai), tai gun 0.
i = 10: d = 0, skip.
i = 2: d = 2 - 10 = -8.
Square 1: rx = 11 + (-8) = 3. freq[11][2] * freq[3][2] * freq[3][10] = 1 * 1 * 1 = 1. ans = 1
Square 2: lx = 11 - (-8) = 19. 19 range e ache (<= 1000), kintu freq[19][2] = 0, tai gun 0.

Return 1.

Abar add(11,2) korle freq[11][2] = 2. Ekhon i = 2 e 2 * 1 * 1 = 2, return 2.

count(14, 8): freq[14][i] shob 0, tai return 0.  
*/


class DetectSquares
{
public:
    int freq[1001][1001];                 // freq[x][y] = (x,y) point ta koyta bar add hoyeche. coordinate 0..1000, tai size 1001
    DetectSquares()
    {
        memset(freq, 0, sizeof(freq));    // shuru te sob count 0. plain array auto 0 hoy na, tai memset
    }

    void add(vector<int> point)
    {
        int x = point[0], y = point[1];   // point[0] = x, point[1] = y
        freq[x][y]++;                     // count 1 bar. "= 1" na, karon duibar add hole 2 hobe, ar square gunar somoy 2 lagbe
    }

    int count(vector<int> point)
    {
        int qx = point[0], qy = point[1]; // query point Q = (qx, qy)
        int ans = 0;                      // koyta square pelam
        // Q er same x e thaka prottek point P = (qx, i) ke diagonal-er "ek dhap" dhorbo
        for (int i = 0; i <= 1000; i++)   // i = P er y coordinate, 0 theke 1000 shob try
        {
            int d = i - qy;               // side length (sign shoho). P, Q er upore hole d positive, niche hole negative
            if (d == 0)                   // P ar Q ek-i jaygay, side 0, square hoy na
                continue;                 // ei i skip
            // square 1: x = qx + d er dike ----
            int rx = qx + d;              // onno duto kona er x coordinate
            if (rx >= 0 && rx <= 1000)    // range check: baire gele freq[rx] e out of bounds crash
            {
                // 3 ta kona: P=(qx,i), (rx,i), (rx,qy). prottek ta koyta ache, shob gun
                ans += freq[qx][i] * freq[rx][i] * freq[rx][qy];
            }
            //  square 2: x = qx - d er dike (ulta dik) ----
            int lx = qx - d;              // FIX: ager bar qy + d chhilo. x coordinate, tai qx, ar dik ulta tai -d
            if (lx >= 0 && lx <= 1000)    // range check
            {
                // ager bar ans += lx chhilo. ekhane 3 ta count er gun
                ans += freq[qx][i] * freq[lx][i] * freq[lx][qy];
            }
        }
        return ans;                       
    }
};
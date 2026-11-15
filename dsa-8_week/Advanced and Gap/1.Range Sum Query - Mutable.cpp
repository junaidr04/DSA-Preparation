

// Brute force solution

class NumArray
{
public:
    vector<int> arr; // array ta ei class er vitore rakhbo, jate update ar sumRange duita function-i use korte pare

    NumArray(vector<int> &nums) // constructor: object banano matro ekbar cholbe, nums ashbe
    {
        arr = nums; // nums er copy ta amader arr e save korlam, ekhon arr amader nijer
    }

    void update(int index, int val) // void mane kichu return korbe na, shudhu change korbe
    {
        arr[index] = val; // index position er purono value muche, notun val boshalam
    }

    int sumRange(int left, int right) // left theke right porjonto sum return korbe
    {
        int total = 0; // jog-fol joma korar jonno, 0 theke shuru

        for (int i = left; i <= right; i++) // i = left theke shuru, right porjonto (<= tai right nijeo include)
        {
            total += arr[i]; // i holo position (index), arr[i] holo oi position er value. value ta total e jog hocche
        }

        return total; // sob jog shesh, answer ferot dilam
    }
};


//update: O(log n)
// sumRange: O(log n)
// Build: O(n log n)
// SC: O(n)

/*
Dry run

nums = [1, 3, 5, 7], build er pore bit = [_, 1, 4, 5, 16].

sumRange(1, 3): prefix(4) - prefix(1)

prefix(4): i=4, s = 16, i = 4 - 4 = 0, thame. Result 16.
prefix(1): i=1, s = 1, i = 0, thame. Result 1.
Answer 16 - 1 = 15 ✅

update(2, 10): delta = 10 - 5 = 5. add(3, 5):

bit[3] = 5 + 5 = 10, i = 3 + 1 = 4
bit[4] = 16 + 5 = 21, i = 8, thame.

sumRange(1, 3): prefix(4) - prefix(1) = 21 - 1 = 20 ✅ (3 + 10 + 7)

*/

class NumArray
{
public:
    int n;           // array er size
    vector<int> arr; // original value gulo, update e purono value lagbe
    vector<int> bit; // Fenwick tree, 1-indexed (index 0 ba byabohar hobe na)

    NumArray(vector<int> &nums)
    {
        n = nums.size();
        arr = nums;           // nums er copy rakhlam
        bit.assign(n + 1, 0); // n+1 size, sob 0 diye
        for (int i = 0; i < n; i++)
        {                        // protita element BIT te boshao
            add(i + 1, nums[i]); // BIT 1-indexed, tai i+1
        }
    }

    // position i (1-indexed) e delta jog koro, ar upor er ghor gulo update koro
    void add(int i, int delta)
    {
        while (i <= n)
        {                    // n porjonto
            bit[i] += delta; // ei ghor er range e delta jog
            i += i & (-i);   // porer ghor e lafao (dan er 1 bit jog)
        }
    }

    // 1 theke i porjonto sum
    int prefix(int i)
    {
        int s = 0;
        while (i > 0)
        {
            s += bit[i];   // ei ghor er range er sum jog
            i -= i & (-i); // dan er 1 bit bad dao, porer ghor e jao
        }
        return s;
    }

    void update(int index, int val)
    {
        int delta = val - arr[index]; // notun - purono = koto beshi/kom holo
        arr[index] = val;             // original array o update
        add(index + 1, delta);        // BIT e shudhu difference jog (1-indexed)
    }

    int sumRange(int left, int right)
    {
        return prefix(right + 1) - prefix(left); // [0..right] - [0..left-1], 1-indexed e
    }
};
// TC: O(E log E + Q log Q) sort er jonno, ar DSU operation prai constant (path compression diye amortized O(log n) o dhorle total same order)
// SC: O(n + Q) (parent, ans, ar query te extra element)


/*
edgeList (sorted) = [0,1,2], [1,2,4], [2,0,8], [1,0,16]
queries (sorted)  = [0,1,2,0], [0,2,5,1]

Query [0,1,2,0] (limit 2):

edgeList[0][2] = 2, 2 < 2 false, kono edge jora holo na
find(0) = 0, find(1) = 1, alada, ans[0] = false

Query [0,2,5,1] (limit 5):

Edge [0,1,2]: 2 < 5, unite(0,1), parent[0] = 1, e = 1
Edge [1,2,4]: 4 < 5, unite(1,2), parent[1] = 2, e = 2
Edge [2,0,8]: 8 < 5 false, while thame
find(0): 0 -> 1 -> 2, leader 2. find(2) = 2. Same, ans[1] = true

Return [false, true]
*/

class DSU
{
public:
    vector<int> parent;
    // parent[x] = x er "leader" ke. Example: parent = [0,1,2] mane 0,1,2 protita nijei leader

    DSU(int n)
    {
        parent.resize(n);
        // n=3 hole parent er 3 ta ghor banalo: [?, ?, ?]

        for (int i = 0; i < n; i++)
            parent[i] = i;
        // shuru te sobai nijer leader: parent = [0, 1, 2]
        // mane 3 ta shohor 3 ta alada group
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        // x jodi nijei leader na hoy, tahole oi leader er leader khuje ber kore sorasori set kore dao
        // Example: parent = [1, 2, 2]. find(0) ke dhoro:
        //   parent[0]=1 != 0, tai find(1) call
        //   parent[1]=2 != 1, tai find(2) call
        //   parent[2]=2 == 2, leader paoa gelo = 2
        //   ferot jawar somoy parent[1]=2, parent[0]=2 hoye jay (path compression)
        //   porer bar find(0) sorasori 2 dibe, chain ghurte hobe na

        return parent[x];
        // x er group er leader ferot dao. Upore find(0) = 2
    }

    void unite(int a, int b)
    {
        parent[find(a)] = find(b);
        // a er group er leader ke b er group er leader er niche boshao, mane duita group ek hoye gelo
        // Example: parent=[0,1,2], unite(0,1):
        //   find(0)=0, find(1)=1, tai parent[0] = 1
        //   ekhon parent = [1,1,2], mane 0 ar 1 ek group, leader 1
    }
};

class Solution
{
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries)
    {
        sort(edgeList.begin(), edgeList.end(), [](vector<int>& a, vector<int>& b)
        {
            return a[2] < b[2];
        });
        // edge gulo dairgho (index 2) diye chhoto theke boro sajalam
        // Example: shuru [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], dairgho 2,4,8,16 already sorted, tai same thakbe
        for (int j = 0; j < queries.size(); j++)
        {
            queries[j].push_back(j);
        }
        // protita query r shesh e tar original position jog korlam, karon pore sort korle order ulte jabe
        // Example: [[0,1,2],[0,2,5]] hoye jay [[0,1,2,0],[0,2,5,1]]
        // format ekhon [p, q, limit, j]
        sort(queries.begin(), queries.end(), [](vector<int>& a, vector<int>& b)
        {
            return a[2] < b[2];
        });
        // query gulo limit (index 2) diye chhoto theke boro sajalam
        // Example: limit 2 ar 5, already sorted, tai change nai
        // (onno example: limit 9 age, limit 3 pore thakle sort e 3 age ashto, tai j lagto)
        DSU dsu(n);
        // n=3 ta shohor, parent = [0,1,2], sobai alada

        int e = 0;
        // edge pointer. e=0 mane "ekhono kono edge jora lagai nai"
        // protita edge shudhu ekbar-i dekha hobe, tai TC bhalo

        vector<bool> ans(queries.size());
        // 2 ta query, tai ans = [false, false] (shuru te). Pore sothik value boshbe
        for (auto& q : queries)
        {
            // q holo ekta ekta query, chhoto limit theke shuru
            // prothom q = [0,1,2,0], tarpor q = [0,2,5,1]
            while (e < edgeList.size() && edgeList[e][2] < q[2])
            {
                dsu.unite(edgeList[e][0], edgeList[e][1]);
                e++;
            }
            // jotokkon edge ache (e < 4) ar tar dairgho limit er cheye choto (strictly <), tar jora lagao
            // `while` keno: ekta query te onek edge ekshathe jora lagte pare

            // Query 1: q=[0,1,2,0], limit=2
            //   e=0: edgeList[0][2]=2, 2 < 2 false, while shuru-i hoy na
            //   kono edge jora holo na, parent = [0,1,2]

            // Query 2: q=[0,2,5,1], limit=5
            //   e=0: dairgho 2 < 5 true, unite(0,1), parent=[1,1,2], e=1
            //   e=1: dairgho 4 < 5 true, unite(1,2), parent=[1,2,2], e=2
            //   e=2: dairgho 8 < 5 false, while thame
            ans[q[3]] = (dsu.find(q[0]) == dsu.find(q[1]));
            // q[0]=p, q[1]=q (duita shohor), q[3]=original index
            // p ar q ek group e thakle true, na hole false. Answer original position e boshbe

            // Query 1: find(0)=0, find(1)=1, alada, false, ans[q[3]=0] = false
            // Query 2: find(0)=2, find(2)=2, same, true, ans[q[3]=1] = true
        }
        return ans;
        // ans = [false, true], expected-er sathe mile gelo
    }
};
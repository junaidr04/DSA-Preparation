// Time: O(E log V); V = n, E = times.size(). Prottek edge theke dhoro ekbar pq.push hote pare, ar heap e push/pop e log lage (heap er size E porjonto bare, log E ar log V ek-i order er).
// Space: O(V + E); adj e O(V + E), dist e O(V), pq e worst case O(E).


/*
Input: n = 3, k = 1, times = [[1,2,10], [1,3,1], [3,2,1]]

Shuru-r obostha (graph toiri shesh):

adj[1] = { (2, 10), (3, 1) }     // 1 theke 2 e 10 sec, 1 theke 3 e 1 sec
adj[2] = { }                     // 2 theke kothao jay na
adj[3] = { (2, 1) }              // 3 theke 2 e 1 sec

dist = [ -,  0,  INF, INF ]      // index 1, 2, 3 (dist[0] fake)
pq   = { (0,1) }                 // (time, node)

Iteration 1: pq theke ber holo (0,1), mane d=0, u=1.

d > dist[1]? 0 > 0 na, tai skip hobe na.
Neighbour (2, 10): dist[1] + 10 = 10 < INF, tai dist[2] = 10, push (10,2).
Neighbour (3, 1): dist[1] + 1 = 1 < INF, tai dist[3] = 1, push (1,3).
dist = [ -, 0, 10, 1 ]
pq   = { (1,3), (10,2) }         // choto time age ber hobe

Iteration 2: ber holo (1,3), mane d=1, u=3. Dekho, 10 na, 1 age ashlo, kom time bole.

1 > dist[3]? 1 > 1 na, skip na.
Neighbour (2, 1): dist[3] + 1 = 2 < dist[2] = 10, tai update: dist[2] = 2, push (2,2).
dist = [ -, 0, 2, 1 ]
pq   = { (2,2), (10,2) }         // node 2 er duto entry

Iteration 3: ber holo (2,2), mane d=2, u=2.

2 > dist[2]? 2 > 2 na, skip na.
adj[2] khali, kono neighbour nei.
pq   = { (10,2) }

Iteration 4: ber holo (10,2), mane d=10, u=2.

10 > dist[2]? 10 > 2 ha, tai continue. Eta purono entry, process kora hoy na.
pq   = { }                        // khali, while shesh

Answer er loop:

dist = [ -, 0, 2, 1 ]
i=1: dist=0, INT_MAX na, ans = max(0,0) = 0
i=2: dist=2, INT_MAX na, ans = max(0,2) = 2
i=3: dist=1, INT_MAX na, ans = max(2,1) = 2
return 2  
*/

class Solution
{
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k)
    {
        // node 1 theke n (1-indexed), tai size n + 1
        // adj[u] = u theke jaoa line gulo: {kon node e, koto second}
        vector<vector<pair<int,int>>> adj(n + 1);
        for (auto& t : times)
        {
            int u = t[0], v = t[1], w = t[2];   // u -> v, w second (ekmukhi)
            adj[u].push_back({v, w});           // v ar w duto-i rakhlam
        }
        // dist[x] = k theke x e pouchanor shobcheye kom shomoy (ekhon porjonto jani)
        // shuru te shob INT_MAX, mane "ekhono pouchai ni"
        vector<int> dist(n + 1, INT_MAX);
        // signal k theke-i shuru, tai k te pouchate 0 second
        dist[k] = 0;
        // min-heap: shobcheye choto time er node ta age ber hoy
        // element: {time, node}
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0, k});
        while (!pq.empty())
        {
            // shobcheye choto time er node ta nilam
            auto [d, u] = pq.top();
            pq.pop();
            // purono, beshi time er entry hole skip (dist[u] age-i kom e update hoye geche)
            if (d > dist[u])
                continue;
            // u theke jara pashe, tader shomoy update korar chesta
            for (auto [v, w] : adj[u])
            {
                // u diye gele v e kom shomoy lage? tahole update
                // (dist[u] INT_MAX na, karon u queue theke ber hoyeche, tai overflow nei)
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});   // notun shomoy diye push
                }
            }
        }   
        // shob node er moddhe shobcheye deri te je node pay, tar shomoy-i answer
        int ans = 0;
        for (int i = 1; i <= n; i++)   // 1 theke, karon dist[0] fake slot
        {
            // kono node e signal na pouchale -1
            if (dist[i] == INT_MAX)
                return -1;
            // shobcheye boro dist (jog na, karon alada shakha ek shathe chole)
            ans = max(ans, dist[i]);
        }
        return ans;
    }
};
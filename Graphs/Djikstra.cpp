#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define vpii vector < pair <int,int> >
#define pii pair<int,int>
#define mem(a,val) memset(a,val,sizeof(a))
#define ff first
#define ss second
#define FOR(i,k,n) for ( int i=k; i<n; i++ )

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 1e5 + 5;

vpii adj[N];
bool vis[N];
int d[N];

priority_queue<pii, vector<pii>, greater<pii>> PQ; 

/**
 * @brief Djikstra
 * 
 * Djistra is used as  BFS for a weighted graph.
 * The differnce between Djikstra and standard BFS is the Djikstra uses Priority Queue
 * instead of a standard queue. The standard queue is sorted according to minimum value
 * of pair. The pair passes its first value for comparison which contains the distance
 * of the node from the source. Here, we store the weight as a distance for ease of 
 * understanding.
 * 
 * So, firstly we take the source node and push it to the PQ with {0,node}. Remember that
 * the priority queue stores the elements in the order { distance_from_source,node } sorted
 * in order of increasing distance_from_source. 
 * 
 * While the queue is not empty, we pop the first element. If the element is already visited
 * (not evaluated), we skip the element. Next, we loop over all its neghbours from the
 * adjacency list. Here too, we check if the neighbour is visited, we skip it. If not, we check
 * if we can improve the minimum distance by checking whether its distance from the node 
 * ( d[node] + distance of the neightbour from node ) is less that the distance of neighbour from
 * source. If yes, we overrite the new distance with the smaller one. This is done until the PQ
 * is empty or all the nodes are visited.
 * 
 * In standard BFS, we marked a node visited inside the node evaluation ( inside element loop of adj list ) 
 * because we only visited an element once, That once was always the smallest path, but this isn't the case
 * with weighted graph. Hence, the need of Djikstra developed.
 * 
 * @param src 
 */

void djikstra(int src) {

    int u,v,w;
    d[src] = 0;

    PQ.push({0, src});

    while(!PQ.empty()) {
        u = PQ.top().second;
        PQ.pop();
        if(vis[u])  continue;
        vis[u] = 1;
        for(auto &x : adj[u]) {
            w = x.ss;
            v = x.ff;
            if(vis[v]) continue;
            if(d[v] > d[u] + w) { 
                d[v] = d[u] + w;
                PQ.push({d[v], v});
            }
        }
    }

}

int main(){
    adj[1] = { {2,4},{5,20} };
    adj[2] = { {1,4},{3,5},{4,3} };
    adj[3] = { {2,5},{5,6} };
    adj[4] = { {2,3},{5,15} };
    adj[5] = { {1,20},{4,15},{3,6} };

    mem(vis, 0);

    FOR(i,1,6)
        d[i]=INT_MAX;

    djikstra(1);
    cout<<d[5];                 // 15   =   min( 4+5+6 , 20 , 4+3+15 )
}

//                  The Graph is represented as follows

//
//                               4          5                         
//                           1--------2---------3 
//                            \       |        /
//                             \      | 3     / 
//                              \     |      /
//                            20 \    4     /
//                                \   |    / 6
//                                 \  |15 /  
//                                  \ |  /
//                                   \| /
//                                    5                                            

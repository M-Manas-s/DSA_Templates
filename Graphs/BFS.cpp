#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define mem(a,val) memset(a,val,sizeof(a))

const int N = 1e5 + 5;

vi adj[N];     //  adjacency list
bool vis[N];            //  visited array
int d[N];               //  distance array

/**
 * @brief Breadth First Search
 * 
 * Here, we maintain a queue and push the source into it initially. The queue is then popped and 
 * the popped element is stored. The popped element is marked visited and we iterate over all the
 * connected nodes of the popped element and push it to the queue.
 * 
 * For the distance part, first we set the distance of source as 0. Now, as the queue is popped first,
 * we set the distance of all the connected nodes from soruce to d[src] + 1 and the child is pushed
 * into the queue. This similarly continues until we visit all the nodes in the graph. We skip the 
 * distance calculation and queue push part if the node is already visited.
 * 
 * BFS is basically exploring the graph breadth by breadth. Simply put, it is like a circle growing in
 * radius or water spreading from a point source.
 * 
 * @param src Source from where bfs has to be started in the Graph
 */

void bfs(int src)
{
    mem(vis,0);
    int u;
    queue<int> Q;
    d[src] = 0;
    vis[src] = 1;
    Q.push(src);
    while(!Q.empty()) {
        u = Q.front(); 
        cout<<u<<' ';
        Q.pop();
        for(auto v : adj[u]) {
            if (vis[v] == 0) {
                d[v] = d[u] + 1;
                vis[v] = 1;
                Q.push(v);
            }
        }
    }
    cout<<endl;
}

int main() {

    adj[1] = {2,3,6};
    adj[2] = {1,3,5};
    adj[3] = {2,4};
    adj[4] = {3,5};
    adj[5] = {2,4};
    adj[6] = {1};

    bfs(1);             // 1 2 3 6 5 4
    bfs(5);             // 5 2 4 1 3 6
}

//                  The Graph is represented as follows

//
//                               5--4
//                               |  | 
//                               |  |                                     
//                       6---1---2--3 
//                            \    /      
//                             \__/     
//   
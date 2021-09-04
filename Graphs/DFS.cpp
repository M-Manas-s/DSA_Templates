#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define mem(a,val) memset(a,val,sizeof(a))

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 1e5 + 5;

bool vis[N];    // visited array
vi adj[N];      // adjacency list

/**
 * @brief Depth First Search
 * 
 * DFS revolves around searching children of a nodes completely then backtracking back to
 * the parent node again to explore furthur non-visited children.
 * 
 * To do this, simply start the dfs from a source marking it as visited inside the dfs
 * function. Now loop over all the children of the node and do a dfs if not visited.
 * 
 * DFS is basically exploring the graph by depth first. Simply put, it is like a maze runner
 * running a branch of the maze then coming back to the starting point.
 * 
 * @param v 
 */

void dfs(int v) {
    vis[v] = true;
    cout<<v<<' ';
    for (int u : adj[v]) {
        if (!vis[u])
            dfs(u);
    }
}

int main() {

    adj[1] = {2,3,6};
    adj[2] = {1,3,5};
    adj[3] = {2,4};
    adj[4] = {3,5};
    adj[5] = {2,4};
    adj[6] = {1};

    mem(vis,false);
    dfs(1);              // 1 2 3 4 5 6
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
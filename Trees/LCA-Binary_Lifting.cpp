#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define vi vector<int>
#define pb(x) push_back(x)
#define FOR(i,k,n) for ( int i=k; i<n; i++ )
#define ROF(i,k,n) for ( int i=k; i>n; i-- )

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int timer;                      // timer -> Used to record time for evaluation of Euler tour
int l;                          // l -> Logarithmic limit of parents
int size;                       // size -> Size of up array (use size+1 in main for 1-based tree)
vector<int> tin, tout;          // tin,tout -> time when dfs for that node started and ended respectively
vector<vector<int>> up;         // up -> Stores ancestors of node in the power of 2
vi adj[100005];                 // adj -> adjacency list

/**
 * @brief Assigns the ancestors to the up vector to respective node. The ith ancestor is 2^ith parent of that node.
 * Uses Euler tour to decide whether a node is a child/ancestor of another node.
 * 
 * up[node][0] = parent (2^th = 1st Parent)
 * 
 * up[node][1] = up[up[node][0]][0] = up[parent][0] (2^1th = 2nd parent = Grandparent)
 *      up[node][0] is Parent
 *      up[parent][0] is Parent's Parent
 *      up[up[node][0]][0] is Grandparent of that node
 *
 * 
 * up[node][2] = up[up[node][1]][1] = up[Grandparent][1] (2^th = 4th parent = Grandparent's Grandparent )
 *      up[node][1] is Grandparent
 *      up[Grandparent][1] = Grandparent of Grandparent
 * 
 * This goes on until the logarithmic limit l is reached
 * 
 * 
 * @param v Node
 * @param p Parent
 */

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    FOR(i,1,l+1)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : adj[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
}

/**
 * @brief Evaluates Euler tour based on tin and tout
 * An ancestor of a node will tour in before the child and leave after the child
 * 
 * @param u Ancestor Node
 * @param v Child Node
 * @return true if u is an ancestor of v
 * @return false if u is not an ancestor of v
 */

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

/**
 * @brief Calculates lca of the passed node with the pre-processed Binary Lifting array
 * if any node is ancestor of the other already, return that
 * 
 * Starts comparing both the nodes for ancestral relation from the 2^l th Parent of Node 1
 * If say Node 1 is already an ancestor, the loop iterates down the 2^i th Parent until it is not an ancestor anymore
 * When the ancestral relation is disrupted Node 1 changes itself to 2^i th Parent of itself 
 * The function ensures that Node 1 ends with the child of LCA, then the parent is returned
 * 
 * @param u Node 1
 * @param v Node 2
 * @return int LCA
 */

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    ROF(i,l,-1) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

/**
 * @brief Preprocesses 'up' vector for finding LCA 
 * 
 * @param root Root of the Tree
 */

void preprocess(int root) {
    tin.resize(size);
    tout.resize(size);
    timer = 0;
    l = ceil(log2(size));
    up.assign(size, vector<int>(l + 1));
    dfs(root, root);
}

int main(){

    size = 9;

    int a[16] = {                                
        1 , 2,                             
        1 , 3,
        3 , 4,
        3 , 5,
        2 , 6,
        4 , 7,
        5 , 8,
        6 , 9,
    };

    FOR(i,0,size-1)
    {
        int x=a[2*i],y=a[2*i+1];
        adj[x].pb(y);
        adj[y].pb(x);
    }
    size++;
    preprocess(1);
    cout<<lca(7,5)<<endl;   // 3
    cout<<lca(5,6)<<endl;   // 1
    cout<<lca(5,8)<<endl;   // 5
}

//                     The following tree is coded above

//                                           1
//                                         /   \ 
//                                        2     3
//                                      /     /  \
//                                     6     4    5
//                                    /       \    \
//                                   9         7    8
//
//

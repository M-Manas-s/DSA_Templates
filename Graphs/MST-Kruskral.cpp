#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define pb(x) push_back(x)
#define all(c) c.begin(),c.end()
#define mem(a,val) memset(a,val,sizeof(a))
#define FOR(i,k,n) for ( int i=k; i<n; i++ )
#define each(x,a) for (auto &x : a)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<int> parent, size_;

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void make_set(int v) {
    parent[v] = v;
    size_[v] = 1;
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size_[a] < size_[b])
            swap(a, b);
        parent[b] = a;
        size_[a] += size_[b];
    }
}

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

vector<Edge> edges,result;

int Kruskral(int n) {
    int cost = 0;
    parent.resize(n);
    size_.resize(n);
    for (int i = 0; i < n; i++)
        make_set(i+1);

    sort(all(edges));

    each(e,edges) {
        if (find_set(e.u) != find_set(e.v)) {
            cost += e.weight;
            result.push_back(e);
            union_sets(e.u, e.v);
        }
    }

    return cost;
}

signed main(){
    int n=5,m=7;
    int adj[m][3] = {
        {1,2,1},
        {1,5,2},
        {1,3,5},
        {2,3,3},
        {2,4,4},
        {3,4,9},
        {2,5,15}
    };
    FOR(i,0,m) {
        Edge e;
        e.u=adj[i][0];
        e.v=adj[i][1];
        e.weight=adj[i][2];
        edges.pb(e); 
    }
    Kruskral(n);
    each(e,result) cout<<e.u<<' '<<e.v<<endl;
    // 1 2
    // 1 5
    // 2 3
    // 2 4
}

//                 5
//             2 /  \ 15
//              / 1  \ 
//             1-----2
//            /      /\
//          5 \    /3  \ 4
//            \  /      \
//             3--------4
//                  9
//
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define vi vector<int>
#define vll vector<ll>
#define vvi vector < vi >
#define vpii vector < pair <int,int> >
#define pb(x) push_back(x)
#define pii pair<int,int>
#define pll pair<long long, long long>
#define all(c) c.begin(),c.end()
#define mp(x,y) make_pair(x,y)
#define mem(a,val) memset(a,val,sizeof(a))
#define eb emplace_back
#define ff first
#define ss second
#define lc(p) (p << 1)
#define rc(p) (p << 1) | 1
#define ps(x, y) fixed << setprecision(y) << x
#define mk(arr, n, type) type *arr = new type[n]
#define range(a, b) substr(a, b - a + 1)
#define trace(x) cerr << #x << ": " << x << endl
#define FIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define input(arr,n) FOR(i,0,n) cin>>arr[i]
#define FOR(i,k,n) for ( int i=k; i<n; i++ )
#define ROF(i,k,n) for ( int i=k; i>n; i-- )
#define ll long long
#define casePrint(x,y) cout<<"Case #"<<x<<": "<<y;
#define each(x,a) for (auto &x : a)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define max_size 100000
int parent[max_size];
int size_[max_size];

/**
 * @brief Finds the parent as well as compresses the path
 * 
 * @param v child whose parent is to be found
 * @return int parent
 */

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

/**
 * @brief Initialises the child as their own parent with a size of 1
 * 
 * @param v 
 */

void make_set(int v) {
    parent[v] = v;
    size_[v] = 1;
}

/**
 * @brief Union two differnet sets
 * 
 * Finds the parent of two child, the parent with the maximum children (size) is picked.
 * That parent is made the parent of the other child as well.
 * 
 * @param a Child a
 * @param b Child b
 */

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

signed main(){
    int arr[5] = {12,34,54,12,345};

    FOR(i,0,5)
        make_set(i);
    
    union_sets(0,1);
    union_sets(1,2);
    union_sets(3,4);

    cout<<find_set(4)<<endl; // 3
    cout<<find_set(2)<<endl; // 0
    cout<<find_set(1)<<endl; // 0
}

//     0         3
//    / \        / 
//   1  2        4
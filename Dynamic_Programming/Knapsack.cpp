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
#define each(a,x) for (auto &x : a)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Standard 0-1 knapsack top-down

// Input
// T
// n W  
// v1 v2 v3 ... vn
// w1 w2 w3 ... wn

void fnc()
{
    int n,W;
    cin>>n>>W;
    vi v(n),w(n);

    FOR(i,0,n)
        cin>>v[i];
    FOR(i,0,n)
        cin>>w[i];
    
    int dp[n+1][W+1];
    mem(dp,-1);

    FOR(i,0,n+1)
        dp[i][0] = 0;
    FOR(i,0,W+1)
        dp[0][i] = 0;

    FOR(i,1,n+1) FOR(j,1,W+1)
    {
        if ( w[i-1]<=j )
            dp[i][j] = max( dp[i-1][j], v[i-1]+ dp[i-1][j-w[i-1]] );
        else
            dp[i][j] = dp[i-1][j];
    }
    FOR(i,0,n+1) 
    {
    FOR(j,0,W+1)
        cout<<dp[i][j]<<' ';
    cout<<endl;
    }
}

signed main(){
    FIO;
    int n;
    cin>>n;
    FOR(i,0,n)
    {
        fnc();
        cout<<"\n";
    }
}
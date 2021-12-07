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

// Given an array of positive integers, find out if a particular sum is possible out of all subsets

// Input
// T
// n sum
// a1 a2 a3 ... an

// Output
// YES or NO

void fnc()
{
    int n,sum;
    // Time complexity is - O(n*sum);
    cin>>n>>sum;
    vi a(n);
    input(a,n);
    bool dp[n+1][sum+1];

    FOR(i,0,sum+1)
        dp[0][i] = false;
    FOR(i,0,n+1)
        dp[i][0] = true;
    
    FOR(i,1,n+1) FOR(j,1,sum+1)
    {
        if ( a[i-1] <= j )
            dp[i][j] = dp[i-1][j] || dp[i-1][j-a[i-1]];
        else
            dp[i][j] = dp[i-1][j];
    }
    cout<<(dp[n][sum]?"YES":"NO");

    // dp table
    // FOR(i,0,n+1) FOR(j,0,sum+1)
    //     cerr<<dp[i][j]<<" \n"[j==sum];
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
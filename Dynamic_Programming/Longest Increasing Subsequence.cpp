#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define vi vector<int>
#define FIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define FOR(i,k,n) for ( int i=k; i<n; i++ )

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

/**
 * @brief Binary Search the index to replace
 * 
 * @param a array
 * @param r right limit
 * @param key key to be searched
 * @param l left limit
 * @return int index to be replaced
 */

int BS(vi &a, int r, int key,int l=0)
{
    while(l<=r)
    {
        int mid=(l+r)/2;
        if (a[mid]>key)
            r=mid-1;
        else
            l=mid+1;
    }
    return l;
}

/**
 * @brief   Return length of LIS. ALso remember that tail array contains tails
 *          of the largest subsequence of that length, ending with smallest tail
 *          possible. It does not contain the actual subsequence itself.
 * 
 * @param v vi whose LIS has to be calculated
 * @return int length of LIS
 */

int LIS(vi &v)
{
	if (v.size() == 0) return 0;

	vi tail(v.size(), 0);
	int length = 1;

	tail[0] = v[0]; // assuming starting element to be a part of LIS

	FOR(i,0,v.size()) 
    {

		// If smaller than the tail of a sequence of existing length,
        // replace it
		if (v[i] < tail[0])
			tail[0] = v[i];

		// If larger than the tail of largest sequence, add new sequence
		else if (v[i] > tail[length - 1])
			tail[length++] = v[i];

		// Replaces the sequence with tail just greater than v[i]
		else
			tail[BS(tail,length, v[i])] = v[i];

	}

	return length;
}

signed main()
{
    FIO;
	vi v{ 2, 5, 3, 7, 11, 4, 10, 13, 6 };
	std::cout << "Length of Longest Increasing Subsequence is "
			<< LIS(v) << '\n';
	return 0;
}

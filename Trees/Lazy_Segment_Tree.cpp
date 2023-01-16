#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define vt vector
#define vi vt<int>

/**
 * @brief minimalistic Segment Tree with lazy propagation
 * 
 */

namespace ST
{
    /**
     * @brief   t represents the segment tree
     *          lazy is used to either mark or store lazy loading values
     * 
     */
    vi t, lazy;

    /**
     * @brief Build the tree like a normal segment tree
     * 
     * @param v Tree Index
     * @param tl Tree left range
     * @param tr Tree right range
     * @param arr array over which Segment Tree has to be built
     */
    void build(int v, int tl, int tr, vi &arr)
    {
        if (tl > tr)
            return;
        if (tl == tr) {
            t[v] = arr[tl];
            return;
        }
        int mid = (tl + tr) / 2;
        build(2 * v, tl, mid, arr);
        build(2 * v + 1, mid + 1, tr, arr);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    /**
     * @brief initialises the tree vectors and builds the tree
     * 
     * @param arr The array over which segment tree has to be built
     */
    void init(vi arr)
    {
        int N = arr.size();
        t.resize(4 * N);
        lazy.resize(4 * N);
        build(1, 0, N - 1, arr);
    }

    /**
     * @brief Performs lazy update on the child nodes and unmarks the parent
     * 
     * Lazy update updates the child with lazy values and unmarks the parent.
     * In sum Segment Tree, where we are updating a range with a specific value,
     * the child will always be divided equally with parent values.
     * 
     * @param v Tree index
     */
    void lazyUpdate(int v)
    {
        if (lazy[v])
        {
            t[v * 2] = t[v * 2 + 1] = t[v]/2;
            lazy[v * 2] = lazy[v * 2 + 1] = true;
            lazy[v] = false;
        }
    }

    /**
     * @brief Updates the Segment Tree lazily, ie if a certain rain coincides completely
     * within the current range of the node, it stops then and there and marks itself as
     * lazy. Otherwise, it updates its children with values and unmarks itself as lazy.
     * 
     * @param v Tree Index
     * @param tl Current node's left range
     * @param tr Current node's right range
     * @param ql Query's left range
     * @param qr Query's right range
     * @param val The value to be updated with
     */

    void update(int v, int tl, int tr, int ql, int qr, int val)
    {
        if (tr < ql || qr < tl)
            return;
        if (ql <= tl && tr <= qr)
        {
            t[v] = ( tr - tl + 1 ) * val;
            lazy[v] = 1;
            return;
        }
        lazyUpdate(v);
        int mid = (tl + tr) / 2;
        update(2 * v, tl, mid, ql, qr, val);
        update(2 * v + 1, mid + 1, tr, ql, qr, val);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    /**
     * @brief Standard Segment Tree query, just that everytime you query deep into
     * a range, you try to upload the values that was sitting lazily. This never
     * comprimises the time complexity, but instead updates the tree deeper only when
     * we want.
     * 
     * @param v The current Tree index
     * @param tl Current node's left range
     * @param tr Current node's right range
     * @param ql Query's left range
     * @param qr Query's right range
     * @return int The query required
     */

    int query(int v, int tl, int tr, int ql, int qr)
    {
        if (tr < ql || qr < tl)
            return 0;
        if ( ql <= tl && tr <= qr)
            return t[v];

        lazyUpdate(v);
        int mid = (tl + tr) / 2;
        return query(2 * v, tl, mid, ql, qr) +
               query(2 * v + 1, mid + 1, tr, ql, qr);
    }
};

signed main()
{
    vi a = {2, 4, 5, 6, 7, 5, 4, 3};
    int n = 8;
    ST::init(a);
    cout << ST::query(1, 0, n - 1, 0, 4) << endl;       // gives 24 (2+4+5+6+7)
    ST::update(1, 0 , n-1, 0, 4 , 10);                  // changes first 5 elements to 10
    cout << ST::query(1, 0, n - 1, 0, 2) << endl;       // gives 30 (10+10+10)
    ST::update(1, 0 , n-1, 1, 3 , 5);                   // changes [1,3] elements to 5
    ST::update(1, 0 , n-1, 7, 7 , 17);                  // changes last element to 17
    for (int i=0; i<n; i++ )                            // print the array
        cout << ST::query(1,0,n-1,i,i) << ' ';          // 10 5 5 5 10 5 4 17
}
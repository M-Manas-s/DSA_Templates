#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define vt vector
#define vi vt<int>
#define each(x, a) for (auto &x : a)

struct ST
{
    vi t,arr;                               // t -> ST, arr-> original array
    int n,ignore_val;                       // n-> size of ST, ignore_val->the value to be passed from dead node
    bool one_indexed;                       // Boolean specifying whther ST is 1-based
    std::function< int(int,int) > combine;  // Combine function for combining two nodes

    /**
     * @brief Left Child
     * 
     * @param p Parent Index
     * @return int Right Child index, 2*p+1 in case of 0 based index else 2*p
     */
    int lc(int p){
        return (p << 1) + (1-one_indexed);
    }

    /**
     * @brief Right child
     * 
     * @param p Parent index
     * @return int Right child index, 2*(p+1) in case of 0 based index else 2*p +1
     */
    int rc(int p){
        return ((p << 1) | 1) + (1-one_indexed);
    }
    
    /**
     * @brief Construct a new ST object from an array
     * 
     * @param A     Array to be used for construction
     * @param cmb   Combine function, defaults to sum
     * @param igv   Ignore value or the value to be passed from dead node, defaults to zero
     * @param o_i   boolean representing whether the tree is one indexed, defaults to 1 (1-based index)
     */
    ST(vi &A,std::function< int(int,int) > cmb = [](int a,int b){return a+b;},int igv=0,bool o_i=1) 
    {
        arr=A;
        n = A.size();
        one_indexed = o_i;
        t.assign(4 * n + 5, 0);
        ignore_val = igv;
        combine = cmb;
        build();
    }

    /**
     * @brief Build the ST
     * 
     * @param v     ST Index
     * @param tl    tree left
     * @param tr    tree right 
     */
    void build(int v, int tl, int tr)
    {
        if (tl == tr)
        {
            t[v] = arr[tl];
            return;
        }

        int tm = (tl + tr) >> 1;
        int l = lc(v);
        int r = rc(v);
        build(l, tl, tm);
        build(r, tm + 1, tr);
        t[v] = combine ( t[l] , t[r] );
    }

    void build()
    {
        build(one_indexed,0,n-1);
    }

    /**
     * @brief Point update the ST in orignal array index pos with val x
     * 
     * @param v     ST index
     * @param pos   postion in original array
     * @param x     new value
     * @param tl    tree left
     * @param tr    tree right
     */
    void update( int v, int pos, int x, int tl, int tr ) 
    {
        if ( tl > pos || tr < pos ) return;

        if (tl == tr) {
            t[v] = x;
            return;
        }

        int tm = (tl + tr) / 2;
        int l = lc(v);
        int r = rc(v);
        update(l, pos, x,  tl, tm);
        update(r, pos, x,  tm+1, tr);
        t[v] = combine( t[l] , t[r] );
    }

    void update(int pos,int x)
    {
        update(one_indexed,pos,x,0,n-1);
    }

    /**
     * @brief Query the ST in range [ql,qr]
     * 
     * @param v ST index
     * @param ql query left
     * @param qr query right
     * @param tl tree left
     * @param tr tree right
     * @return int Query value
     */
    int query( int v,int ql, int qr, int tl, int tr) 
    {
        if (tl > qr || tr < ql) 
            return ignore_val;
        if (ql > qr) 
            return ignore_val;
        if ( tl >= ql && tr <= qr) {
            return t[v];
        }

        int tm = (tl + tr) >> 1;
        int l = lc(v);
        int r = rc(v);
        int L = query( l, ql, qr, tl, tm);
        int R = query( r, ql, qr, tm+1, tr);

        return combine(L,R);
    }

    int query(int ql,int qr)
    {   
        return query(one_indexed,ql,qr,0,n-1);
    }

    /**
     * @brief Any custom function
     * 
     * @param v ST index
     * @param ql query left
     * @param qr query right
     * @param tl tree left
     * @param tr tree right
     */
    void custom( int v,int ql, int qr, int tl, int tr){
        return;
    }

    void custom(int ql,int qr){
        return custom(one_indexed,ql,qr,0,n-1);
    }

};

signed main()
{
    auto cmb = [&] (int a,int b){
        return (a+b);
    };
    vi a = {1,2,3,4,5,6,7,8};

    ST st(a,cmb,0,1);
    each(x,st.t) cout<<x<<' ';
    cout<<endl;
    cout<<(st.query(3,5))<<endl;    // 15
    st.update(3,10);                // 4 -> 10
    each(x,st.t) cout<<x<<' ';
    cout<<endl;
    cout<<(st.query(3,5));           // 21
}
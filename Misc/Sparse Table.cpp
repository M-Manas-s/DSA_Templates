#include <bits/stdc++.h>

using namespace std;

/**
 * @brief Sparse Table
 * 
 * Sparse Table is a unique data structure that stores the information
 * for range of lengths of powers of 2, ie. 1,2,4,8,.. from each index.
 * This helps us make range queries in O(log(n)) time but adds a space
 * overhead of O(n*log(n)).
 * 
 * For exmaple, let's consider an array of length 10 (0-based indexing).
 * So, index 3 will store the information of ranges -
 *      1)  [3,3]
 *      2)  [3,4]
 *      3)  [3,6]
 * The next range will be [3,11] which will go out of bounds, so we don't 
 * store that. So, each index stores log(n) numbers.
 * 
 * @tparam T Template class for the data stores
 * @tparam function<T(const T&,const T&)> Function that combines the ranges
 */

template <typename T,class F = function<T(const T&,const T&)>>



struct SparseTable {
    
    /**
     * @brief 
     * 
     * @param n The size of array
     * @param mat The sparse table matrix
     * @param func  The combine function
     * @param ignore_val Ignore value, defaults to zero
     */

    int n;
    vector<vector<T>> mat;
    F func;
    int ignore_val;

    /**
     * @brief Construct a new Sparse Table object
     * 
     * The Sparse table can be built using Dynamic Programming where we
     * first build the table for length of k, then use it build table for
     * length of 2*k, by combining the two range of length k and k.
     * 
     * The matrix dimensions are matrix[log(range)][index]
     * 
     * @param a The array over which sparse table has to constructed
     * @param f The combine function
     * @param igv Ignore value
     */

    SparseTable(const vector<T> &a, const F &f,const T &igv = 0) : func(f) {
        n = static_cast<int>(a.size());
        ignore_val = igv;
        int max_log = 32 - __builtin_clz(n);
        mat.resize(max_log);
        mat[0] = a;
        for ( int j = 1; j < max_log; j++ ) {
            mat[j].resize(n - (1 << j) + 1);
            for ( int i = 0; i<= n - (1 << j); i++ )
                mat[j][i] = func(mat[j-1][i], mat[j-1][i+ (1 << (j-1))]);
        }
    }

    /**
     * @brief This function is specifically written to perform Range Maximum 
     * or Range Minimun queries.
     * 
     * RMQ is the biggest advantage of a Sparse Table as it can be computed 
     * in contant time. This is so because, overlapping ranges never pose
     * a problem in RMQ. On the other hand, overlapping ranges might pose a 
     * problem in range queries like sum queries, where we will count the
     * overlapping ranges again.
     * 
     * Let's say you want to calcualte the RMQ for range [3,15]. The value 
     * can be calculates as -
     *      RMQ( [3,3 + power(2,log(range)) ] , [15- power(2,log(range)) ,15] )
     * 
     * log(range) = log(13) = 3 => RMQ( [3,11] , [7,15] )
     * 
     * @param from 
     * @param to 
     * @return T 
     */

    T rmq(int from,int to) const {
        assert(0 <= from && from <= to && to <= n-1);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return func(mat[lg][from], mat[lg][to-(1<<lg)+1]);
    }

    /**
     * @brief Calculate any general sparse table query
     * 
     * Sparse Table is capable of performing other types of range queries as
     * well, such as range sum, range xor, etc. Here, overlapping ranges might 
     * pose a problem so we compute the range in binary sequences, ie. in powers 
     * of two, which result in O(log(n)) query time.
     * 
     * Say you want to perform range sum query over [2,15]. We will perform
     * following queries - 
     *      1) [2,9]    - length 8
     *      2) [10,13]  - length 4
     *      3) [14,15]  - length 2
     * 
     * The sum of lengths 8+4+2 = 14 which is the total range 15-2+1 = 14.
     * We performed log(14) = 3 queries.
     * 
     * Unsurprisingly, we can perfrom RMQ using this function as well because, this
     * function performs range queries over ranges that do not collide. RMQ works on
     * colliding ranges, so it will definitely work here too, although this defeats
     * the whole purpose of using a Sparse Table.
     * 
     * Note : Initialise ignore variable with appropriate value according to need.
     * For RMQ it will either be INT_MIN or INT_MAX. For sum and xor queries, it will 
     * be 0.
     * 
     * @param from Start of range
     * @param to End of range, both zero indexed
     * @return T The range query
     */

    T query(int from,int to) const {
        if ( from > to )
            return ignore_val;
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return func( mat[lg][from], query(from + (1 << lg) ,to) );
    }

};

int main(){

    auto max_fnc = [&](int a,int b){
        return max(a,b);
    };

    auto sum_fnc = [&](int a,int b){
        return a+b;
    };

    vector<int> a = {1,2,3,4,5};
    int inf = 1e9;

    SparseTable<int,function<int(int,int)>> max_spt(a,max_fnc,-inf);    // Max Sparse Table
    SparseTable<int,function<int(int,int)>> sum_spt(a,sum_fnc);         // Sum Sparse Table

    cout<<max_spt.query(1,3)<<endl;     // 4 
    cout<<max_spt.rmq(1,3)<<endl;       // 4

    cout<<sum_spt.query(2,4)<<endl;     // 12
    cout<<sum_spt.query(0,4)<<endl;     // 15

}
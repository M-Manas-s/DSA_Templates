#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define FOR(i,k,n) for ( int i=k; i<n; i++ )
/**
 * @brief Structure to store Fenwick Tree and corresponding functions
 * 
 */

struct Bit{
    vi bit;
    int n;

    /**
     * @brief Construct a new Bit object, allocating the bit vector the passed size
     * 
     * Assigns the bit vector with max_n + 1 zero values, we are using a 1-based Fenwick Tree
     * In case of Range Query - Point Update, assigns
     * 
     * @param max_n size of the vector upon which the BIT has to be built
     */

    Bit(int max_n) {
        n = max_n + 1;
        bit.assign(n, 0);
    }

    /**
     * @brief Construct a new Bit object constructing the bit vector from the passed vector
     * 
     * This constructor calls the previous constructor to explicilty assign a size to the bit vector
     * which is the size of passed vector + 1 (for 1-based BIT)
     * 
     * It then constructs the bit vector based on the passed vector
     * 
     * @param a Vector upon which bit has to be constructd
     */

    Bit(vi a) : Bit(a.size()) {
        FOR(i,0,a.size())
            add(i+1, a[i]);
    }

    /**
     * @brief Return the sum of the elements from [1,idx] both inclusive and using a 1-based indexing
     * 
     * Notice how idx in both querying and adding proceeds the same way forward and backward
     * idx +/- = (idx & -idx)
     * Understanding this first helps you understand that the order and reading and writing is essentially the same
     * 
     * Now, the BIT is designed in such a way that if you want to say read a sum of [1,15], it will read
     * sum of = first 8 + next 4 + next 2 + next 1 
     * (the correct sequence starts from back ie first 1 closest element, then next 2 closest element leaving the first
     * selected element and so on until all the indexes are read)
     * 
     * Here, understand that the sum of every power of 2 sequences are stored in a single index, ie
     * Sum of first 8 elements are stored in index 8, sum of first 4 elements are stored in index 4
     * Hence, you only read log2n elements but adding it gives the whole sum until the desired index
     * 
     * This is BIT
     * 
     * @param idx the index until whose sum has to returned, ie [1,idx]
     * @return int Sum of elements [1,idx]
     */

    int query(int idx) {
        int query = 0;
        while (idx > 0) {
            query += bit[idx];
            idx -= (idx & -idx);
        }
    return query;
    }

    /**
     * @brief Returns the sum of the range [l,r]
     * 
     * sum(l,r) = sum(0,r) - sum(0,l)
     * 
     * @param l left limit
     * @param r right limit
     * @return int sum of [l,r]
     */

    int query(int l, int r) {
        return query(r) - query(l - 1);
    }

    /**
     * @brief Constructs the BIT for a value val at index idx
     * 
     * This function adds the value of val at index idx as well as all the corresponding
     * indices responsible for computing the sum of that range
     * 
     * That is, value of the first element has to be stored in -
     * 1) First index
     * 2) 1 + ( 1 & -1 ) = 1+1 = Second index ( stores sum(1,2) )    ( idx becomes 2 )
     * 3) 2 + ( 2 & -2 ) = 2+2 = Fourth index ( stores sum(1,4) )    ( idx becomes 4 )
     * 4) 4 + ( 4 & -4 ) = 4+4 = Eighth index ( stores sum(1,8) )    ( idx becomes 8 )
     * and so on...
     * 
     * The value of 3rd element has to be stored in- 
     * 1) Third index
     * 2) 3 + ( 3 & -3 ) = 3+1 = Fourth Index ( stores sum(1,4) )    ( idx becomes 4 )
     * 3) 4 + ( 4 & -4 ) = 4+4 = Eighth Index ( stores sum(1,8) )    ( idx becomes 8 )
     * and so on..
     * 
     * @param idx 
     * @param val 
     */

    void add(int idx, int val) {
        while (idx < n) {
            bit[idx] += val;
            idx += (idx & -idx);
        }
    }

    /**
     * @brief This function actually does a range update, ie adds a value to a range [l,r]
     * 
     * The function only makes two point updates so how does it result in range update?
     * 
     * This function is a part of Range Update, Point Query algorithm. Now, the only change from Point Update, Point Query algorithm
     * ( everything we discussed before this function was Point Update, Point Query algorithm ) is the way we interpret the
     * query. The query for this function is actually a sum but we read it as a point query.
     * To simplify things, let us take an example - 
     * 
     * Normally query(idx) = sum(0,idx), this is very much true here, in this case, too but we do not interpret it as
     * a sum upto that index, but as a point value.
     * 
     * Let's assume that the bit array is initialised with 0 at all indices. Let us add(1,5,20). 
     * Essentially adding 20 to 1 ( and corresponding indices ) and -20 to 6 ( and corresponding indices ). Now let's read this
     * 
     * query(1) to query(5) will return 20 
     * ( as sum(1,1) = sum (1,2) = sum(1,5), the normal array representation will be { 20,0,0,0,0,-20,0,0... } -> This is NOT a BIT )
     * 
     * query(6) to query(n) will return 0
     * ( as sum(6,6) = sum (6,n) = 20+0+0+0+0+(-20), following the same representation from above )
     * 
     * So, we are reading the sum but interpreting it as a point value.
     * 
     * @param l 
     * @param r 
     * @param val 
     */

    void add(int l, int r, int val) {
        add(l, val);
        add(r + 1, -val);
    }
};


int main(){

    vi a({1,2,3,4,5});
    Bit ft(a); 

    cout<<ft.query(1)<<endl;    // 1
    cout<<ft.query(2)<<endl;    // 3
    ft.add(1,5);
    cout<<ft.query(2)<<endl;    // 8 (5+3)

    // Range Update, Point Query

    Bit ft2(vi {4,2,3});        // { 4,6,3 } -> bit array
    cout<<ft2.query(3);         // 9
    ft2.add(1,2,5);             // { 9,11,-2 } -> bit array
    cout<<ft2.query(3);         // 9  -> Value at index 3 remains unchanged as we updated only [1,2]
    cout<<ft2.query(2);         // 11
}

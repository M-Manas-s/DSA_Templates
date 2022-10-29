#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define vt vector
#define vi vt<int>
#define FIO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define each(x, a) for (auto &x : a)

/**
 * @brief Node for Binary Trie, can be improvised to have other
 *        variables like end, etc. This implementation only focuses
 *        on storing count and not end. 
 * 
 * The height of the trie used in this implementaiton is fixed, ie. bits. This
 * reduces the recursive implementation of trie to an iterative one. Every query 
 * performed on trie always traverses the tree upto the root ( unless it breaks
 *  off, of course ). This makes the implementation a little different from the 
 * standard trie.
 * 
 * For example, if we want to check if a number exists in the trie, we don't have
 * to worry about the number ending somewhere along the way. It is guarenteed that
 * if the number exists, there will be a complete path from the root to the leaf.
 * 
 */

class TrieNode
{

    /**
     * @brief children can either be 0 or 1
     *        cnt is the number of digits passing through this node
     * 
     */

    public:
        TrieNode *children[2] = {};
        int cnt = 0;
};

/**
 * @brief Binary Trie that stores bits
 * 
 */

class BinaryTrie
{
    TrieNode *root;
    int bits;
 
public:

    /**
     * @brief Construct a new Binary Trie object with bits = 31 by
     *        by default. Root is the psudo-root node.
     * 
     */

    BinaryTrie()
    {
        root = new TrieNode();
        bits = 31;
    }
    
    /**
     * @brief Construct a new Binary Trie object with custom
     *        parameters
     * 
     * @param a vector of integers to be inserted   
     * @param b number of bits for the numbers - generally 31 or 63
     */

    BinaryTrie(vector<int> a,int b = 31) 
    { 
        root = new TrieNode();
        insert(a); 
        bits = b;
    }

    /**
     * @brief Inserts the number into the trie. 
     * 
     * Traverse down the tree and check whether node exists or not. If not,
     * allocate the node. Increase the count of the node's cnt value;
     * 
     * @param x 
     */

    void insert(int x)
    {
        TrieNode *cur = root;
        for (int i = bits; i >= 0; i--)
        {
            bool b = (x >> i) & 1;
            if (!cur->children[b])
                cur->children[b] = new TrieNode();
            cur = cur->children[b];
            cur->cnt++;
        }
    }

    void insert(vector<int> a)
    {
        for (auto s : a)
            insert(s);
    }

    /**
     * @brief Removing the number from the trie. 
     * 
     * This alone requires a recursive implementation for the sake of simplicity.
     * A double pass iterative approach will also work but recursion is better suited.
     * So, the function reduces the count of children, and deletes the node 
     * ( sets it to NLLL ) if no number passes through it.
     * 
     * @param cur current traversing node
     * @param x number to be deleted
     * @param i current bit position
     */

    void remove(TrieNode* cur, int x, int i)
    {
        if ( i == -1 ) return;

        bool b = (x >> i) & 1;
        cur->children[b]->cnt--;
        remove(cur->children[b],x,i-1);
        if ( cur->children[b]->cnt == 0 )
            cur->children[b] = NULL;

    }

    void remove(int x)
    {
        remove(root,x,bits);
    }

    /**
     * @brief Removing the number without clearing the node
     * 
     * This approach won't clear the memory but just set the count to zero, which is also
     * correct since you won't traverse this subtree once the count goes to zero. Still, it 
     * is better to maintain a smaller tree whenever possible and cut-off the subtree once
     * it is completely empty. The choice totally depends upon the programmer.
     * 
     * @param x Number to be deleted
     */

    // void remove(int x)
    // {
    //     TrieNode *cur = root;

    //     for (int i = bits; i >= 0; i--)
    //     {
    //         bool b = (x >> i) & 1;
    //         cur = cur->children[b];
    //         cur->cnt--;
    //     }
    // }

    /**
     * @brief Check if a number is present.
     * 
     * Again, because the height of the tree is fixed, it becomes lot easier
     * on the implementation end to compute this. We can keep traversing towards
     * the leaf if the bits are matching, else return false. Once we reach the leaf,
     * return true.
     * 
     * @param s 
     * @return true if number is present or in other words, we reached the leaf.
     * @return false if number isn't matching
     */

    bool found(int s)
    {
        TrieNode *cur = root;
        for (int i = bits; i >= 0; i--)
        {
            bool b = (s >> i) & 1;
            if (!cur->children[b])
                return 0;
            cur = cur->children[b];
        }
        return 1;
    }

    /**
     * @brief Computes the maximum xor of a given number with the trie
     * 
     * Keep traversing down the tree. If it is possible to take the inverted bit,
     * add the bit to the answer and travverse it, else traverse the current bit,
     * 
     * @param x The number whose maximum xor has to be calculated
     * @return int The maximum xor
     */

    int max_xor(int x)
    {
        TrieNode *cur = root;
        int ans = 0;
        for (int i = bits; i >= 0; i--)
        {
            bool b = (x >> i) & 1;
            if ( cur->children[!b] && cur->children[!b]->cnt > 0 )
            {
                ans += (1LL << i);
                cur = cur->children[!b];
            }
            else
                cur = cur->children[b];
        }
        return ans;
    }
    
};

signed main(){
    FIO;
    BinaryTrie trie;
    vi ins = {0,25,2};
    trie.insert(ins);
    cout<<trie.found(25)<<endl;     // Yes
    cout<<trie.found(26)<<endl;     // No
    trie.remove(25);                
    cout<<trie.max_xor(5)<<endl;    
    
    // Had 25 been there in the trie, answer would have been 25^5=28
    // Now, it is 2^5=7
}
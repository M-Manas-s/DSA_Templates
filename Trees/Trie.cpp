#include <bits/stdc++.h>

using namespace std;


/**
 * @brief Trie template for any general trie
 * 
 * This template keeps count of words ending at a particular
 * node as well as count of common prefix upto the word.
 * 
 */

struct TrieNode
{

    TrieNode *children[26];
    int wordCount, prefixCount;

    /**
     * @brief Inserts a string into the trie
     * 
     * Loops through each character in the word, and inserts it into
     * the trie by making a new node if one doesn't exist already. Prefix
     * Count is updated for each character while Word Count is updated
     * only where the word ends.
     * 
     * @param word the word to be inserted
     */

    void insert(string word)
    {
        TrieNode *curr = this;
        for (auto &ch : word)
        {
            if (!curr->children[ch - 'a'])
                curr->children[ch - 'a'] = new TrieNode();
            curr = curr->children[ch - 'a'];
            curr->prefixCount++;
        }
        curr->wordCount++;
    }

    /**
     * @brief Searches for a word in the trie
     * 
     * This is an improvised version of boolen search where deuplicates
     * can also be handled. Traverse the trie according to the query
     * word and break off if the node doesn't exist. If the whole word
     * is looped, return the count of words ending at that location.
     * 
     * @param word The word to be searched
     * @return int Number of words ending at that node
     */

    int search(string word)
    {
        TrieNode *curr = this;
        for ( auto &ch : word )
        {
            if ( !curr->children[ch-'a'] )
                return false;
            curr = curr->children[ch-'a'];
        }
        return curr->wordCount;
    }

    /**
     * @brief Checks the number of strings with same prefix
     * 
     * Instead of returning wordCount, return the PrefixCount in the search
     * function.
     * 
     * @param prefix The prefix to be checked
     * @return int The number of strings with same prefix
     */

    int starts_with(string prefix)
    {
        TrieNode *curr = this;
        for (auto &ch : prefix)
        {
            if ( !curr->children[ch - 'a'] )
                return false;
            curr = curr->children[ch - 'a'];
        }
        return curr->prefixCount;
    }

    /**
     * @brief Removes a string from the trie and also nullifies the node recursively
     * 
     * This is the only function to ffollow a recursive approach. The reason for this
     * is to process the node in pre-Order and delete the node in post-Order. The 
     * deletion can be performed in pre-Order as well but that defeats the purpose of
     * de-allocating the space. The deallocation of space starts from the leaf and
     * propagates up the tree.
     * 
     * Search if the word exists, if not, just return back as there is nothing to 
     * remove. Decrease the prefixCount along the way. Now, if the current character
     * is the last character, decrease the wordCount too, else dive deeper into the
     * trie and keep repeating the same.
     * 
     * After the tree has finished processing, check if the child has no words passing
     * through it. If so, delete the node. Technically we are deleting that part of the
     * word that has no common prefix with any other word. This approach clears the memory
     * and removes the chances for extra computation as well, though it is more error
     * prone.
     * 
     * @param curr current traversing node
     * @param word the word to be removed
     * @param i the current looping index of the word
     */

    void remove(TrieNode *curr,string word,int i)
    {

        if ( i == 0 && !search(word) ) return;

        curr->children[word[i]-'a']->prefixCount--;

        if ( i == word.length()-1 )
            curr->children[word[i]-'a']->wordCount--;
        else
            remove(curr->children[word[i]-'a'],word,i+1);

        if ( curr->children[word[i]-'a']->prefixCount == 0 )
        {
            delete (curr->children[word[i]-'a']);
            curr->children[word[i]-'a'] = NULL;
        }
    }

    /**
     * @brief Wrapper for remove function with default parameters.
     * 
     * @param word Word to be removed
     */

    void remove(string word)
    {
        remove(this,word,0);
    }

};

int main()
{
    TrieNode *trie = new TrieNode();
    trie->insert("hello");
    trie->insert("help");
    trie->insert("help");
    trie->insert("hiya");

    cout<<trie->starts_with("h")<<endl;     // 4
    cout<<trie->starts_with("hel")<<endl;   // 3
    cout<<trie->search("help")<<endl;       // 2

    trie->remove("help");

    cout<<trie->search("help")<<endl;       // 1
    cout<<trie->starts_with("he")<<endl;    // 2
}
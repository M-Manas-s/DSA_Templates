#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define vi vector<int>
#define FOR(i,k,n) for ( int i=k; i<n; i++ )

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

/**
 * @brief Builds the Longest Proper Suffix vector
 * 
 * ci switches back to last known match or starts with zero if nothing was matched earlier.
 * Say last match was of two characters and now the third character is also matching, the while loop breaks 
 * and lps[i] gets added by ci+1 effectively saying that last two characters (ci) plus this new character
 * is a proper suffix. 
 * 
 *  ci           000120
 *  string      abcabcd
 *  lps         0001230
 * 
 * If say the new character that arrived does not match, we jump back to the last character of the previously 
 * matched suffix hoping that matches.
 * 
 *  ci           0000120
 *  string      abcdabca
 *  lps         00001231
 * 
 *  ci           00001112
 *  string      bbccbbbbc
 *  lps         010012223
 * 
 * @param p Pattern stirng
 * @return vector<int> LPS vector
 */

vector<int> buildLPS(string p)
{
    vi lps(p.length());
    lps[0]=0;
    FOR(i,1,p.length())
    {
        int ci = lps[i-1];

        while( ci>=1 && p[i]!=p[ci] )
            ci = lps[ci-1];
        
        if ( p[i]==p[ci] )
            lps[i]=ci+1;
        else
            lps[i] = ci;
    }
    return lps;
}

/**
 * @brief Finds the number of occurances of pattern stirng p in search string s
 * 
 * ci swtiches back to the last known proper suffix (that is also a prefix) if ci has reached the
 * length of the pattern or the pattern stops matching anymore.If the ci index of pattern and current
 * iterating index of string matches, ci increments or else the search resumes back from the current ci 
 * index of pattern because the proper suffix was also a prefix, so we don't need to match it again. If 
 * ci reaches the length of pattern (All the pattern was matched), we have found a pattern match in the
 * string.
 * 
 *          aababaabaababa
 *          a                   (Match => ci=1)
 * 
 *          aababaabaababa
 *          ab                  (No match, rollback to first index => ci=1)
 * 
 *          aababaabaababa
 *          xab                 (We didn't match the first index again. Match => ci=2)
 * 
 *          aababaabaababa      (ci == p.length() == 3 , 1 complete pattern match found)
 *          xaba
 * 
 *          aababaabaababa      (As c==p.length(), we iterate ci back to the mathcing index => 1. Match => ci=2)
 *          xxxab
 * 
 *          and this goes on....
 * 
 * @param s Search String s
 * @param p Pattern String p
 * @return int Occurances of pattern p in string s
 */

int kmp(string s, string p)
{
    vi lps = buildLPS(p);
    int ci=0;
    int ans=0;

    FOR(i,0,s.length())
    {
        while( ci==p.length() || (ci>=1 && s[i]!=p[ci]) )
            ci = lps[ci-1];
        if ( s[i]==p[ci] )
            ci++;
        if (  ci==p.length())
            ans++;
    }
    return ans;
}


int main(){
    cout<<kmp("aababaabaababa","aba");  //5
    return 0;
}
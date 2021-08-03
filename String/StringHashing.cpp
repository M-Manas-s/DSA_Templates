#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define FOR(i,k,n) for ( int i=k; i<n; i++ )

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 100;              // 
const int mod = 1e9 + 7;        // Indirectly represents the number of possible hash values that can be generated
const int base = 33;            // Usually this integer is greater than the number of distinct characters in the string

/**
 * @brief Modular addition
 * 
 *  Assuming => (a+b) < INT_MAX
 *  (a+b)%m = (a%m + b%m)%m
 *  (a-b)%m = (a%m - b%m)%m
 * 
 * @param a integer 1
 * @param b integer 2
 * @param mod const mod value
 * @return int Modular sum of a and b
 */
 
int add(int a, int b, int mod){
    int res = (a + b) % mod;
    if(res < 0)
        res += mod;
    return res;
}

/**
 * @brief Modular mulitplication
 * 
 * As a*b can be greater than INT_MAX, we typecast it into LL
 * (a*b)%m = (a%m * b%m)%m
 * 
 * @param a integer 1
 * @param b integer 2
 * @param mod const mod value
 * @return int Modular multiplication
 */
 
int mult(int a, int b, int mod){
    int res = (a * 1LL * b) % mod;
    if(res < 0)
        res += mod;
    return res;
}
 
/**
 * @brief Binary Power
 * 
 * Trivial Power function time complxity => O(b)
 * Binary Power time complexity => O(log b)
 * 
 * let b = 8
 * Trivial => a*a*a*a*a*a*a*a 
 * Binary Power => ((a^2)^2)^2
 * 
 * The algorithm keeps on squaring the passed integer upon itself and dividing the power by 2.
 * If the power turns out to be odd for that particular iteration, it multiplies it with the result.
 * In the last iteration, the power will become odd (2/2=1) every time and the result gets multiplied
 * by the exponentiating integer.
 * 
 * @param a Passed integer whose power has to be found
 * @param b The power to which the integer has to be raised
 * @param mod const mod value
 * @return int Binary Power
 */

int power(int a, int b, int mod){
    int res = 1;
    while(b){
        if((b % 2) == 1)
            res = mult(res, a, mod);
        a = mult(a, a, mod);
        b /= 2;
    }
    return res;
}
 
int pw[N];
int inv[N];
int H[N];

/**
 * @brief Calculates power and inverse power 
 * 
 * pw array stores base raised to the power of that index modulo mod
 *      pw = { (1%mod) , (base%mod) , (base^2%mod) , (base^3%mod), ..... }
 * It is done using the previous calculated value as the sequence follows a Geometric Progression
 * 
 * Now, we calculate the inverse power of the base modulo mod or (base^-i)%mod and store it in inv array
 * The formula goes as - 
 *      Inverse Power modulo m = (base^-1)%mod = (base^(mod-2))%mod 
 * Now using this value, we calculate inverse power i (base^-i % mod) using DP as we did for power
 * 
 */
 
void precalc() {
    pw[0] = 1;
    FOR(i,1,N)
        pw[i] = mult(pw[i - 1], base, mod);
    
    int pw_inv = power(base , mod - 2 , mod);
    inv[0] = 1;
    FOR(i,1,N)
        inv[i] = mult(inv[i - 1], pw_inv, mod);
}

/**
 * @brief Pre-computes the hash of the string
 * 
 * The formula goes as-
 *      H(S) = Sum [ i= 0 to N-1 -> s[i] * p^i ]
 * Here s[i] is in the form of integer ( 0-26 )
 * 
 * H[i] is the hash of the substring s[0:i] inclusive
 * 
 * @param s String to be hashed
 */
 
void build(string s){
    int n = s.length();
    FOR(i,0,n){
        H[i] = add((i == 0) ? 0 : H[i - 1], mult(pw[i], s[i] - 'a' + 1, mod), mod);
    }
}

/**
 * @brief Get the Hash value of the substring between the passed indices
 * 
 * To get the Hash of substring s[x:y], we need to follow the equation
 *      hash = H[y] - H[x-1]
 * This alone isn't enough, we also need to scale down the power of base
 * To understand this , let us take an example (Please ignore modulo here) - 
 *      Say, the string is "abcdef" and we need the hash of the substring "cde" or indices [2:4]
 *          H[1] = 1*33^0 + 2*33^1
 *          H[4] = 1*33*0 + 2*33*1 + 3*33^2 + 4*33^3 + 5*33^4
 *      Now, H[4] - H[1] = 3*33^2 + 4*33^3 + 5*33^4 , but the power of base should start from 0 in hash
 *      So, we scale it down to xth inverse power of base. 
 *          (H[4] - H[1])*inv[2] = 3*33*0 + 4*33^1 + 5*33^2
 *      This is the correct hash
 * 
 * Now, the hash becomes
 *          hash = (H[y] - H[x-1]) * inv[x]
 *         
 * @param x Starting index
 * @param y Ending index
 * @return int Hash value
 */
 
int getHash(int x , int y){
    int res = add(H[y], (x == 0) ? 0 : -H[x - 1], mod);
    res = mult(res , (x == 0) ? 1 : inv[x], mod);
    return res;
}

int main(){
    string s = "abcdef";
    precalc();
    build(s);
    cout<<getHash(0,1)<<'\n';   // 1*33^0 * 2*33^1 = 67
    cout<<getHash(0,4)<<'\n';   // 1*33^0 + 2*33^1 + 3*33^2 + 4*33^3 + 5*33^4 = 6076687
    cout<<getHash(2,4)<<'\n';   // 3*33^0 + 4*33^1 + 5*33^2 = 5580
}



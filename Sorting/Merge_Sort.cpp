#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define FOR(i,k,n) for ( int i=k; i<n; i++ )

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

/**
 * @brief Merge the two sorted subarrays 
 * 
 * Merge sort uses Divide and Conquer algorithm to Divide the array into two halves (possibly) 
 * and then merge them into one soted array. This is done recursively until all the elements are
 * sorted.
 * 
 * The merge function is responsible for merging the two sorted halves. Firstly, we create two
 * index pointers - one for the subarray starting with smaller index (li) and one for the 
 * subarray starting with larger index (hi). They are initialized with their starting indices
 * corresponding to their respective subarrays. 
 * 
 * Now, we create a temporary array (t), with size high-low+1, that merges these two subarrays 
 * into a single sorted array,  * which, in the end, overwrites the original array in that 
 * range ([low,high])
 * 
 * Now, we initialize another index pointer for the temporary array t - i to 0. We now start 
 * looping the temporatry array,t. Starting from li and hi, we check which number corresponding 
 * to these indices is smaller. Say, the number corresponding to li, a[li] is smaller, we write 
 * a[li] to t[i] and increment li, else we write a[hi] to t[i] and increment hi. This process is
 * repeated until either li or hi reaches their limit - li<=mid, hi<=high.
 * 
 * After the above iteration is over, it is possible that either li or hi has not reached their
 * limit, i.e. one of the subarrays has not been completely wirtten in temporary array t. So, we 
 * find which number has reached the limit - say li==mid+1 now, so we may not have written the
 * subarray a[hi] to a[high], so we loop until hi<=high and write the corresponding element 
 * at corresponding place in the temporary array.
 * 
 * After all the above is done, we have successfully merged the above subarrays in the temporary
 * array. Now, starting from low, we start wrtiting the original array - a, with the temporary
 * array starting with index 0. After every element is written, we have now overwritten the 
 * original array with merged sorted subarrays.
 * 
 * @param a the original array
 * @param low starting of subarray with lower index
 * @param mid ending of subarray with lower index, the subarray with higher index starts right
 *            after this
 * @param high ending of the subarray with higher index 
 */

void merge(int a[], int low, int mid, int high){

    int li = low, hi = mid+1;                 // lower index, higher index

    int t[high-low+1];                        // temporary array
    int i;

    for ( i=0 ; li<=mid && hi<=high; i++ )
    {
        if ( a[li] < a[hi] )
        {
            t[i] = a[li];
            li++;
        }
        else
        {
            t[i] = a[hi];
            hi++;
        }
    }

    if ( li == mid+1 )
        while( hi<=high )
            t[i++] = a[hi++];
    
    if ( hi == high+1 )
        while( li<=mid )
            t[i++] = a[li++];

    for ( int j=0,k = low ; k<=high; k++,j++ )
        a[k] = t[j];
}

/**
 * @brief Performs the merge sort function by dividing the array into equal subarray and merging it.
 * So where is the sort part? When we divide the array into two subarrays of length 1, we have two
 * sorted subarrays ( PS. Arrays with single element are sorted :P ). Now, we merge them with the
 * merge function and move forward to merging the next subarrays. This is done until low < high, or 
 * essintially the lower and higher index do not cross each other, this can happen with singleton
 * arrays.
 * 
 * If you study the algorithm in terms of a binary tree, mergeSort follows a post-order merge, ie,
 * it first finely divides the array into singleton arrays and then starts merging them one by one, 
 * essentially sorting the whole array in the end.
 * 
 * @param a Original array
 * @param low Starting index of the array/subarray to be sorted
 * @param high Ending index of the array/subarray to be sorted
 */

void mergeSort(int a[], int low,int high)
{
    if ( low < high )
    {
        int mid = (high + low)/2;
        mergeSort(a,low,mid);
        mergeSort(a,mid+1,high);
        merge(a,low,mid,high);
    }
}

int main(){
    int a[8] = {5,7,2,4,6,13,1,8};
    mergeSort(a,0,7);

    FOR(i,0,8)
        cerr<<a[i]<<' ';       // 1 2 4 5 6 7 8 13
}

//                   {5,7,2,4,6,13,1,8}
//                    /               \
//              {5,7,2,4}           {6,13,1,8}
//               /    \                /    \
//             {5,7} {2,4}         {6,13}   {1,8}
//              / \     / \         /  \     /  \   
//           {5} {7} {2} {4}       {6} {13} {1} {8}     // Traversal is complete here, now we start merging
//            \  /     \ /          \   /    \   /
//           {5,7}   {2,4}         {6,13}   {1,8}
//            \       /             \        /
//           {2,4,5,7}             {1,6,8,13}
//                    \                /
//                    {1,2,4,5,6,7,8,13}
//
//


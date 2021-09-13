#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define FOR(i,k,n) for ( int i=k; i<n; i++ )

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

/**
 * @brief Partitions the array according to the pivot where elements placed to the left of pivot
 * are less than it and the elements placed to the right of pivot are more than it.
 * 
 * This partitioning technique uses the end of the array as pivot.
 * 
 * Patitioning works very close to two pointer technique where you maintain a point for the lower
 * half of the pivot ( elements less than pivot ) in a variable, say i and other pointer for looping
 * through the array, say j. In the end, i will contain the index of the elements upto which all 
 * the elements are less than the pivot. We can then swap pivot and the element at ith position to
 * partition the element on the pivot.
 * 
 * The other index pointer j, reads the element of the array from low to high one by one. Say if the 
 * element at jth position is less than or equal to the pivot, we increment i and replace the element
 * at ith position with the element at the jth position. By doing this we make sure that all the 
 * elements upto i are less than the pivot. We keep incrementing i for every element less than pivot
 * while looping the array. After we've looped over the given range, all the elements upto i will be 
 * less than pivot. Then we replace pivot with (i+1)th element to correctly place the pivot.
 * 
 * We return the pivot in the end to sort the elements after and before the pivot recursively.
 * 
 * @param arr Array to be partitioned
 * @param low starting index
 * @param high ending index
 * @return int pivot point or the location of pivot after partitioning 
 */

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low-1;

    FOR(j,low,high)
    {
        if ( arr[j] <= pivot )
        {
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

/**
 * @brief Recursively sorts the array by dividing the array into two parts based on the pivot, the
 * pivot is generally the last element of the current array, the is partitioned and place correctly.
 * 
 * Quick Sort uses Divide and Conquer approach to divide the array into small components and sort them
 * alone.
 * 
 * Say, the array is - {4,7,2,5,6}
 * 
 * First we partition the array based on the last element, here 6,
 * So, the array becomes - {4,2,5,6,7}
 * As 6 is the pivot, elements to the left of 6 are less than 6 and to its right are greater than 6.
 * The partition function retruns the index of 6 (i.e. 3). Now, we quicksort the arrays from [0,2] and
 * [4,4]. This goes on until low is no more less than high ( when pivot becomes equal to low or high ).
 * 
 * 
 * @param arr Array or part of the array to be sorted
 * @param low starting index
 * @param high ending index
 */

void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pivot = partition(arr, low, high); 
  
        quickSort(arr, low, pivot - 1); 
        quickSort(arr, pivot + 1, high); 
    } 
} 

int main(){
    int a[5] =  {5,7,2,4,6};
    quickSort(a,0,4);

    FOR(i,0,5)
        cerr<<a[i]<<' ';       // 2 4 5 6 7
}


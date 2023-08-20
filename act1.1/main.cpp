/**
 * @file main.cpp
 * @author Juan Daniel Muñoz Dueñas A01641792 / Carlos David Amezcua Canalez A01641742
 * @brief
 * @version 0.1
 * @date 2023-08-19
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <vector>

using namespace std;

/*
Description: Function to merge two halves of a subarray.
Parameters:
    arr: array containing the subarray to be merged, possibly the whole array.
    l: index of the leftmost element of the subarray.
    m: index of the middle element of the subarray.
    r: index of the rightmost element of the subarray.
Complexity, where n is the number of elements in the subarray:
    Time: O(n)
    Space: O(n)
*/
void merge(vector<double> &arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    vector<double> firstHalve(n1), secondHalve(n2);

    /*
    Copy data to temp arrays firstHalve[] and secondHalve[]
    Complexity O(N)
    */
    for (int i = 0; i < n1; i++)
        firstHalve[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        secondHalve[j] = arr[m + 1 + j];

    /*
    Merge the temp arrays back into arr[l..r]
    Complexity O(N)
    */
    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (firstHalve[i] >= secondHalve[j]) {
            arr[k] = firstHalve[i];
            i++;
        }
        else {
            arr[k] = secondHalve[j];
            j++;
        }
        k++;
    }

    /*
    Copy the remaining elements of firstHalve[], if there are any
    Complexity O(N)
    */
    while (i < n1) {
        arr[k] = firstHalve[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of secondHalve[], if there are any
    Complexity O(N)
    */
    while (j < n2) {
        arr[k] = secondHalve[j];
        j++;
        k++;
    }
}

/*
Description: Recursive function to sort a subarray using merge sort.
Parameters:
    arr: array containing the subarray to be sorted, possibly the whole array.
    l: index of the leftmost element of the subarray.
    r: index of the rightmost element of the subarray.
Complexity, where n is the number of elements in the subarray:
    Time: O(n log n)
    Space: O(n)
*/
void mergeSort(vector<double> &arr, int l, int r) {
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

/*
Description: Main function. Reads the input and calls the merge sort function.
Test cases:
    1.
        Input: 0
        Output: 0
*/
int main() {
    int n;
    cin >> n;
    vector<double> arr(n);
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    mergeSort(arr, 0, n - 1);
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}

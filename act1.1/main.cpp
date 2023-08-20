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
Function to merge two halves of a subarray.
Complexity, where n is the number of elements in the subarray:
    Time: O(n)
    Space: O(n)
*/
void merge(vector<double> &arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    vector<double> L(n1), R(n2);

    /*
    Copy data to temp arrays L[] and R[]
    Complexity O(N)
    */
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /*
    Merge the temp arrays back into arr[l..r]
    Complexity O(N)
    */
    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /*
    Copy the remaining elements of L[], if there are any
    Complexity O(N)
    */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any
    Complexity O(N)
    */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/*
Recursive function to sort an array using merge sort
Complexity, where n is the number of elements in the array:
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

int main() {
    // The test cases are the following:
    // Empty array
    // Array with 5 elements already sorted
    // Array with 5 elements sorted in reverse
    // Array with 11 elements with repeated values
    // Array with 100 elements with random values

    int n;
    cin >> n;
    vector<double> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    mergeSort(arr, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}

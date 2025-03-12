/*
    l = left index of the array
    r = right index of the array
    m = middle index of the array

    MergeSort Function:
        1. If l < r, then
            a. Calculate m = (l+r)/2
            b. MergeSort(arr, l, m)
            c. MergeSort(arr, m+1, r)
            d. Merge(arr, l, m, r)

    Merge Function:
        1. n1 = m-l+1
        2. n2 = r-m
        3. Create two arrays L and R of size n1 and n2 respectively
        4. Copy the elements of arr[l...m] to L[0...n1-1] and arr[m+1...r] to R[0...n2-1]
        5. L[n1] = INT_MAX
        6. R[n2] = INT_MAX
        7. i = 0, j = 0
        8. For k = l to r
            a. If L[i] <= R[j], then arr[k] = L[i] and i++
            b. Else arr[k] = R[j] and j++
*/

#include <iostream>
using namespace std;

void MergeSort(int arr[], int l, int r){
    // Check if the array has more than one element
    if(l < r){
        int m = (l + r) / 2; // middle index of the array

        MergeSort(arr, l, m); 
        MergeSort(arr, m+1, r);
        Merge(arr, l, m, r);
    }
}
void Merge(int arr[], int l, int m, int r){
    int n1 = m-l+1; // size of left array
    int n2 = r-m; // size of right array

    int L[n1], R[n2]; // left and right arrays

    for(int i = 0; i < n1; i++) L[i] = arr[l+i]; // copying elements to left array
    for(int i = 0; i < n2; i++) R[i] = arr[m+1+i]; // copying elements to right array
    
    L[n1] = INT_MAX; 
    R[n2] = INT_MAX;

    int i = 0, j = 0; 

    // Merging the left and right arrays
    for(int k=l; k <= r; k++){ 
        if(L[i] <= R[j])
            arr[k] = L[i++];
        else
            arr[k] = R[j++];
    }
}

int main(){
    cout << "Enter the number of elements: ";
    int n; cin >> n;

    // Array of n size
    int arr[n];

    //Unsorted Array Input
    cout << "Enter the elements: ";
    for(int i = 0; i < n; i++) cin >> arr[i];

    MergeSort(arr, 0, n-1); //MergeSort Function

    //Sorted Array Output
    cout << "Sorted array: ";
    for(int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}


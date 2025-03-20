/*  
    l = left index of the array
    r = right index of the array

    QuickSort Function:
        1. if l < r, then
            a. p = Partition(arr, l, r)
            b. QuickSort(arr, l, p-1)
            c. QuickSort(arr, p+1, r)
    
    Partition Function:
        1. pivot = arr[r]
        2. i = l-1
        3. for j = l to r-1
            a. if arr[j] < pivot, then
                i++
                swap arr[i] and arr[j]
        4. swap arr[i+1] and arr[r]
        5. return i+1
*/

#include <iostream>
using namespace std;

int Partition(int arr[], int l, int r){
    int pivot = arr[r];
    int i = l-1;
    for(int j = l; j < r; ++j){
        if(arr[j] < pivot){
            ++i;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[r]);
    return i+1;
}

void QuickSort(int arr[], int l, int r){
    // Check if the array has more than one element
    if(l < r){
        int p = Partition(arr, l, r);
        QuickSort(arr, l, p-1);
        QuickSort(arr, p+1, r);
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

    QuickSort(arr, 0, n-1); //QuickSort Function

    //Sorted Array Output
    cout << "Sorted array: ";
    for(int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}
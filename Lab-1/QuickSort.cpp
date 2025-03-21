/*
    Towfiq Omar Rakin
    23524202131
*/

#include <iostream>
using namespace std;

void swap(int &a, int &b){
    if(&a == &b) return;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

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
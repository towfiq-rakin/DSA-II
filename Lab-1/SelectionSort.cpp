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

void SelectionSort(int arr[], int n, string s){
    for(int i = 0; i < n-1; i++){
        if(s == "ascn"){
            int minIndex = i;
            for(int j = i+1; j < n; j++)
                if(arr[j] < arr[minIndex])
                    minIndex = j;
            swap(arr[minIndex], arr[i]);
        }
        else if(s == "dscn"){
            int maxIndex = i;
            for(int j = i+1; j < n; j++)
                if(arr[j] > arr[maxIndex])
                    maxIndex = j;
            swap(arr[maxIndex], arr[i]);
        }
    }
    return;
}
int main(){

    int arr[] = {4, 7, 2, 78, 35, 23, 15, 1, 9};
    int n = sizeof(arr)/sizeof(arr[0]);

    cout << "Unsorted Array: ";
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }

    SelectionSort(arr,n,"ascn");
    cout << endl << "Ascending Order: ";
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }

    SelectionSort(arr,n,"dscn");
    cout << endl << "Descending Order: ";
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }
}
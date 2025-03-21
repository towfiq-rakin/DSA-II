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

void BubbleSort(int arr[], int n, string s){
    bool swapped;
    for(int i = 0; i < n-1; i++){
        swapped = false;
        for(int j = 0; j < n-i-1; j++){
            if(s == "ascn")
                if(arr[j] > arr[j+1]){
                    swap(arr[j], arr[j+1]); 
                    swapped = true;
                }
            if(s == "dscn")
                if(arr[j] < arr[j+1]){
                    swap(arr[j], arr[j+1]); 
                    swapped = true;
                }
        }
        if(swapped == false) break;
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

    BubbleSort(arr,n,"ascn");
    cout << endl << "Ascending Order: ";
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }

    BubbleSort(arr,n,"dscn");
    cout << endl << "Descending Order: ";
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }
}
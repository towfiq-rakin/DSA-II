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

void InsertionSort(int arr[], int n, string s){
    for(int i = 1; i < n; i++){
        int key = arr[i];
        int j = i-1;
        if(s == "ascn"){
            while(j >= 0 && arr[j] > key){
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = key;
        }
        else if(s == "dscn"){
            while(j >= 0 && arr[j] < key){
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = key;
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

    InsertionSort(arr,n,"ascn");
    cout << endl << "Ascending Order: ";
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }

    InsertionSort(arr,n,"dscn");
    cout << endl << "Descending Order: ";
    for(int i=0; i<n; i++){
        cout << arr[i] << " ";
    }
}
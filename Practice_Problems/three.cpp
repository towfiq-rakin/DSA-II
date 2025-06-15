/*
You are developing a system for a hospital where multiple patients book appointments, and
each appointment has patient name and serial number. The hospital wants to sort all patient
appointments chronologically using Merge Sort, so they can manage the daily schedule.
Write a C++ program to accept a list of patients with their names and serial, sort the list in
ascending order of serial number using Merge Sort.
*/

#include <bits/stdc++.h>
using namespace std;

struct Patient {
    int serial;
    string name;
};

void Merge(vector<Patient> &patients, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<Patient> L(n1), R(n2);

    for(int i = 0; i < n1; i++) L[i] = patients[l + i];
    for(int i = 0; i < n2; i++) R[i] = patients[m + 1 + i];

    L.push_back({INT_MAX, ""}); 
    R.push_back({INT_MAX, ""}); 

    int i = 0, j = 0;
    for(int k = l; k <= r; k++) {
        if(L[i].serial <= R[j].serial) {
            patients[k] = L[i++];
        } else {
            patients[k] = R[j++];
        }
    }
}

void MergeSort(vector<Patient> &patients, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        MergeSort(patients, l, m);
        MergeSort(patients, m + 1, r);
        Merge(patients, l, m, r);
    }
}

int main() {
    int n;
    cout << "Enter number of patients: ";
    cin >> n;

    vector<Patient> patients(n);
    cout << "Enter patient details (serial name): " << endl;
    for (int i = 0; i < n; i++) {
        cin >> patients[i].serial >> patients[i].name;
    }

    MergeSort(patients, 0, n - 1);

    cout << "Sorted patient appointments:" << endl;
    for (const auto &p : patients) {
        cout << p.serial << " " << p.name << endl;
    }

    return 0;
}

/*
Input:
5
5 CR_Muhit
3 CR_Shahed
1 Alpha
4 Beta
2 Gamma
*/
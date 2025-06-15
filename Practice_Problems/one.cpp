/*
    You are developing a system for a company where each employee has a unique Employee ID, Name, and Salary. 
    The company wants to sort the employee records by Employee ID using Merge Sort, and later use Binary Search 
    to quickly find an employee based on their Employee ID. Write C++ program to implement this problem.
*/

#include <bits/stdc++.h>
using namespace std;

struct Employee {
    int id;
    string name;
    double salary;
};

void Merge(vector<Employee> &emp, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<Employee> L(n1), R(n2);

    for(int i=0; i<n1; i++) L[i] = emp[l+i];
    for(int i=0; i<n2; i++) R[i] = emp[m+1+i];

    L.push_back({INT_MAX, "", 0}); 
    R.push_back({INT_MAX, "", 0}); 

    int i = 0, j = 0;
    for(int k = l; k <= r; k++) {
        if(L[i].id <= R[j].id) {
            emp[k] = L[i++];
        } else {
            emp[k] = R[j++];
        }
    }
}
void MergeSort(vector<Employee> &emp, int l, int r){
    if(l < r){
        int m = (l + r) / 2; 
        MergeSort(emp, l, m); 
        MergeSort(emp, m+1, r);
        Merge(emp, l, m, r);
    }
}

int binarySearch(const vector<Employee> &emp, int id) {
    int left = 0, right = emp.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (emp[mid].id == id) {
            return mid;
        } else if (emp[mid].id < id) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int n;
    cout << "Enter the number of emp: ";
    cout << "Enter the number of emp: ";
    cin >> n;

    vector<Employee> emp(n);
    cout << "Enter Employee ID, Name, and Salary for each employee:" << endl;
    cout << "Enter Employee ID, Name, and Salary for each employee:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> emp[i].id >> emp[i].name >> emp[i].salary;
    }

    MergeSort(emp, 0, n - 1);


    cout << "Sorted Employee Records by ID:" << endl;
    for (const auto &emp : emp) {
        cout << "ID: " << emp.id << ", Name: " << emp.name << ", Salary: " << emp.salary << endl;
    }

    int searchId;
    cout << "Enter Employee ID to search: ";
    cout << "Enter Employee ID to search: ";
    cin >> searchId;
    int index = binarySearch(emp, searchId);

    if (index != -1) {
        cout << "Employee found: ID: " << emp[index].id << ", Name: " << emp[index].name << ", Salary: " << emp[index].salary << endl;
    } else {
        cout << "Employee with ID " << searchId << " not found." << endl;
    }
}

/*
input:
5
104 CR_Muhit 50000
105 CR_Shahed 60000
103 Alpha 55000
101 Beta 70000
102 Gamma 65000
101           
104 CR_Muhit 50000
105 CR_Shahed 60000
103 Alpha 55000
101 Beta 70000
102 Gamma 65000
101           
*/

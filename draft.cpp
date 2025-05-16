/*
    1. Take user input of Name, ID, Grade
    2. Sort them by their ID
    3. Binary Search to find
*/

#include <bits/stdc++.h>
using namespace std;

struct Student{
    string name;
    int id;
    double grade;
    bool operator<(Student const& other) {
        return id < other.id;
    }
};

int find(vector<Student> &student, int x){
    int l = 0;
    int r = student.size()-1;
    while(l <= r){
        int mid = (l+r)/2;
        if(x == student[mid].id) return mid;
        else if(x < student[mid].id) r = mid-1;
        else l = mid + 1;
    }
    return -1;
}

void sort(vector<Student> &student){
    int n = student.size();
    if (n < 2) return;
    int mid = n/2;
    vector<Student> left(mid), right(n-mid);

    for(int i=0; i<mid; ++i) left[i] = student[i];
    for(int i=mid; i<n; ++i) right[i-mid] = student[i];

    sort(left); sort(right);

    int i = 0, j = 0, k = 0;
    while(i < left.size() and j < right.size())
        if(left[i].id < right[j].id) student[k++] = left[i++];
        else student[k++] = right[j++];

    while(i < left.size()) student[k++] = left[i++];
    while(j < right.size()) student[k++] = right[j++];
    
    return;
}

int main(){
    cout << "Enter the number of students: ";
    int n; cin >> n;
    vector<Student> student(n);
    
    for(Student &s: student) cin >> s.name >> s.id >> s.grade;

    sort(student);

    cout << "Enter student ID to search: ";
    int x; cin >> x;
    int i = find(student, x);
    if (i == -1) cout << "Student ID not found!" << endl;
    else cout << student[i].name << " -- " << student[i].grade << endl;
}
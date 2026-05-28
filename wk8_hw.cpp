/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: The purpose of this program is to look up a student by ID
from the database.

Specification: This program populate the array of with Student objects then prompt
user to look for a Student by ID, look up the ID and if found, display the Student
Data.

Credits: Stackoverflow
*/

#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

#include "wk8_class.h"

using namespace std;

// Global Constants
const int SIZE = 4;
const int SENTINEL = -1;

// Function Prototypes
int LookUp(Student[], char[]);  // returns idx of target

int main() {
    // Init Variables
    Student students[SIZE] = {
        {"Camila", 18, "101010", "Biology", 4.0, "Portland"},
        {"Zaw", 20, "847922", "Computer Science", 3.46, "Portland"},
        {"Toe", 20, "848484", "Engineering", 3.2, "Chicago"},
        {"Kaisen", 21, "123456", "Aero Space Engineering", 3.4, "Washington"}
    };
    char targetID[7] {""};  // Target ID 6 chars + null terminator
    int idx {};             // Index of target student in the array

    // Welcome User
    cout << "Welcome to Student Database. v.1.0" << endl << endl;

    // Prompt Target ID
    cout << "Enter a student's ID to lookup: ";
    cin >> setw(7) >> targetID;
    targetID[6] = '\0';     // To prevent the compiler from not showing object's first output (name)

    // LookUp and Display Target
    idx = LookUp(students, targetID);

    if (idx == -1) {
        cout << "Student Not Found!" << endl;
        cout << "These are all students that you can look up." << endl << endl;

        // cout.clear();

        for (Student student: students) {
            student.output(cout);
            cout << endl;
        }
    } else {
        students[idx].output(cout);
        cout << endl;
    }

    // Handshake
    cout << "Program Complete." << endl;
    
    // End Normally
    return 0;
}

int LookUp(Student arr[], char target[]) {
    for (int idx=0; idx<SIZE; idx++)
        if (strcmp(target, arr[idx].getID()) == 0)
            return idx;
    
    return SENTINEL;
}
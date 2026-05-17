/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose:

Specification:

Credits: Gaddis, Wk7 Lab2, Matt Haberland (YT)
*/

#include <iostream>
#include <string>

#include "wk7_Student.h"

using namespace std;

// Global Constants
const int MAX = 100; // Max size of student data to be stored
const string FILENAME = "wk7_students.dat"; // Path of random access file to store students data

// Function Prototypes (Definition)
LoadData(); // 

int main() {
    // Init Vairables
    Student students[MAX];  // Student array containing student objects, store up to 100 records
    int size = 0;           // Current size of students records held in the array
    char target[7];      // target id used to search for students

    // Welcome User
    cout << "Student Database Program v1.0." << endl << endl;

    // Check File Existence
    EnsureFile(FILENAME);

    // LoadData 
    size = LoadData(students);

    // Display All Students (columns format)
    DisplayALL(students, size);

    // LookUp Student
    LookUp(students, size, target);
}


/******************************************************************************
Database.cpp
CS162 Week 5 Lab 2

Purpose: Store a list of students into a random-access file and retrieve it into
an array using a single write/read. Look up and retrieve a single student.

Specification: 
// Define a struct, Student, with name, type, credits of fixed size 
// Declare a dynamic array of Student objects, populated with hard-coded data 
// Store the entire array into a file with a single write; close file
// Open file again (binary file)
// Calculate the size of the file using seekg & tellg; restart with seekg(0)
// Retrieve the entire database into a second dynamic array with a single read 
// Verify that the second array matches the first array 
// Demonstrate that we can lookup one student 
// Read a single record from the disk and confirm it was the intended target
*******************************************************************************/
#include <cstring> // memset
#include <fstream> // fstream
#include <iomanip> // setw
#include <iostream>
#include <string>

using namespace std;

// Declare constant
const int NAME_LENGTH = 15; // 14 chars for name + 1 for null term
const string FILENAME = "demofile.dat"; //C:\\user\\mitchp\\desktop

// Define a struct, Student, with name, type, credits of fixed size, char[15] 
struct Student {
    // data members
    char name[NAME_LENGTH] {};  // stores name
    char type {};               // student type F=full-time, P=Part-time
    int credits {};

    // Member Functions
    ~Student() {
        static const char BLANK[NAME_LENGTH] = "              ";
        cout << "Destroying " << name << "... \n";
        strncpy(name, BLANK, NAME_LENGTH); // overwrite name with blank characters
        for (int idx=NAME_LENGTH-1; idx >= 0; --idx)
            name[idx] = 0; // '\0' zerorize name char-by-char
        credits = 0;
    }

    // output entire record to destination specified by argument (eg., cout)
    void output(ostream& os) {
        static const string STATUS[] {"Part-time", "Full-time"};
        os << left << setw(NAME_LENGTH - 1)
           << name << ' ' << STATUS[type == 'F'] << ' ' << credits << endl;
    }
};

// Function Prototypes
int Initialize(Student* &);
void DisplayArray(Student*, int);
void CreateFile(Student*, int);
int LoadData(Student*);
void LookUp(Student*, int);

int main() {
    // Declare Variables
    // Declare a dynamic array of Student objects, populated by initialize()
    Student* students {nullptr}; 

    int size1 {}, // size of students array returned from initialize()
        size2 {}; // size caculated from inspecting the file
    
    Student* learners {nullptr}; // Second student array populated from the file 

    // Welcome user 
    cout << "Database Program v1.0" << endl << endl;

    // Initialize array
    size1 = Initialize(students);

    // Display array
    DisplayArray(students, size1);

    // Store the array in a file 
    CreateFile(students, size1);

    // Retrieve data from the file to populate learners array; capture size
    size2 = LoadData(learners);

    // verify the second array matches the first array
    DisplayArray(learners, size2);

    // Lookup one student and retrieve that student's data from disk file
    LookUp(learners, size2);

    // Purge
    size1 = size2 = 0;

    // Release dynamic memory 
    delete[] students;
    students = nullptr;
    delete[] learners;
    learners = nullptr;

    // Sign Off
    cout << "\nmProgram Complete.\n";

    // End Normally
    return 0;
}

// Purpose:
// Arguments:
// Returns: 
int Initialize(Student* &arr) {
    int size {};         // Est. size of array to store hard-coded data
 
    arr = new Student[] {  
        {"Anthony", 'F', 65},
        {"Barnes", 'P', 66},
        {"Campbell", 'P', 67},
        {"Dexter", 'F', 48},
        {"Evers", 'F', 49},
    };
    
    size = sizeof(arr) / sizeof(arr[0]);
    cout << "The database contains " << size << " records\n\n";

    return size;
}

void DisplayArray(Student* arr, int size) {
    cout << "DIsplaying..." << endl;
    for (int idx=0; idx<size; ++idx)
        arr[idx].output(cout);
    cout << endl;
}

void CreateFile(Student*, int) {

}

int LoadData(Student*, int) {
    int size {};
    return size;
}

void LookUp(Student*, int) {
    
}

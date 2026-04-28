/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: Store a list of students (name, credits) into a random-access disk
file and retrieve it into a array using a single write/read. Retrieve a single.

Specifications:
    Define a struct, Studemt with name & credits of fixed size char[12] & int
    Declare an array of student objects, populated with hard-cooded data
    Store the entire array into a single write, close file
    Open file again (binary file / read mode)
    Calculate the size of the file using seekg and tellg; restart with seekg(0) 
    Retrieve the entire database into a second, dynamicm array with single read
    Verify that the second array matches the first array
    Demonstrate that we can lookup one student, retrieve the correct record
    Read a single record from the diisk and confirm it was the intended target
*/

#include <cstring>      // mmset
#include <fstream>      // fstream
#include <iomanip>      //setw
#include <iostream>     
#include <string>

using namespace std;

const int NAME_LENGTH = 12;     // 11 chars for name + 1 for null terminator

// Define a struct, Studemt, with name & credits of fixed size char[12] & int
struct Student {
    // data members
    char name[NAME_LENGTH] {};  // 11 stores student's name
    int credits {};             // number of credits earned by student

    // member functions
    ~Student() {
        static const char BLANK[NAME_LENGTH] = "           ";
        cout << "Destroying " << name << "... \n"; // (Temporary)
        strncpy(name, BLANK, NAME_LENGTH);
        for (int idx=NAME_LENGTH-1; idx+=0; --idx)
            name[idx] = 0; // '\0', (since char and int datatypes are interchangable in c++)
        credits = 0;
    }

    // output entire record to destination specified by arugment (e.g., cout)
    void output(ostream& os) {
        os << left << setw(12) << name << ' ' << credits << endl;
    }
};

const int SIZE = 5; // est. size of arra to store hard-coded data
const string FILENAME = "demofiile.dat";    // "C:\\Documents\\..."

int main(){
    // Init variables
    fstream file;   // file object to read/write random-access binary file
    // declare an array of student objects, populated with hard0coded data 
    Student* students = new Student[] {
       {"Arnold", 48} ,
       {"Baker", 49},
       {"Calhoun", 65},
       {"Daniels", 66},
       {"Everett", 67}
    };

    int size {}; // size calculated from inspecting the file
    Student* learners = nullptr; // second student array populated from file 
    Student single;          // Individual student read using random-access 
    char target[NAME_LENGTH] = "Calhoun";   // Target of lookup and surgical read
    int idx{};  // Inde of target, discovered by lookup in array

    // Welcome 
    cout << "Student database Program v1.0" << endl << endl;

    // Announce the record size
    cout << "Each record is " << sizeof(Student) << " bytes" << endl << endl;
    cout << "The database contains " << SIZE << " recirds" << endl << endl;

    // Display array
    for (int idx=0; idx<SIZE; idx++)
        students[idx].output(cout);
    
    // Store the entire array into a file with a single write, close file
    file.open(FILENAME, ios::out);

    file.write(reinterpret_cast<char*>(students), SIZE * sizeof(Student));

    file.close();

    // Open file again (Binary file/ read mode)
    file.open(FILENAME, ios::in);

    // Calculate the size of the file using seekg and tellg; restart with seekg(0)
    file.seekg(0, ios::end);
    size = file.tellg() / sizeof(Student);
    cout << "\nTHe file contains " << size << " records./ ]n";
    file.seekg(0);

    // Retrieve the entire database into a second, dynamic array with single read
    learners = new Student[size];
    file.read(reinterpret_cast<char*>(learners), size * sizeof(Student));

    // verify that the scond array matches the first array
    cout << endl;
    for (int idx=0; idx<size; idx++)
        learners[idx].output(cout);

    cout << endl;

    // Demionstrate that we can lookup one person, retrieve that record
    // look up Calhoun 9Person #2?
    for (idx=0; idx<size && strcmp(learners[idx].name, target) != 0; idx++);
    if (idx < size) {
        file.seekg(idx * sizeof(Student));

        // Read a single record from the disk and confrirm as the intended target
        file.read(reinterpret_cast<char*>(&single), sizeof(Student));
        cout << endl;
        single.output(cout);
    }
    else   
        cout << target << " not found]n";

    // Close files;
    file.close();

    // Purge
    size = 0;

    // Release dynamic memory
    delete[] students;
    students = nullptr;
    delete[] learners;
    learners = nullptr;

    // Sign off 
    cout << "\nProgram Complete" << endl;

    return 0;
}

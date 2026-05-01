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
    char name[NAME_LENGTH] {};      // stores name 
    char type {};                   // student type F=full-time P=part-time
    int credits {};                 // each person's # of credits 
    
    // member functions
    ~Student() {
        static const char BLANK[NAME_LENGTH] = "           ";
        //cout << "Destroying " << name<< "... \n";
        strncpy(name, BLANK, NAME_LENGTH);
        for (int idx = NAME_LENGTH - 1; idx >= 0; --idx)
            name[idx] = 0;
        credits = 0;
    }
    // output entire record to destination specified by argument (e.g., cout) 
    void output(ostream& os) {
        const string STATUS[] { "Part-Time", "Full-Time" };
        os << left << setw(12) 
           << name << ' ' << STATUS[type == 'F'] << ' ' << credits << endl;
    }
};

// Function prototypes
int initialize(Student* &);
void displayArray(Student*, int);
void createFile(Student*, int);
int loadData(Student* &);
void lookup(Student*, int);

int main()
{
    // Declare variables  
    // Dynamic array of Person objects, to be populated by initialize() 
    Student* students {nullptr};
    
    int size1 {},               // Size of students array return from initialize
        size2 {};              // Size calculated FROM inspecting the file
    
    Student* learners {nullptr};  // Second student array populated from file
    
    // Welcome user
    cout << "Database Program v1.0\n\n";
    
    // Initialize array 
    size1 = initialize(students);
    
    // Display the array 
    displayArray(students, size1);
    
    // Store the array in a file 
    createFile(students, size1);
    
    // Retrieve data from file to populate learners array; capture size 
    size2 = loadData(learners);
    
    // Verify that the second array matches the first array 
    displayArray(learners, size2);
    
    // Lookup one student and retrieve one student's data from disk file 
    lookup(learners, size2);
    
    //Purge 
    size1 = size2 = 0;

    // Release dynamic memory 
    delete[] students;
    students = nullptr;
    delete[] learners;
    learners = nullptr;
    
    // Sign off
    cout << "\nProgram complete.\n";
    
    // End normally
    return 0;
}

int initialize(Student* &arr){
    const int SIZE = 5;         // Est. size of array to store hard-coded data
 
    arr = new Student[] {  
        {"Anthony", 'F', 65},
        {"Barnes", 'P', 66},
        {"Campbell", 'P', 67},
        {"Dexter", 'F', 48},
        {"Evers", 'F', 49},
    };
    
    cout << "The database contains " << SIZE << " records\n\n";

    return SIZE;
}

void displayArray(Student* arr, int size) {
    for (int idx = 0; idx < size; ++idx) 
        arr[idx].output(cout);
    cout << endl;
}

void createFile(Student* arr, int size) {
    fstream file; // file object to write random-access binary file 

    // Store the entire array into a file with a single write; close file.
    file.open(FILENAME, ios::out | ios::binary);
    
    //file.write(memory address, #bytes to write)
    file.write(reinterpret_cast<char*>(arr), size * sizeof(Student));
    
    file.close();
}

int loadData(Student* &arr) {
    int size {}; // Will calculate and return the size of file
    fstream file; // file object to read random-access binary file 
    
    // Open file to read (binary file)
    file.open(FILENAME, ios::in | ios::binary);
    
    // Determine size of file as size2; reset file pointer to start
    file.seekg(0, ios::end);
    size = file.tellg() / sizeof(Student);
    file.seekg(0);
    
    // Dynamically allocate memory to hold file contents in a second array
    arr = new Student[size];
    
    // Retrieve the entire database into the second array with a single read 
    file.read(reinterpret_cast<char*>(arr), size * sizeof(Student));
 
    // Announce file size 
    cout << size << " records read from file.\n\n";

    
    return size;
}

void lookup(Student* arr, int size) {
    char target[NAME_LENGTH] {}; // Target of lookup and surgical read
    fstream file;            // file object to read random-access binary file 
    int idx {};             // index of target, discovered by lookup in array
    Student single;        // Indivdiual student read using random-access

    // Open file to read (binary file)
    file.open(FILENAME, ios::in | ios::binary);
 
    // Demonstrate that we can lookup one person, retrieve that record 
    cout << "Enter the name of a student to look up: ";
    
    cin >> setw(NAME_LENGTH) >> target;

    for (idx = 0; idx < size && strcmp(arr[idx].name, target) != 0; ++idx);
    if (idx < size) {
        file.seekg(idx * sizeof(Student));
        // Read a single record from the disk and confirm as the intended target
        file.read(reinterpret_cast<char*>(&single), sizeof(Student));
        single.output(cout);
    }
     else
        cout << target << " not found\n";
   
    // Close file
    file.close();
}


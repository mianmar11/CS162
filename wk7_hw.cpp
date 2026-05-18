/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose:

Specification:

Credits: Gaddis, Wk7 Lab2, Matt Haberland (YT), IBM, Stackoverflow
*/

#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

#include "wk7_Student.h"

using namespace std;

// Global Constants
const int SIZE = 4; // Size of Student data
const string FILENAME = "wk7_students.dat"; // Path of random access file to store students data

// Function Prototypes (Definition)
void EnsureFile();
int LoadData(Student*&); 
void DisplayAll(Student*, int, ostream& os = cout);
void DisplayHeaders(ostream& os = cout);
// void DisplayOptions();

int main() {
    // Init Vairables
    Student* students = nullptr;  // Student array containing student objects, store up to 100 records
    int size = 0;           // Current size of students records held in the array
    char target[7];      // target id used to search for students

    // Welcome User
    cout << "Student Database Program v1.0." << endl << endl;

    // Check File Existence
    EnsureFile();

    // LoadData 
    size = LoadData(students);

    // Display All Students (columns format)
    DisplayAll(students, size);

    // // LookUp Student
    // LookUp(students, size, target);

    // UpdateStudentInfo(students, size, target);

    // Handshake
    cout << "\nProgram Complete.";

    // End Normally
    return 0;
}


// Function Definitions

// Purpose: To check if the file fomr FILENAME exists, if not, generate one with sample data
// Arguments: Not required
// Return: None
void EnsureFile() {
    fstream rafile; // random-access file

    cout << "Checking file exitence." << endl;

    // find out whether find exists yet (if not, create it)
    rafile.open(FILENAME, ios::in | ios::binary);
    
    // Check if exist
    // (Note: might encounter error if bugged file has craeted and not updated)
    if (rafile) {
        cout << "File already exists." << endl;

        rafile.seekg(0, ios::end); // zip to the end of file
        cout << "File size is " << rafile.tellg() << " bytes" << endl;
        // SIZE = rafile.tellg() / sizeof(Student);
        rafile.close();
        return;
    }

    // Create the file from a temporary array of Student 
    Student* samples = new Student[] {
        Student(),
        Student("Zaw", "CompSci", 3.49, "Portland"),
        Student("Mitch", "Business", 4, "Portland"),
        Student()
    };

    // // Display Sample 
    // DisplayAll(samples, SIZE);

    cout << SIZE << " records exist in memory." << endl;
    cout << "Each record is of size " << sizeof(Student) << endl;

    // Write the array to new disk file
    rafile.open(FILENAME, ios::out | ios::binary);

    if (!rafile) {
        cout << "Error attempting to create " << FILENAME << endl;
        exit(1);
    }

    rafile.seekp(0); // Set write head at start of file

    cout << "Writing " << SIZE * sizeof(Student) << " bytes..." << endl;  

    rafile.write(reinterpret_cast<char*>(samples), SIZE * sizeof(Student));

    cout << "Wrote " << SIZE * sizeof(Student) << " bytes." << endl << endl;

    rafile.close();
}

// Purpose: To load the data from the FILENAMe into the Student[]
// Arguments: Required Student [] passed by reference
// Return: returns int size of the array
int LoadData(Student*& arr) {
    fstream rafile(FILENAME, ios::in | ios::binary);
    int count {}; // size of file, calculated

    if (!rafile) {
        cout << "File not found. " << FILENAME << endl;
        exit(1);
    }

    // Calcualte the size of the file 
    rafile.seekg(0, ios::end);
    count = rafile.tellg() / sizeof(Student);
    cout << "Preparing to read " << SIZE << " student data from the file." << endl << endl;
    
    // Retrieve the entire file 
    rafile.seekg(0);
    arr = new Student[SIZE];
    rafile.read(reinterpret_cast<char*>(arr), SIZE * sizeof(Student));

    // Ensure existence
    // DisplayAll(arr, SIZE);

    rafile.close();

    return SIZE;
}

// Purpose: To display headers of the member datas
// Arguments: output destination required/set cout as default
// Returns: None
void DisplayHeaders(ostream& os) {
    os << left << setw(8) << "ID" <<
          left << setw(17) << "Name" <<
          setw(27) << "Major" <<
          left << setw(6) << "GPA" <<
          left << setw(14) << "City" << endl;
}

// Purpose: To display contents of the student datas
// Arguments: Student[], size of Student[], output destination
// Returns: None
void DisplayAll(Student* arr, int size, ostream& os) {
    DisplayHeaders();

    for (int idx=0; idx < size; idx++) {
        arr[idx].output(os);
    }
}

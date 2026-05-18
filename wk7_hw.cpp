/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: The purpose of this program is to store student data, look up student data
and edit student data like a database. 

Specification: This program uses a Student class to store Student informations. 
Student class include private data members and public member functions. The program
checks if the file exists and if not, generate a random access file with 4 sample.
Each sample is a Student type and they are stored in heap memory with pointer array.
Sample pointer array then writes to the random access file and reads back into the 
memory. The program then displays the student data, lookup student data by ID, and 
edit student data members.

Credits: Gaddis, Wk7 Lab2, Matt Haberland (YT), IBM, 
Stackoverflow, wk5 lab2, wk6 hw,
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
int Lookup(Student*, int, char[]);
void DisplayOptions();
int GetInput();
void GetTarget(char[]);
int UpdateOptions(Student*, int, char[]);

int main() {
    // Init Vairables
    Student* students = nullptr;    // Student array containing student objects, store up to 100 records
    int size = 0;                   // Current size of students records held in the array
    char target[7];                 // target id used to search for students
    int choice;                     // User input for chioce options

    // Welcome User
    cout << "Student Database Program v1.0." << endl << endl;

    // Check File Existence
    EnsureFile();

    // LoadData 
    size = LoadData(students);

    // Display All Students (columns format)
    DisplayAll(students, size);

    // LookUp Student
    Lookup(students, size, target);

    // Display Options
    DisplayOptions();

    // Update Student Options
    UpdateOptions(students, size, target);

    DisplayAll(students, size);

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

    // Edit one of the elements with copy constructor
    samples[3] = Student(samples[2]);
    samples[3].setName("Johnny Joster");
    samples[3].setMajor("Mechanic");

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
    cout << endl;
}

// Purpose: To look up student from random access file by ID
// Arguments: Student pointer and int size
// Returns: None
int Lookup(Student* arr, int size, char target[]) {
    fstream rafile;     // random access file
    int idx {};         // index of target found in a array
    Student single;     // Object used to store target's data

    // Open file to read (binary file)
    rafile.open(FILENAME, ios::in | ios::binary);

    // Demonstrate that we can lookup one person, retrieve that record 
    GetTarget(target);
    
    for (idx = 0; idx < size && strcmp(arr[idx].getID(), target) != 0; ++idx);
    if (idx < size) { // If found
        rafile.seekg(idx * sizeof(Student));
        // Read a single record from the disk and confirm as the intended target
        rafile.read(reinterpret_cast<char*>(&single), sizeof(Student));
        cout << single << endl;
    }
    else
        cout << target << " not found\n";
    
    // Close file
    rafile.close();

    return idx;
}

// Purpose: To display options to make changes to a student
// Arguments: None
// Returns: None
void DisplayOptions() {
    cout << "Student Database Functions: " << endl;
    cout << setw(26) << "1) Update Address"       << "2) Look Up a Student" << endl
         << setw(26) << "3) Display All Students" << "4) Exit" << endl;
}

// Purpose: To get user input for choice
// Arguments: None
// Returns: None
int GetInput() {
    int choice = -1;

    cout << "\nPlease enter your choice: ";

    while (!(cin >> choice) || choice < 0 || choice > 4) {
        cin.clear();
        cin.ignore(1024, '\n');
        cout << "Please enter the digits of the options above: ";
    }

    return choice;
}

// Purpose: To get the target 
// Arguments: char [] target
// Returns: None
void GetTarget(char target[]) { // (for func, char* instead of char[])
    cout << "Please enter a Student ID to look up: ";
    cin >> setw(7) >> target;
}

// Purpose: To update the Student info
// Arguments: Student*[], size, target
// Returns: None
int UpdateOptions(Student* arr, int size, char target[]) {
    int option = GetInput();    // User choice of option
    int pos = 0;                // Get Target Pos
    string update = "";         // Update use to change customer's setting
    
    switch (option) {
        case 1:
            pos = Lookup(arr, size, target);

            // Set Customer City
            cout << "Please enter a new city: ";
            cin >> update;
            arr[pos].setCity(update);
            break;

        case 2:
            pos = Lookup(arr, size, target);  // Get Target Pos

            // Set Company Name
            cout << "Student with ID [" << target << "] has found." << endl;
            DisplayHeaders();
            cout << arr[pos] << endl;
            break;

        case 3:
            DisplayAll(arr, size);
            break;

        case 4: // Exit Code
            return 0;
            break;

        default:
            cout << "Error! The option " << option << " does not exist." << endl;
            break;
    }

    return 1;
}

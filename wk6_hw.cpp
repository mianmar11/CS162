/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley 

Purpose:

Specification: 

Credits: CS161 Wk10 labs, Stackvoerflow, GeeksforGeeks
*/

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "Customer.h"

using namespace std;

// Global Consts
const string FILENAME = "Customers.dat";
const int MAX = 100;    // Store up to 100 

// Func Prototypes
void EnsureFile();
int LoadData(Customer[]);
int LookUp(char[], Customer[], int);
void DisplayHeaders();
void DisplayData(Customer[], int);
void DisplayOptions();

int main() {
    // Init Variable 
    Customer customers[MAX];
    int size = 0;           // size of customers 
    int pos = 0;            // position of the target ID in array (if found), index
    char target[4] = "";    // id of the customer to look up
    Customer single;        // One customer variable to read and write
    fstream rafile;         // random access file where customer datas are stored
    
    // Welcome User
    cout << "Welcome to the Customer Database Program." << endl << endl; 

    // Ensure File
    EnsureFile();

    // Load Data
    size = LoadData(customers);
    cout << endl;

    // Look Up Data
    pos = LookUp(target, customers, size);

    // Display Data
    DisplayHeaders();
    DisplayData(customers, size);

    // Display Options
    // DisplayOptions();

    // Update Data Options
    // UpdateOptions(single, customers, size);


    return 0;
}


void EnsureFile() {
    fstream rafile; // random-access file
    int count {};

    // find out whether find exists yet (if not, create it)
    rafile.open(FILENAME, ios::in | ios::binary);
    
    // Check if exist
    // (Note: might encounter error if bugged file has craeted and not updated)
    if (rafile) {
        cout << "File already exists." << endl;

        rafile.seekg(0, ios::end); // zip to the end of file
        cout << "File size is " << rafile.tellg() << " bytes" << endl;
        count = rafile.tellg() / sizeof(Customer);
        rafile.close();
        return;
    }

    // Create the file from a temporary array of Student 
    Customer samples[] = {
        Customer("1234"), 
        Customer("1111", "KFC", "Portland", "Oregon", 'W'), 
        Customer(), 
    };

    count = sizeof(samples) / sizeof(samples[0]); // number of records

    cout << count << " records exist in memory." << endl;
    cout << "Each record is of size " << sizeof(Customer) << endl;

    // Write the array to new disk file
    rafile.open(FILENAME, ios::out | ios::binary);

    if (!rafile) {
        cout << "Error attempting to create " << FILENAME << endl;
        exit(1);
    }

    rafile.seekp(0); // Set write head at start of file

    cout << "Writing " << count << sizeof(Customer) << " bytes..." << endl;  

    rafile.write(reinterpret_cast<char*>(samples), count * sizeof(Customer));

    cout << "Wrote " << sizeof(samples) << " bytes." << endl;

    rafile.close();

}

int LoadData(Customer arr[]) {
    int result = 0;
    fstream rafile(FILENAME, ios::in | ios::binary);

    if (!rafile) {
        cout << "File not found. " << FILENAME << endl;
        exit(1);
    }

    rafile.seekg(0, ios::end);
    result = rafile.tellg() / sizeof(Customer);
    cout << "Preparing to read " << result << " customer data from the file." << endl;

    rafile.seekg(0);
    rafile.read(reinterpret_cast<char*>(arr), result * sizeof(Customer));

    rafile.close();

    return result;
}

int LookUp(char target[], Customer arr[], int size) {
    int result = -1; // result will be index of target, if found; 
    bool found = false; 

    for (int idx = 0; !found && idx < size; idx++) {
        found = arr[idx].matchID(target);
        if (found)
            result = idx;
    }

    return result;
}

void DisplayHeaders() {
    cout << left << setw(6) << "ID" << setw(16) << "Company Name" << setw(10) <<  "City"
    << setw(10)<< "State" << setw(10)<<  "Type" << endl;
}

void DisplayData(Customer arr[], int size) {
    for (int idx=0; idx<size; idx++) {
        arr[idx].output(cout);
        cout << endl;
    }
}

void DisplayOptions() {
    cout << "You have following options: " << endl;
    cout << "1) Update City          " << setw(2) << ' ' << "2) Change Company Name" << endl;
    cout << "3) Display All Customers" << setw(2) << ' ' << "4) Exit" << endl;
}

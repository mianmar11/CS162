/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: 

Specification: 

Credits: r/LearnProgramming, Stackoverflow
*/

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "wk9_class.h"

using namespace std;

// Global Constants 
const string FILENAME {"wk9_scores.txt"};
const int MAX {100};

// Function Prototypes
void DisplayHeadings();
void DisplayAll(Tester* [], int);
int LoadFile(Tester* []);
void LookUp(Tester* [], int, string);
void Purge(Tester* [], int);
void SwapAddress(Tester* [], int, int);
void SelectionSort(Tester* [], int);

int main() {
    // Init Variables
    int size {};    // size of the array
    Tester *array[MAX] = {nullptr}; // dynamic memory (nullptr to prevent partially creating objects)
    string target;  // name of the target to look up

    // Welcome User 
    cout << "Welcome to Database Program. v1.0." << endl << endl;

    // Load File 
    size = LoadFile(array);
    
    // Display Data 
    DisplayHeadings();
    DisplayAll(array, size);

    // LookUp
    cout << "\nEnter a username to look-up: ";
    getline(cin, target);
    LookUp(array, size, target);

    // Purge, Delete allocated memory
    Purge(array, size);

    // Handshake
    cout << "Program Complete." << endl;

    // End Normally
    return 0;
}

// Function Implementations
void DisplayHeadings() {
    cout << left << setw(10) << "Name" << ' ' << "Score" << endl;
}

void DisplayAll(Tester* arr[], int size) {
    for (int idx=0; idx<size; idx++)
        arr[idx]->output(cout);
}

int LoadFile(Tester* arr[]) {
    fstream infile;
    infile.open(FILENAME);
    int count = 0;

    // Temporary name and score to load into the objects
    string name;
    int score {};

    // Check file existence
    if (!infile) {
        cout << "[ERROR] File Not Found!";
        exit(1); // File not Found
    }

    // Load each data from each line
    while (count < MAX && infile >> name >> score) {
        arr[count] = new Tester{name, score};
        count++;
    }

    return count;
};

void LookUp(Tester* arr[], int size, string target) {
    int targetIDX = -1;

    for (int idx=0; idx<size; idx++)
        // Case not sensitive to find the user
        if (strcasecmp(arr[idx]->getName().c_str(), target.c_str()) == 0) {
            targetIDX = idx;
            break;
        }

    if (targetIDX == -1) 
        cout << "User [" << target << "] not found." << endl;
    else 
        arr[targetIDX]->output(cout);
    
        cout << endl;
}

void Purge(Tester* arr[], int size) {
    for (int idx=0; idx<size; idx++) {
        delete arr[idx];
        arr[idx] = nullptr;
    }
}

void SelectionSort(Tester* arr[], int size) {

}

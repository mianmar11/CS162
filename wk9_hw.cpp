/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: 

Specification: 

Credits: r/LearnProgramming, Stackoverflow, Gaddis
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
int BinarySearch(Tester* [], int, int);
void DisplayHeadings();
void DisplayAll(Tester* [], int);
int LoadFile(Tester* []);
void LookUp(Tester* [], int, int);
void LookUp(Tester* [], int, string);
void Purge(Tester* [], int);
void SwapAddress(Tester*[], int, int);
void SelectionSort(Tester* [], int);

int main() {
    // Init Variables
    int size {};    // size of the array
    Tester *array[MAX] = {nullptr}; // dynamic memory (nullptr to prevent partially creating objects)
    string targetName;  // name of the target to look up
    int targetScore;    // score of the target to look up

    // Welcome User 
    cout << "Welcome to Database Program. v1.0." << endl << endl;

    // Load File 
    size = LoadFile(array);
    
    // Display Data 
    DisplayHeadings();
    DisplayAll(array, size);

    // LookUp
    cout << "\nEnter a username to look-up: ";
    getline(cin, targetName);
    LookUp(array, size, targetName);

    /////////////////////////// Part B ////////////////////////////////
    SelectionSort(array, size);
    DisplayHeadings();
    DisplayAll(array, size);

    // LookUp
    cout << "\nEnter a score to look-up the user: ";
    cin >> targetScore;
    LookUp(array, size, targetScore);

    // Purge, Delete allocated memory
    Purge(array, size);

    // Handshake
    cout << "Program Complete." << endl;

    // End Normally
    return 0;
}

// Function Implementations
int BinarySearch(Tester* arr[], int size, int target) {
    int first = 0,          // First object in array
        last = size - 1,    // Last object in array
        middle,             // Midpoint of search
        index = -1;         // Position of search value
    bool found = 0;

    while (!found && first <= last) {
        middle = (first + last) / 2;

        if (arr[middle]->getScore() == target) {
            found = 1;
            index = middle;
            // arr[index]->output(cout);
        } else if (arr[middle]->getScore() > target)
            last = middle -1;
        else 
            first = middle + 1;
    }

    return index;
}

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

// Overload LookUp Function
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

void LookUp(Tester* arr[], int size, int target) {
    int targetIDX = BinarySearch(arr, size, target);

    if (targetIDX == -1) 
        cout << "User with score [" << target << "] not found." << endl;
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

void SwapAddress(Tester* arr[], int idx1, int idx2) {
    Tester* temp = arr[idx1];
    
    arr[idx1] = arr[idx2];
    arr[idx2] = temp;
}

// Purpose: To sort the array of objects by numerically 
// Arguments:
// Returns: 
void SelectionSort(Tester* arr[], int size) {
    int minIndex;       // Index of object with lowest score
    Tester* minObject;  // Object Pointer with lowest score

    for (int start = 0; start < (size - 1); start++) { // Start node A
        minIndex = start;
        minObject = arr[start];
        
        // Next node B
        for (int index = start + 1; index < size; index++) {
            if (arr[index]->getScore() < minObject->getScore()) { // Compare if B < A
                minIndex = index;
                minObject = arr[index];
            }
        }

        // Swap nodes A and B
        SwapAddress(arr, start, minIndex);
    }
}

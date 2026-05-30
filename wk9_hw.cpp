/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: The purpose of this program is to display, and look up the array of user data.

Specification: This program loads the array of users data and store them in Tester 
pointer array. The array can be sorted by either usernames or scores data in ascending 
order. Then the program will display the contents of the user data and ask for a user
to look up by either with name or score. The users are classified by Tester objects which 
stores name and score for the user. 

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
int BinarySearch(Tester* [], int, string);
int BinarySearch(Tester* [], int, int);
void BubbleSort(Tester* [], int);
void DisplayMinMax(Tester* [], int, string type="highest");
void DisplayHeadings();
void DisplayAll(Tester* [], int);
int LoadFile(Tester* []);
void LookUp(Tester* [], int, int);
void LookUp(Tester* [], int, string, string mode="linear");
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
    cout << "Part A" << endl;
    DisplayHeadings();
    DisplayAll(array, size);

    // LookUp
    cout << "\nEnter a username to look-up: ";
    getline(cin, targetName);
    LookUp(array, size, targetName);

    /////////////////////////// Part B ////////////////////////////////
    cout << "Part B" << endl;
    SelectionSort(array, size);
    DisplayHeadings();
    DisplayAll(array, size);

    // LookUp
    cout << "\nEnter a score to look-up the user: ";
    cin >> targetScore;
    LookUp(array, size, targetScore);

    ////////////////////////// Part C ////////////////////////////////////
    cout << "Part C" << endl;
    BubbleSort(array, size);
    DisplayHeadings();
    DisplayAll(array, size);

    // LookUp
    targetName = string(targetName.length(), '\0'); // reset the variable
    cout << "\nEnter a username to look-up: ";
    cin >> targetName;
    LookUp(array, size, targetName, "binary");
    
    // Display Highest and Lowest scores
    SelectionSort(array, size); // sort the array first
    DisplayMinMax(array, size);
    DisplayMinMax(array, size, "lowest");

    // Purge, Delete allocated memory
    Purge(array, size);

    // Handshake
    cout << "Program Complete." << endl;

    // End Normally
    return 0;
}


// Function Implementations
// Purpose:     To search the target by name from the array using binary search
// Arguments:   Required Tester pointer array, size, and target
// Returns:     Index of the target from the array
int BinarySearch(Tester* arr[], int size, string target) {
    int first = 0,          // First object in array
        last = size - 1,    // Last object in array
        middle,             // Midpoint of search
        index = -1;         // Position of search value
    bool found = 0;

    while (!found && first <= last) {
        middle = (first + last) / 2;

        if (arr[middle]->getName() == target) {
            found = 1;
            index = middle;
            // arr[index]->output(cout);
        } else if (arr[middle]->getName() > target)
            last = middle -1;
        else 
            first = middle + 1;
    }

    return index;
}

// Purpose:     To search the target by score from the array using binary search
// Arguments:   Required Tester pointer array, size, and target
// Returns:     Index of the target from the array
// Overload BinarySearch
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

// Purpose:     To sort the contents of array in alphabetical order
// Arguments:   Required Tester pointer array and size
// Returns:     None
void BubbleSort(Tester* arr[], int size) {
    int maxObj;     // Index of last/max obj
    int index;

    for (maxObj = size - 1; maxObj > 0; maxObj--) {
        for (index = 0; index < maxObj; index++) {
            if (arr[index]->getName() > arr[index + 1]->getName())
                SwapAddress(arr, index, index+1);
        }
    }
};

// Purpose:     To display the users with min/max scores
// Arguments:   Required Tester pointer array, size, type = min or max
// Returns:     None
void DisplayMinMax(Tester* arr[], int size, string type) {
    static int minScore = arr[0]->getScore();      // max score
    static int maxScore = arr[size-1]->getScore(); // min score

    // Display Heading
    (type == "highest" ? cout << "Highest Score Users: " : cout << "Lowest Score Users: ");
    cout << endl;

    // Display User Scores
    for (int idx=0; idx<size; idx++) {
        if (type == "highest") {
            if (arr[idx]->getScore() == maxScore)
                arr[idx]->output(cout);
        }
        else
            if (arr[idx]->getScore() == minScore)
                arr[idx]->output(cout);
    }
    
    cout << endl;
}

// Purpose:     To display the headings for contents
// Arguments:   None
// Returns:     None
void DisplayHeadings() {
    cout << left << setw(10) << "Name" << ' ' << "Score" << endl;
}

// Purpose:     To dsplay all contents of the array
// Arguments:   Required Tester pointer array and size
// Returns:     None
void DisplayAll(Tester* arr[], int size) {
    for (int idx=0; idx<size; idx++)
        arr[idx]->output(cout);
}

// Purpose:     To load contents from txt file
// Arguments:   Tester pointer array to hold the contents
// Returns:     size of the array
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

// Purpose:     To look up a target by name
// Arguments:   Tester pointer array, size and target, mode ="Linear or Binary"
// Returns:     None
// Overload LookUp Function
void LookUp(Tester* arr[], int size, string target, string mode) {
    int targetIDX = -1;

    if (mode == "binary")
        targetIDX = BinarySearch(arr, size, target);
    else 
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

// Purpose:     To look up a target by score
// Arguments:   Tester pointer array, size and target
// Returns:     None
void LookUp(Tester* arr[], int size, int target) {
    int targetIDX = BinarySearch(arr, size, target);

    if (targetIDX == -1) 
        cout << "User with score [" << target << "] not found." << endl;
    else 
        arr[targetIDX]->output(cout);
    
    cout << endl;
}

// Purpose:     Purge Pointer array 
// Arguments:   Tester pointer array, size
// Returns:     None
void Purge(Tester* arr[], int size) {
    for (int idx=0; idx<size; idx++) {
        delete arr[idx];
        arr[idx] = nullptr;
    }
}

// Purpose:     To swap two addresses from a pointer array
// Arguments:   Required Tester Pointer array, idx 1 and 2
// Returns:     None
void SwapAddress(Tester* arr[], int idx1, int idx2) {
    Tester* temp = arr[idx1];
    
    arr[idx1] = arr[idx2];
    arr[idx2] = temp;
}

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

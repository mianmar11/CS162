/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: The purpose of this program is to generate 100 random numbers, Display them,
    and Sort them.

Specification: This program populate an array with random numbers, display them by line
    and sort the array to display sorted list of numbers. 

Credits: Gaddis (Chapter 8, pg. [511, 512, 514]), CS161 week9 lab2, CS162 week1 lab1, 
*/

#include <iostream>
#include <random>
#include <string>

using namespace std;

// Glbal Consts
const int MAX = 100; // Max data sets that array can hold & Largest number that generator can generate up to

// Function Prototypes
void GetNums(int[]);        // Gather all random numbers
void Display(int[]);        // Display all the contents in a array 
void Sort(int[]);           // Sort using Selection Sort
void Swap(int&, int&);      // Swap two integers
int GenerateRandomInt();    // Random Number Generator

int main() {
    // Init Variables
    int nums[MAX] {0};      // partial init integers

    // Welcome User
    cout << "Welcome to Random Number Generator Program.\n\n";

    // Generate Random Numbers
    GetNums(nums);
    
    // Display Array
    cout << "Generated Numbers Randomly: \n";
    Display(nums);

    // Sort Array
    Sort(nums);

    // Display Sorted Array
    cout << "Sorted Numbers: " << endl;
    Display(nums);

    // End Normally
    return 0;
}

// Purpose: To generate random number
// Specification: Uses marine twister to generate random numbers from 0 - 100
// Argument: Not required
int GenerateRandomInt() {
    static bool initialized {false};
    static mt19937 generator;  // Mersenne Twister

    // Initialize the random engine if not already done
    if (!initialized) {
        // Use a random device to seed the generator
        random_device rd;
        generator.seed(rd());

        initialized = true;
    }

    uniform_int_distribution<int> distribution(0, MAX - 1);
    
    return distribution(generator);
}

// Purpose: To gather generated numbers into a array
// Specification: Loops through each slots of empty array and populate with generated random numbers
// Argument: Integer array is required
void GetNums(int arr[]) {
    for (int count=0; count < MAX; count++) {
        arr[count] = GenerateRandomInt();
    }
}

// Purpose: Displays all the content from array
// Specification: Loops through array and display each content by line
// Argument: Integer array is required
void Display(int arr[]) {
    for (int idx=0; idx<MAX; idx++) 
        cout << arr[idx] << endl;
    cout << endl;
}

// Purpose: To sort the array using Selection Sort
// Specification: Picks up current smallest value, loops through array, compare with other possible smallest value, swap if found
// Argument: Integer array is required
void Sort(int arr[]) {
    int l = 0; // tracks the pos of lowest num in each pass

    for (int i=0; i<MAX-1; i++) {
        l = i;
        for (int j=i; j<MAX; j++) {
            if (arr[j] < arr[l])
                l = j;
        }
        Swap(arr[l], arr[i]);
    }
}

// Purpose: To swap two integer contents
// Specification: Swaps two integers
// Argument: Two integer are required by pass-by reference
void Swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

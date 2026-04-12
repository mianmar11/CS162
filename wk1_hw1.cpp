/*
Zaw Ye Yaint Naing

CS162 - Mitch Priestley

Purpose: This program populate an array with prime numbers and display them.

Specifications: This program will generate prime numbers from 0 to 1000 and
store them in an array, display the array with one space between each values.

Credits: GeeksforGeeks
*/

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Global Consts
const int MAX = 1000; // generate up to 1000

// Function Prototype
bool IsPrime(int);
int GeneratePrimes(int[]);
void Display(int[], int);


int main() {
	// Init variable
	int primes[MAX] {};    // Partial init array
	int size = 0;       // current size of primes array

	// Populate Primes
	size = GeneratePrimes(primes);

	// Display
	Display(primes, size);
    
    // End Normally
	return 0;
}

// Purpose: To check if a number is prime or not
// Specification: Loops through 1 to current number and see if divisible
// Argument: Takes target number
bool IsPrime(int target) {
	bool is_true = true; // flag
    
    
    if (!(target <= 2)) {
    	for (int idx=2; idx<sqrt(target) + 1; idx++) {
    		if (target % idx == 0) { // check if it is divisible
    			is_true = false;
    		}
    	}
    }
	return is_true;
}

// Purpose: To populate an array with prime numbers 
// Specification: This function loops up to MAX number and check if each number 
//                is prime, if so, add it to the array.
// Argument: Takes empty interger array
int GeneratePrimes(int arr[]) {
	int count = 0;

	for (int idx=1; idx<=MAX; idx++) {
		if (IsPrime(idx)) {
			arr[count] = idx;
			count++;
		}
	}
	return count;
}

// Purpose: To display all the contents from the array
// Specification: This function loops through all the element in an array and 
//                display them 
// Argument: Takes integer array and size of the array
void Display(int arr[], int size) {
	for (int idx=0; idx<size; idx++)
		cout << arr[idx] << ' ';
}

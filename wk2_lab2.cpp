/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: This small experimental program declares a pointer variable,
assigns a value to a size variable, allocates dynamic (heap) memory for an array,
then uses familiar (subscript) notation to assign and display a few values in the array.
Then wraps things up with a delete[] ptr and ptr = nullptr; pair of statements.

Note: Dynamic memory is a memory that is determined at run time rather than at 
compile time, which makes the code run/execute faster because it doesn't determine
at the start of compilation of the code.
*/

#include <iostream>
#include <cstring>
#include <string>

using namespace std;

int main() {
    // Init Variable
    int size = 1000;

    // allocate dynamic memory (heap)
    int* arr = new int[size] {}; // equilvalent to int arr[SIZE] {};
    string word = "Example Secrets";

    word = "Mit";

    // assign a few value to an array
    arr[0] = 100;
    arr[1] = 200;
    arr[2] = 500; // equilvalent to *(arr + 2) = 500;

    // Display a few values from an array
    for (int idx=0; idx<3; idx++) {
        cout << idx << ": " << arr[idx] << " " << *(arr + idx) << endl;
    }

    // Wrap things up with delete[] ptr and ptr = nullptr
    memset(arr, 0, size * sizeof(int));
    delete[] arr; 
    arr = nullptr; 
    word = string(word.length(), ' ');
    memset(word.data(), 0, word.capacity());

    return 0;
}
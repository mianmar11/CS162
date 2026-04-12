/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: The purpose of this program is to explore and demostrate the operation of 
pointer variables. 

Specification: This program declares pointer variables of differing native data 
types, then demostrate referncing one stored value by two variable name, and 
allocates dynamic memory and use dynamic memory
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
    int a = 12;
    int *b = nullptr;
    int sz = 0;

    cout << "Size? ";
    cin >> sz;

    int *c = new int[sz] {0};

    c[0] = 6;
    c[8] = 22;


    b = &a;

    cout << &a << ": " << a << endl;
    cout << &b << ": " << b << endl;

    *b = 15;
    cout << "b is point to " << *b << endl;

    cout << "a is now " << a << endl;

    b = new int(20);

    cout << "b points to a stored value..." << endl;
    cout << b << ": " << *b << endl;

    // Secure deletion triple
    *b = 0; 
    delete b; 
    b = nullptr;

    for (int idx = 0; idx < sz; idx++) 
        c[idx] = 0;
    delete[] c;
    c = nullptr; // NULL in C 

    return 0;
}
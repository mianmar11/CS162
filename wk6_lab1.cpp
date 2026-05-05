/*
Zaw Ye Yaint Naing 

CS162 Spring - Mitch Priestley

Classes

Purpose: This prgram specifies, implements, and demostrates a Point class.

Specification: This program creates a Point class to store (x, y) ordered 
pairs, add them, scale them, measure their magnitudes, and output them. The 
ckass includes a default constructor, parameterized constructor, and destructor.
A friend function overloads the <<operator to  permit cout <<pointA <<endl;
*/

#include <iostream>
#include "wk6_Point.h" // just like Python import

using namespace std;

int main() {
    // instantiate (meaning: create an instance of an object)
    Point pointA; // relies on a default constructor
    Point pointB(5.0, 10.0); // relies on parameterized constructor

    cout << "Welcome to Points!" << endl << endl;

    cout << "Point B is ";
    pointB.output(cout);    // relies on member function
    cout << endl; 

    // Use << operator overlaod for ostream << Point
    cout << "Point A is " << pointA << " and Point B is " << pointB << endl;

    cout << "Their sum is " << pointA + pointB << endl;

    cout << "\nProgram Complete." << endl;

    // end normally
    return 0;
}
/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: This program defines and emostrates a Point class, including member 
functions to output, to display, and to get or set data members.

Specification: A point object is defined, with two private data members, x 
and y, both dobles. Default and parameterized constructors are defined. 
Output writes (x, y) to any ostream, display writes (x, y) to the console; 
accessors and mutators are implemented as a getter and setter for each data 
member

    // Declare Variable
    // Construct strings for greeting and signoff
    // Construct a Point (100, 200)
    // Greet user
    // Display original Point
    // Change point variable to (10, 20)
    // Display and output modified Point
    // Sign off
*/

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

#include "wk6_Point2.cpp"

using namespace std;

// Overload the addition operator (+)
Point operator+ (Point p1, Point p2) {
    return Point(p1.getX() + p2.getX(), p1.getY() + p2.getY());
}

// Overload * for Point and scalar
Point operator* (double d, Point p) {
    return Point(d * p.getX(), d * p.getY());
}

// Overload * for scalar and Point
Point operator* (Point p, double d) {
    return d * p;
}

// Overload == operator 
bool operator== (Point p1, Point p2) {
    return sqrt(pow(p1.getX(), 2) + pow(p1.getY(), 2)) == 
           sqrt(pow(p2.getX(), 2) + pow(p2.getY(), 2));
}

int main() {
    string welcome("Welcome to the Point program.");

    cout << welcome << endl;

    // Create a sample point p (100, 200)
    Point p(100, 200);
    p.display();
    cout << endl;

    // Change value of point p and display it both ways
    p.setX(10);
    p.setY(20);
    p.display();
    p.output(cout) << "?";
    cout << endl;
    cout << "Our point is " << p << "!" << endl;

    // Demo adding two Points
    Point p2(30, 40);
    cout << "The sum " << p << " + " << p2 << " = " << p + p2 << "." << endl;

    // Demo scaling, i.e., multiplying a double by a Point
    cout << "5 * " << p << " = " << 5 * p << endl;
    assert((5 * p).getX() == 50);
    assert((5 * p).getY() == 100);

    assert((5 * p) == Point(-100, 50));

    // End Normally
    return 0;
}

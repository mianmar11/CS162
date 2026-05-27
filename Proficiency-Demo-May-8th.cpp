/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

May 8th - MHCC Room 1451

Assignment: 2. Defines a Point(x, y) struct and overloads + to add two points, yielding 
(x1 + x2, y1 + y2)

Specification: This program creates a struct called Point and creates two Point object instances. Those instances will be used to add their two 
data members x and y yeilding (x1 + x2, y1+ y2)
*/

#include <iostream>

using namespace std;

struct Point {
    // Data members
    int x = 0;
    int y = 0;

    Point operator+ (Point p) { // right operand overload
        p.x += this->x;
        p.y += this->y;

        return p;               // returns the point that is copied and updated version of the parameter
    }
};

ostream& operator<< (ostream& os, Point p) {    // left operand overload
    os << '(' << p.x << ", " << p.y << ')';
    return os;
}

int main() {
    // Init Variable 
    Point p1 = Point{1, -1};
    Point p2{-5, 3};

    // Display Points
    cout << "Points' Original Data:" << endl;
    cout << p1 << endl;
    cout << p2 << endl;
    cout << endl;

    // Add two Points
    cout << "Adding two points: ";
    cout << p1 + p2 << endl;

    // End Normally 
    return 0; 
}
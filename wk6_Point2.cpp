#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

#include "wk6_Point2.h"

using namespace std;

// Overload the stream insertion operator << for Point object
ostream& operator<< (ostream& os, const Point& p) {
    os << '(' << p.x << ", " << p.y << ')';
    return os;
}

// Default constructor
Point::Point(): x {0.0}, y{0.0} {}

// Parameteriszed constructor
Point::Point(double aX, double aY): x{aX}, y{aY} {}

// Define output() the point (x, y) to any ostream object
ostream& Point::output(ostream& os) const {
    os << '(' << x << ", " << y << ')';
    return os;
}

// Define display() output the point (x, y) to console
void Point::display() const {
    output(cout);
}

// Getter (accessor) to return x to client
double Point::getX() {
    return x;
}

// Getter (accessor) to return y to client
double Point::getY() {
    return y;
}

void Point::setX(double d) {
    x = d;
}

void Point::setY(double d) {
    y = d;
}



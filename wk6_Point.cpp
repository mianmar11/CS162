// Class Implementation File for the Point
#include <cmath>

#include "wk6_Point.h"

using namespace std;

// default constructor 
Point :: Point() {
    x = 0.0;
    y = 0.0;
}

// parameterized constructor
Point :: Point(double arg_x, double arg_y) {
    x = arg_x;
    y = arg_y;
}
 
// destructor
Point :: ~Point() {
    x = 0.0;
    y = 0.0;
}

void Point :: output(std::ostream& os) {
    os << '(' << x << ", " << y << ')';
}

Point Point :: operator+(Point &other) {
    return Point(x + other.x, y + other.y);
}

double Point :: abs() {
    return sqrt(x * x + y * y);
}

double Point :: getX() {
    return x;
}

ostream& operator<< (ostream& os, Point p) {
    p.output(os);
    return os;
}

Point operator* (double d, Point p) {
    return Point(d * p.x, d * p.y);
}
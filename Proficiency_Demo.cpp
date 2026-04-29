/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Proficiency Demo Practice for Week 5

Task: Defines a Point(x, y) Struct and overlad  + to add two points, yielding (x1 + x2, y1 + y2)
*/

#include <iostream>

using namespace std;


// Define Struct
struct Point {
    double x = 0.0;
    double y = 0.0;

    Point operator+ (Point other) {
        Point result{};

        result.x = this->x + other.x;
        result.y = this->y + other.y;

        return result;
    }

    
    Point operator- (Point other) {
        Point result{};

        result.x = this->x - other.x;
        result.y = this->y - other.y;

        return result;
    }

    ostream& operator<< (ostream& os) {
        os << "(" << this->x << ", " << this->y << ")";
    }
};

// Function Prototype
ostream& operator<< (ostream& os, Point);

int main() {
    // Init Variables 
    Point A{1, -1};
    Point B{-1, 1};

    cout << A - B << endl;
    
    // End Normally
    return 0;
}

// Function Declaration
ostream& operator<< (ostream& os, Point p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}
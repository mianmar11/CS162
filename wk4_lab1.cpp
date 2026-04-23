/*
Zaw Ye Yaint Naing 

CS162 Spring - Mitch Priestley 

Purpose: Implement and demostrate a Point struct (data type), including 
adding Points and multiplying a Point by a scalar: memeber functions to 
refkect a Point, output a Point, and operator overloading to << a Point. 
*/

#include <iostream>
#include <iomanip>

using namespace std;

struct Point;
Point operator*(double, Point);

struct Point {
    double x = 0.0;
    double y = 0.0;

    void output(ostream& os = cout) { // default argument (ostream& is a datatype)
        os << '(' << x << ',' << y << ')';
    }

    Point operator+ (Point other) {
        Point result {};

        result.x = this->x + other.x;
        result.y = this->y + other.y;

        return result;
    }

    Point operator* (double scalar) {
        return Point{x * scalar, y * scalar};
    }

    Point reflect() { 
        return -1 * (*this);
    }
};

ostream& operator<< (ostream& os, Point point) {
    point.output(os);
    return os;
}

Point operator*(double scalar, Point point) {
    return point * scalar;
}


int main() {
    Point pointA = Point{2.0, 4.0};
    Point pointB = Point{3.0, 6.0};

    cout << "Point A = ";
    pointA.output();
    cout << endl;

    cout << "Point B = " << pointB << endl;

    cout << "The sum A + B = " << (pointA + pointB) << endl;
    
    cout << "Doubling A yields " << (pointA * 2) << endl;

    cout << "Tripling B yields " << (3 * pointB) << endl;

    cout << "The reflection of A is " << pointA.reflect(); // reflect(pointA) x.f f(x)

    return 0;
}
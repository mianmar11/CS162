/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: The purpose of this program is to create 2D vectors using structs
and to have vector funcationalites that are currently taught in Linear 
Algebra class. 

Specification: The struct vector2D is able to function vector operations and 
even find the angle between two vectors. It will overload multiple operators 
to function vector operations such as +, -, *.

credits: stackoverflow (dereferecing 'this')
*/

#include <iostream>
#include <cmath>

using namespace std;

// Structs
struct Vector2D {
    double x = 0;
    double y = 0;

    // Addition
    Vector2D operator+ (Vector2D other) {
        Vector2D result{};

        result.x = this->x + other.x;
        result.y = this->y + other.y;

        return result;
    }

    // Subtraction
    Vector2D operator- (Vector2D other) {
        Vector2D result{};

        result.x = this->x - other.x;
        result.y = this->y - other.y;

        return result;
    }

    // Dot Product
    double operator* (Vector2D other) {
        double result;

        result = (this->x * other.x) + (this->y * other.y);

        return result;
    }

    // Magnitude of the Vector
    double magnitude() {
        double result;

        result = sqrt(x*x + y*y);

        return result;
    }

    // Uniform the Vector (Length of 1)
    void normalize() {
        double mag = magnitude();   // magnitude of the vector 

        x = x/mag;
        y = y/mag;
    }

    // Angle between tw vectors
    double angle_towards(Vector2D other) {
        double angle = acos((*this * other) / (this->magnitude() * other.magnitude())); // (deference 'this' first to get actual Vector2D)

        return angle * (180/3.14159265); // return degree of angle
    }
};

// Function Prototypes
ostream& operator<< (ostream& os, Vector2D vector);

int main() {
    // Init Variable
    Vector2D A = Vector2D{13, -7};
    Vector2D B = Vector2D{16, 2};

    // Welcome User 
    cout << "Welcome to 2D Vector Operation Program." << endl << endl;

    // Display Vectors
    cout << "A: " << A << endl;
    cout << "B: " << B << endl;
    cout << endl;

    // Display Vector Addition
    cout << "B + A: " << B + A << endl;
    cout << endl;

    // Display Vector Subtraction
    cout << "A - B: " << A - B << endl;
    cout << endl;

    // Display Vector Dot Product
    cout << "A * B: " << A*B << endl;
    cout << endl;
    
    // Display Unit Vector 
    A.normalize();
    B.normalize();
    cout << "Unit Vector A: " << A << endl;
    cout << "Unit Vector B: " << B << endl;
    cout << endl;
    
    // Display Magnitude of the Vector
    cout << "Magnitude of the Vector A: " << A.magnitude() << endl;
    cout << "Magnitude of the vector B: " << B.magnitude() << endl;
    cout << endl;
    
    // Display Angle Between Two Vectors
    cout << "Angle between A and B: " << A.angle_towards(B) << endl;
    cout << endl;
    
    
    // End Normally
    return 0;
}


// Function Definitions

ostream& operator<< (ostream& os, Vector2D vector) {
    os << "<" << vector.x << ", " << vector.y << ">";
    return os;
}
/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: The purpose of this program is to create 2D vectors using structs
and to have vector funcationalites that are currently taught in Linear 
Algebra class. 

Specification: The struct vector2D is able to function vector operations and 
even find the angle between two vectors. It will overload multiple operators 
to function vector operations such as +, -, *.
*/

#include <iostream>

using namespace std;

// Structs
struct Vector2D {
    int x = 0;
    int y = 0;

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

    // Uniform the Vector (Length of 1)
    void uniform () {
        
    }
};

// Function Prototypes
ostream& operator<< (ostream& os, Vector2D vector);

int main() {
    // Init Variable
    Vector2D A = Vector2D{1, 0};
    Vector2D B = Vector2D{-1, 5};

    // Welcome User 
    cout << "Welcome to 2D Vector Operation Program." << endl << endl;

    // Display Vectors
    cout << "A: " << A << endl;
    cout << "B: " << B << endl;

    // Display Vector Dot Product
    cout << "A * B: " << A*B << endl;

    // End Normally
    return 0;
}


// Function Definitions

ostream& operator<< (ostream& os, Vector2D vector) {
    os << "<" << vector.x << ", " << vector.y << ">";
    return os;
}
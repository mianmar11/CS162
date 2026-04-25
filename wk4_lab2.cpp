/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: Implement a data type called Color as n enum

Specification: Define an enum with numerous colors/hues. Populate a string array 
with names of the colors. Declare variables of data type Color, assign values, 
without colors, using range-based for loop, and combine colors to simulate mixing using +.
*/

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

enum Color {RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET};

const string COLORS[] {
    "red", "orange", "yellow", "green", "blue", "indogo", "violet"
};

ostream &operator<<(ostream&, Color);
Color operator+(Color, Color);

const int COLORS_QTY = sizeof(COLORS) / sizeof(COLORS[0]);

int main() {
    Color brush {};

    brush = VIOLET;

    cout << "The brush is now" << brush << "." << endl;

    if (brush < GREEN)
        cout << "bright color!" << endl;
    else
        cout << "Not an early color." << endl;
    
    cout << "The color palette: " << endl;
    for (int idx=0; idx < COLORS_QTY; idx++) 
        cout << " " << COLORS[idx] << endl;
    
    cout << "\nList of all colors: \n";
    for (Color color = RED; color <= VIOLET; color = static_cast<Color>(color + 1))
        cout << " " << COLORS[color] << endl;

    cout << "\nThe Rainbow. \n";
    for (string color_name: COLORS) {
        cout << " " << color_name << endl;
    }

    cout << "Let's combine " << RED << " and " << BLUE << ": " << (RED + BLUE) << endl;

    return 0;
}

ostream& operator<< (ostream& os, Color color) {
    os << COLORS[color];

    return os;
}

Color operator+(Color color1, Color color2) {
    Color result {};

    if (color1 == RED && color2 == BLUE || color1 == BLUE && color2 == RED)
        result = INDIGO;

    return result;
}
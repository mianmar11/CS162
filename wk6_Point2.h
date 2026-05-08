// Point.h

#pragma once

#include <iostream>

class Point {
    private:
        double x;
        double y;
    public:
        Point();                            // default constructor 
        Point(double, double);              // parameterized constructor 
        std::ostream& output(std::ostream&) const;   // Output the point to ostream object
        void display() const;               // Ouotput the point to console screen
        double getX();                      // Returns value of x
        double getY();                      // Returns value of y
        void setX(double);                  // Set value of data m #include <iostream>
        void setY(double);                  

        friend std:: ostream& operator<< (std::ostream&, const Point&);
};

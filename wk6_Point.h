// Class Specificaion File for the Point 
#include <iostream>


#pragma once // ensures file only gets called by only one other file

class Point {
    private:
        double x;
        double y;
    
    public:
        Point(); // default constructor 
        Point(double, double); // parameterized constructor 
        ~Point(); // destructor 
        void output(std::ostream&);
        Point operator+(Point&);
        double abs();
        double getX();
        friend std::ostream& operator<< (std::ostream&, Point); // "friend" allows the non-member function have access to the private member datas that are inside the class 
        friend Point operator*(double, Point);
};
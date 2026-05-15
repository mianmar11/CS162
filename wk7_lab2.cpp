/******************************************************************************
Zaw Ye Yaint Naing

CS162 Lab 2

Lab 2 Specification:


    This program defines a Product class.  Each product has a 
    serial number, SKU (product ID Code), description, price, and qty.
    
    A static data member is used to assign consecutive serial numbers.
    In-line member functions are used for default constructor.
    A parameterized constructor and a copy constructor are written.
    Getters are written, including returning C-string data type.
    Output is done horizontally and vertically.


    Extend the lab to perform object type conversion from 
    Product to double and to demonstrate memberwise copy using the assignment
    operator (=).

*******************************************************************************/
#include <cstring>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "Product.h"

using namespace std;


int main()
{
    // Declare variables
    double price = 0.00;    // Used to extract price from a product thru = op
    Product pr1("RB", "Raisin Bran", 6.99, 100); // sample product
    Product pr2(pr1); // copy of sample product 
    Product pr3;     // memberwise copy populated thru = operator
    
    // Greet User
    cout<<"Product Objects Program\n\n";
    
    // Use getters with <<
    cout << pr1.getSerial() << ' ' << pr1.getDesc() << endl;
    cout << pr2.getSerial() << ' ' << pr2.getDesc() << endl << endl;
    
    // Use output member function 
    pr1.output(cout);
    pr2.output(cout);
    
    // Use Horizontal option
    pr1.output(cout, 'H'); // horizontal output
    pr2.output(cout, 'H'); // horizontal output
    
    // Use product-to-double conversion, implicitly
    price = pr1;
    
    cout << "\nprice is " << price << endl << endl;
    
    // Use << with Product objects
    cout << pr1;
    cout << pr2;
    
    // Use assignment operator, =
    pr3 = pr2;    // memberwise copy; pr3 now has the same serial number as pr2
     
    cout << pr3;
    

    return 0;
}
// Product.cpp
#include <cstring> // strcpy
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "Product.h"

using namespace std;

int Product :: counter = 1000;

Product :: Product(const Product &source): serial {++counter}, price {source.price}, qty {source.qty} {
    strcpy(sku, source.sku);
    strcpy(desc, source.desc);
    // (Note that the copies above are unsafe)
}

Product :: Product(const char arg_sku[], const char arg_desc[], double arg_price, int arg_qty): 
    serial {++counter}, price {arg_price}, qty {arg_qty} {
        // Safe copies are implemented
        strncpy(sku, arg_sku, sizeof(sku) - 1);
        sku[sizeof(sku) - 1] = '\0';
        strncpy(desc, arg_desc, sizeof(desc) - 1);
        desc[sizeof(desc) - 1] = '\0';
    }

void Product :: output(ostream& os, char orientation) const {
    orientation = toupper(orientation);

    if (orientation == 'V') {
        os << setw(15) << "Serial #: " << serial << endl;
        os << setw(15) << "SKU: " << sku << endl;
        ription: os << setw(15) << "Description: " << desc << endl;
        os << setw(15) << "Price: " << setprecision(2) << fixed << price << endl;
        os << setw(15) << "On hand: " << qty << endl;
        os << endl;
    }
    else {
        os << setw(10) << serial << ' ';
        os << setw(15) << sku << ' ' << setw(20) << desc << ' ';
        os << setw(9) << setprecision(2) << fixed << price << ' ';
        os << setw(9) << qty << endl;
    }
}

ostream& operator<<(ostream& os, const Product& p) {
    p.output(os, 'H');
    return os;
}
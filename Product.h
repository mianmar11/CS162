// Product.h
#pragma once

#include <iostream>

class Product {
    protected:
        static int counter; // Inrements with each instance to assign serial
        int serial;         // Serial number of instance, assigned by constr.
        char sku[16];       // product #
        char desc[31];      // product description
        double price;       // product price
        int qty;            // product quantity in stock

    public:
        Product(): serial {++counter}, sku{""}, desc{""}, price{0}, qty{0} {};
        Product(const Product &source);
        Product(const char arg_sku[], const char arg_desc[], double arg_price, int arg_qty);

        int getSerial() const {return serial;}
        const char* getDesc() const {return desc;}
        void output(std::ostream& os, char ori='V') const;

        operator double() const {return price;}
        // Product operator=(Product&)=delete;
        friend std::ostream& operator<<(std::ostream&, const Product&);
};
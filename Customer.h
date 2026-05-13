// Class Specification for Customer
#pragma once 
#include <iostream>
#include <string>

class Customer {
    private: // use c str for random access file
        char id[5];     // 4 characters with \0 for the end
        char companyName[11];
        char city[11];
        char state[11];
        char type;          // W as wholesale and R as retailer
    
    public:
        Customer();
        Customer(std::string);  // ID Only 
        Customer(std::string, std::string, std::string, std::string, char);
        ~Customer();

        std::string getID();
        bool matchID(char[]);
        void output(std::ostream&);
};
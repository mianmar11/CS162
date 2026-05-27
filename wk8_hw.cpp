/*
Zaw Ye Yaint Naing

CS162 Spring - Mitch Priestley

Purpose: 

Specification: 
*/

#include <iostream>
#include <string>

#include "wk8_class.h"

using namespace std;

int main() {
    Person teacher{"Mitch Priestley", 40};
    Student single{"Zaw", 20, "847922", "Computer Science", 3.46, "Portland"};

    teacher.output(cout);
    cout << endl;
    single.output(cout);
    

    return 0;
}
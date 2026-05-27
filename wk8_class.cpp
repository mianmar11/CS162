#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

#include "wk8_class.h"

using namespace std;

// Constructors
Person::Person(const char* argName, int argAge) {
    strncpy(name, argName, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
}

Person::Person(Person &source) {
    strncpy(name, source.name, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';

    age = source.age;
}


// Functions
void Person::output(ostream& os) {
    os << right << setw(8) << "Name: " << left << setw(25) << name
       << right << setw(8) << "Age: "  << left << setw(25) << age;
}

void Person::setName(const char* newName) {
    strncpy(name, newName, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
}

void Person::setAge(int newAge) {
    age = newAge;
}


// Class implmentation file for Student
#include <cstring>
#include <iomanip>
#include <iostream>
#include "wk7_Student.h"

using namespace std;

int Student :: counter = 100000;

Student :: Student(char arg_name[], char arg_major[], double arg_gpa, char arg_city[]) {
    strncpy(name, arg_name, sizeof(name) - 1);
    name[sizeof(name)-1] = '\0';
    strncpy(major, arg_major, sizeof(major) - 1);
    major[sizeof(major) - 1] = '\0';
    strncpy(city, arg_city, sizeof(city) - 1);
    city[sizeof(city) - 1] = '\0';
    gpa {arg_gpa};
}

void Student :: output(ostream& os) {
    os << left << setw(18) << id <<
          left << setw(18) << name <<
          left << setw(18) << major <<
          left << setw(18) << gpa <<
          left << setw(18) << city << endl;
}


// Getters (Mutators)
void Student :: setID(char arg[]) {
    strncpy(id, arg, sizeof(id) - 1);
}   

void Student :: setName(char arg[]) {
    strncpy(name, arg, sizeof(name) - 1);
}

void Student :: setMajor(char arg[]) {
    strncpy(major, arg, sizeof(major) - 1);
}

void Student :: setGpa(double arg) {
    if (arg < 0 || arg > 4) {
        cout << "ERROR! GPA must be between 0 - 4. \n" <<
        "The new value was not assigned.\n";
        void;
    }
    gpa {arg};
}

void Student :: setCity(char arg[]) {
    strncpy(city, arg, sizeof(city) - 1);
}


// Getters (Accessors)
const char* Student :: getID() {
    return id;
}

const char* Student :: getName() {
    return name;
}

const char* Student :: getMajor() {
    return major;
}

const double Student :: getGpa() {
    return gpa;
}

const char* Student :: getCity() {
    return city;
}


// Operator Overload
ostream& operator<<(ostream& os, const Student& student) {
    student.output(os);
    return os;
}

// Class implmentation file for Student
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

#include "wk7_Student.h"

using namespace std;

int Student :: counter = 100000;

Student :: Student(string arg_name, string arg_major, double arg_gpa, string arg_city) {
    itoa(++counter, id, 10);

    strncpy(name, arg_name.c_str(), sizeof(name) - 1);
    strncpy(major, arg_major.c_str(), sizeof(major) - 1);
    strncpy(city, arg_city.c_str(), sizeof(city) - 1);
    
    name[sizeof(name)-1] = '\0';
    major[sizeof(major) - 1] = '\0';
    city[sizeof(city) - 1] = '\0';
    
    gpa = arg_gpa;
}

Student :: Student(const Student& other): gpa {other.gpa} {
    itoa(++counter, id, 10);

    strncpy(name, other.name, sizeof(name) - 1);
    strncpy(city, other.city, sizeof(city) - 1);
    strncpy(major, other.major, sizeof(major) - 1);

    name[sizeof(name) - 1] = '\0';
    city[sizeof(city) - 1] = '\0';
    major[sizeof(major) - 1] = '\0';
}

void Student :: output(ostream& os) {
    os << left << setw(8) << id <<
          left << setw(17) << name <<
          left << setw(27) << major <<
          left << setw(6) << gpa <<
          left << setw(14) << city << endl;
}


// Setters (Mutators)
void Student :: setID(char arg[]) {
    strncpy(id, arg, sizeof(id) - 1);
    major[sizeof(major) - 1] = '\0';
}   

void Student :: setName(char arg[]) {
    strncpy(name, arg, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
}

void Student :: setMajor(char arg[]) {
    strncpy(major, arg, sizeof(major) - 1);
    major[sizeof(major) - 1] = '\0';
}

void Student :: setGpa(double arg) {
    if (arg < 0 || arg > 4) {
        cout << "ERROR! GPA must be between 0 - 4. \n" <<
        "The new value was not assigned.\n";
        return;
    }
    gpa = arg;
}

void Student :: setCity(char arg[]) {
    strncpy(city, arg, sizeof(city) - 1);
    city[sizeof(city) - 1] = '\0';
}


// Getters (Accessors)
// (Cannot change the value of the return type from the main nor inside other member funcs)
const char* Student :: getID() const {
    return id;
}

const char* Student :: getName() const {
    return name;
}

const char* Student :: getMajor() const {
    return major;
}

const double Student :: getGpa() const {
    return gpa;
}

const char* Student :: getCity() const {
    return city;
}


// Operator Overload
ostream& operator<<(ostream& os, Student& student) {
    student.output(os);
    return os;
}

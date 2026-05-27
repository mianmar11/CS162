#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

#include "wk8_class.h"

using namespace std;

// Constructors
Person::Person(const char* argName, int argAge): age{argAge} {
    strncpy(name, argName, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
}

Person::Person(const Person &source) {
    strncpy(name, source.name, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';

    age = source.age;
}

Student::Student(const char* name, int age, const char* argID, const char* argMajor, 
double argGPA, const char* argCity): Person(name, age) {

    strncpy(id, argID, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    strncpy(major, argMajor, sizeof(major) - 1);
    major[sizeof(major) - 1] = '\0';

    strncpy(city, argCity, sizeof(city) - 1);
    city[sizeof(city) - 1] = '\0';

    gpa = argGPA;
}

Student::Student(const Student &source) {
    
    strncpy(name, source.name, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';

    age = source.age;

    strncpy(id, source.id, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    strncpy(major, source.major, sizeof(major) - 1);
    major[sizeof(major) - 1] = '\0';

    strncpy(city, source.city, sizeof(city) - 1);
    city[sizeof(city) - 1] = '\0';

    gpa = source.gpa;
}


// Functions
void Person::output(ostream& os) {
    os << right << setw(8) << "Name: " << left << setw(25) << name << endl
       << right << setw(8) << "Age: "  << left << setw(25) << age << endl;
}

void Student::output(ostream& os) {
    Person::output(os);

    os << right << setw(8) << "ID: " << left << setw(25) << id << endl
       << right << setw(8) << "Major: "  << left << setw(25) << major << endl
       << right << setw(8) << "GPA: " << left << setw(25) << gpa << endl
       << right << setw(8) << "City: "  << left << setw(25) << city << endl;
}

// Setters
void Person::setName(const char* newName) {
    strncpy(name, newName, sizeof(name) - 1);
    name[sizeof(name) - 1] = '\0';
}

void Person::setAge(int newAge) {
    age = newAge;
}

void Student::setID(const char* newID) {
    strncpy(id, newID, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';
}

void Student::setMajor(const char* newMajor) {
    strncpy(major, newMajor, sizeof(major) - 1);
    major[sizeof(major) - 1] = '\0';
}

void Student::setGPA(double newGPA) {
    gpa = newGPA;
}

void Student::setCity(const char* newCity) {
    strncpy(city, newCity, sizeof(city) - 1);
    city[sizeof(city) - 1] = '\0';
}

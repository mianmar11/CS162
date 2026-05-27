#include <iostream>
#pragma once


class Person {
    private:

    protected:
        char name[25];
        int age;
    
    public:
        Person(): name{""}, age{0} {};
        Person(const char* argName, int argAge): age{argAge} {};
        Person(Person &source);

        void output(std::ostream& os);

        void setName(const char* newName);
        void setAge(int newAge);

        const char* getName() {return name;};
        int getAge() {return age;};
};


class Student: public Person {
    private:
        char id[6];
        char major[18];
        double gpa;
        char city[12];

    protected: 

    public:
        Student(const char* argID, const char* argMajor, 
        double argGPA, const char* city);
};

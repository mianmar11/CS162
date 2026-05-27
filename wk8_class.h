#include <iostream>
#pragma once


class Person {
    private:

    protected:
        char name[25];
        int age;
    
    public:
        Person(): name{""}, age{0} {};
        Person(const char* argName, int argAge);
        Person(const Person &source);

        void output(std::ostream& os);

        void setName(const char* newName);
        void setAge(int newAge);

        const char* getName();
        int getAge();
};


class Student: public Person {
    private:
        char id[6];
        char major[18];
        double gpa;
        char city[12];

    protected: 

    public:
        Student();
        Student(const char* name, int age, const char* argID, const char* argMajor, 
        double argGPA, const char* argCity);
        Student(const Student &source);

        void output(std::ostream& os);

        void setID(const char* newID);
        void setMajor(const char* newMajor);
        void setGPA(double newGPA);
        void setCity(const char* newCity);

        const char* getID();
        const char* getMajor();
        double getGPA();
        const char* getCity();
};

// Class specification for Student class 
#include <iostream>
#pragma once

class Student { 
    private:
        static int counter; // increment each time a class is instantiated
        char id[7];         // 6 digit id with ending \0 (counter)
        char name[16];      // 16 char name with ending \0
        char major[26];     // 26 char with ending \0
        double gpa;         // cumulative gpa 
        char city[13];      // 13 char city with ending \0
    
    public: 
        Student(): id{++counter}, name{""},         // Default constructor
            major{""}, gpa{0.0}, city{""} {};
        Student(char[], char[], double, char[]);    // Parameterize constructor

        void output(std::ostream&);         // write the member datas to any ostream destination or file

        void setID(char[]);                 
        void setName(char[]);
        void setMajor(char[]);
        void setGpa(double);
        void setCity(char[]);

        const char* getID();
        const char* getName();
        const char* getMajor();
        const double getGpa();
        const char* getCity();

        friend std::ostream& operator<<(std::ostream&, Student&);
};
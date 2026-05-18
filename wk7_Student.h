// Class specification for Student class 
#include <iostream>
#include <string>

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
        Student(): name{""},         // Default constructor
            major{""}, gpa{0.0}, city{""} {itoa(++counter, id, 10);};
        Student(std::string, std::string, double, std::string);    // Parameterize constructor
        Student(const Student& other);              // Copy Constructor

        void output(std::ostream&);         // write the member datas to any ostream destination or file

        void setID(std::string);                 
        void setName(std::string);
        void setMajor(std::string);
        void setGpa(double);
        void setCity(std::string);

        const char* getID() const;
        const char* getName() const;
        const char* getMajor() const;
        const double getGpa() const;
        const char* getCity() const;

        friend std::ostream& operator<<(std::ostream&, Student&);
};
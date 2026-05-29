#pragma once 

#include <iostream>

class Tester {
    protected:
    public: // temp, testing purposes only 
        std::string name;
        int score;
    
    public: 
        Tester(): name {""}, score {} {};
        Tester(std::string argName, int argScore): name {argName}, score {argScore} {};
        ~Tester();
        
        void setName(std::string newName);
        void setScore(int newScore);

        std::string getName();
        int getScore();

        void output(std::ostream& os);
};